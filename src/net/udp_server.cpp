#include <misaka/net/udp_server.hpp>

#include <asio/use_awaitable.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <google/protobuf/util/time_util.h>
#include <fmt/format.h>

#include <random>
#include <chrono>

template <class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

namespace misaka::net {

UdpServer::UdpServer(
    asio::io_context& io_context,
    std::string_view  address,
    uint16_t          port)
    : m_IOContext(io_context),
      m_Socket(io_context, Endpoint(asio::ip::make_address(address), port)),
      m_Carrier(io_context),
      m_RunningTimer(io_context),
      m_Logger(spdlog::stderr_color_st(fmt::format("UDP Server {}:{}", address, port))) {
#if defined(_DEBUG)
    m_Logger->set_level(spdlog::level::debug);
#endif  // _DEBUG
    m_Logger->info("Init");
}

void UdpServer::Listen() {
    if (m_Running || std::chrono::steady_clock::now() < m_RunningTimer.expiry()) return;

    m_Running = true;
    m_RunningTimer.expires_at(std::chrono::steady_clock::time_point::max());
    asio::co_spawn(
        m_IOContext, [&]() -> asio::awaitable<void> {
            m_Logger->info("start listening.");
            while (m_Running) {
                try {
                    Endpoint remote;
                    size_t   n = co_await m_Socket.async_receive_from(
                        asio::buffer(m_ReciveBuffer.data(), m_ReciveBuffer.size()),
                        remote,
                        asio::use_awaitable);

                    m_Logger->debug("get a message from {}:{}", remote.address().to_string(), remote.port());
                    co_await ProcessMessage(m_ReciveBuffer.data(), n, remote);

                    if (!m_Running) {
                        m_RunningTimer.expires_from_now(std::chrono::seconds(0));
                    }
                } catch (std::exception e) {
                    m_Logger->error(e.what());
                }
            }
        },
        asio::detached);
}

void UdpServer::StopListen() {
    m_Logger->info("stop listening.");
    m_Running = false;
}

void UdpServer::SetRequestProcessor(std::function<Response(const Context&)> processor) {
    m_RequestProcessor = processor;
}

asio::awaitable<std::optional<Response>> UdpServer::Send(Request              request,
                                                         const Endpoint&      remote,
                                                         std::chrono::seconds timeout) {
    auto message = GenerateMessage(std::move(request));
    auto buffer  = message.SerializeAsString();
    try {
        m_Logger->debug("send message to {}:{}",
                        remote.address().to_string(),
                        remote.port());

        co_await m_Socket.async_send_to(asio::buffer(buffer), remote, asio::use_awaitable);
    } catch (const std::exception& e) {
        m_Logger->error("{} remote:{}:{}", e.what(), remote.address().to_string(), remote.port());
    }
    uint64_t message_id = message.messageid();
    auto     response   = co_await m_Carrier.Get(message_id, timeout);
    co_return response;
}

KademliaMessage UdpServer::GenerateMessage(std::variant<Request, Response> payload, std::optional<uint64_t> message_id) {
    static thread_local std::mt19937_64     generator;
    std::uniform_int_distribution<uint64_t> distribution(
        std::numeric_limits<uint64_t>::min(),
        std::numeric_limits<uint64_t>::max());

    KademliaMessage message;
    message.set_messageid(message_id.has_value() ? message_id.value() : distribution(generator));
    (*message.mutable_time()) = google::protobuf::util::TimeUtil::GetCurrentTime();

    std::visit(overloaded{
                   [&](Request&& arg) {
                       (*message.mutable_request()) = std::move(arg);
                   },
                   [&](Response&& arg) {
                       (*message.mutable_response()) = std::move(arg);
                   },
               },
               std::move(payload));

    return message;
}

asio::awaitable<void> UdpServer::ProcessMessage(uint8_t* data, size_t n, const Endpoint& remote) {
    KademliaMessage message;
    if (!message.ParseFromArray(data, n)) {
        m_Logger->warn("The data form {}:{} can not be parse, and it will be discard!",
                       remote.address().to_string(), remote.port());
        co_return;
    }

    uint64_t message_id = message.messageid();
    if (message.has_request()) {
        if (!m_RequestProcessor) {
            m_Logger->warn("Please set a request processor to handle income request.");
            co_return;
        }

        auto response = m_RequestProcessor({message.request(), remote});
        auto buffer   = GenerateMessage(response, message_id).SerializeAsString();
        try {
            m_Logger->debug("send message to {}:{}", remote.address().to_string(), remote.port());

            co_await m_Socket.async_send_to(asio::buffer(buffer), remote, asio::use_awaitable);
        } catch (const std::exception& e) {
            m_Logger->warn(e.what());
        }

    } else {
        try {
            m_Carrier.Set(message_id, message.response());
        } catch (const std::range_error& e) {
            m_Logger->warn("Unexpected response from {}：{}", remote.address().to_string(), remote.port());
        }
    }
}

}  // namespace misaka::net
