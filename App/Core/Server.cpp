#include "Server.hpp"

#include <cppcoro/async_scope.hpp>
#include <cppcoro/when_all.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <fmt/format.h>

namespace Misaka {

UdpServer::UdpServer(std::string_view address, uint16_t port)
    : m_Socket(cppcoro::net::socket::create_udpv4(m_IOService)),
      m_Logger(spdlog::stdout_color_st(
          fmt::format("UDP Server {}:{}",
                      address,
                      port))) {
    m_Logger->set_level(spdlog::level::debug);

    auto _address = cppcoro::net::ipv4_address::from_string(address);
    if (_address) {
        m_Endpoint = cppcoro::net::ipv4_endpoint(*_address, port);
    } else {
        m_Logger->error("error format of address: {}", address);
        m_Logger->warn("will use address 0.0.0.0 as address");
        m_Endpoint = cppcoro::net::ipv4_endpoint(cppcoro::net::ipv4_address(), port);
    }

    m_Socket.bind(m_Endpoint);
    m_Logger->info("Host:{}", m_Endpoint.to_string());
}

cppcoro::task<void> UdpServer::Listen() {
    m_Logger->info("start listening.");
    std::exception_ptr ex;

    try {
        while (true) {
            auto [len, remote] = co_await m_Socket.recv_from(m_Buffer.data(), m_Buffer.size(), m_Canceller.token());
            m_Logger->debug(
                "Get data from: {}"
                "Data: {}",
                remote.to_string(), std::string_view(m_Buffer.data(), len));
        }
    } catch (cppcoro::operation_cancelled) {
        m_Logger->info("stop listening.");
    } catch (...) {
        ex = std::current_exception();
    }

    if (ex) std::rethrow_exception(ex);
}

void UdpServer::Stop() {
    m_Canceller.request_cancellation();
}

cppcoro::task<NodeState> UdpServer::Ping(const cppcoro::net::ip_endpoint& remote) {
    auto message = GenerateMessage();
    auto buffer  = message.SerializeAsString();

    m_Logger->debug("remote: {}", remote.address().to_string());

    co_await SendMessage(remote, message);

    // wait response here
    co_return NodeState::RUNNING;
}

cppcoro::task<Response> UdpServer::SendRequest(Request request, const cppcoro::net::ip_endpoint& remote) {
    auto message = GenerateMessage();
    message.set_allocated_request(&request);

    co_await SendMessage(remote, message);
    // wait response here

    co_return Response{};
}

cppcoro::task<void> UdpServer::SendMessage(const cppcoro::net::ip_endpoint& remote, const KademliaMessage& message) {
    auto   buffer      = message.SerializeAsString();
    size_t buffer_size = buffer.size();
    m_Logger->debug("send message, {} bytes(s)", buffer.size());

    try {
        size_t bytes_send = 0;
        while (bytes_send < buffer_size) {
            bytes_send += co_await m_Socket.send_to(remote, buffer.data() + bytes_send, buffer_size - bytes_send);
        }

        m_Socket.close_send();

    } catch (const std::exception& e) {
        m_Logger->error(e.what());
    }
}

KademliaMessage UdpServer::GenerateMessage() {
    KademliaMessage message;
    message.set_messageid(GenerateMessageID());
    message.set_state(NodeState::RUNNING);
    return message;
}

uint64_t UdpServer::GenerateMessageID() {
    // TODO
    thread_local uint64_t counter = 1;
    return counter++;
}

}  // namespace Misaka
