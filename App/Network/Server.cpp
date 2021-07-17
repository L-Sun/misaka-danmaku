#include "Server.hpp"

#include <asio/use_awaitable.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <google/protobuf/util/time_util.h>

#include <format>
#include <random>
#include <chrono>

template <class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

namespace Misaka {

UdpServer::UdpServer(
    Kademlia::ID      id,
    asio::io_context& io_context,
    std::string_view  address,
    uint16_t          port)
    : m_RouteTable(id),
      m_Socket(io_context, asio::ip::udp::endpoint(asio::ip::make_address(address), port)),
      m_Carrier(io_context),
      m_Logger(spdlog::stderr_color_st(std::format("UDP Server {}:{}", address, port))) {
#if defined(_DEBUG)

    m_Logger->set_level(spdlog::level::debug);
    m_Logger->debug("Init");

#endif  // _DEBUG
}

asio::awaitable<void> UdpServer::Listen() {
    m_Logger->info("start listening.");
    try {
        asio::ip::udp::endpoint remote;
        while (true) {
            size_t n = co_await m_Socket.async_receive_from(
                asio::buffer(m_ReciveBuffer.data(), m_ReciveBuffer.size()),
                remote,
                asio::use_awaitable);

            m_Logger->debug("get a message from {}:{}", remote.address().to_string(), remote.port());
            co_await ProcessMessage(m_ReciveBuffer.data(), n, remote);
        }
    } catch (std::exception e) {
        m_Logger->error(e.what());
    }
}

asio::awaitable<std::optional<Response>> UdpServer::Send(Request              request,
                                                         const Kademlia::ID&  remote,
                                                         std::chrono::seconds timeout) {
    auto remote_endpoint = m_RouteTable.GetBuckets(remote).Get(remote);
    if (!remote_endpoint.has_value())
        co_return std::nullopt;

    auto message = GenerateMessage(std::move(request));
    auto buffer  = message.SerializeAsString();
    try {
        m_Logger->debug("send message to {}:{}",
                        remote_endpoint->get().address().to_string(),
                        remote_endpoint->get().port());

        co_await m_Socket.async_send_to(asio::buffer(buffer), remote_endpoint->get(), asio::use_awaitable);
    } catch (const std::exception& e) {
        m_Logger->error(e.what());
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
    message.set_originid(m_RouteTable.GetID().to_string());
    message.set_messageid(message_id.has_value() ? message_id.value() : distribution(generator));
    (*message.mutable_time()) = google::protobuf::util::TimeUtil::GetCurrentTime();

    std::visit(overloaded{
                   [&](Request& arg) {
                       (*message.mutable_request()) = std::move(arg);
                   },
                   [&](Response& arg) {
                       (*message.mutable_response()) = std::move(arg);
                   },
               },
               payload);

    return message;
}

asio::awaitable<void> UdpServer::ProcessMessage(uint8_t* data, size_t n, const asio::ip::udp::endpoint& remote) {
    KademliaMessage message;
    if (!message.ParseFromArray(data, n)) {
        m_Logger->warn("The data form {}:{} can not be parse, and it will be discard!",
                       remote.address().to_string(), remote.port());
        co_return;
    }

    uint64_t message_id = message.messageid();
    if (message.has_request()) {
        auto response = m_RequestProcessor(message.request());
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

}  // namespace Misaka