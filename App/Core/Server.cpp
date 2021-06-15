#include "Server.hpp"

#include <asio/use_awaitable.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <format>
#include <chrono>

namespace Misaka {

std::variant<std::monostate, Request, Response> UdpServer::PaserMessage(
    uint8_t* data,
    size_t   size) {
    std::variant<std::monostate, Request, Response> result;
    // TODO paser data to request or response
    return result;
}

UdpServer::UdpServer(
    asio::io_context&                              io_context,
    Kademlia::RouteTable<asio::ip::udp::endpoint>& route_table,
    std::string_view                               address,
    uint16_t                                       port)
    : m_Socket(io_context, asio::ip::udp::endpoint(asio::ip::make_address(address), port)),
      m_RouteTable(route_table),
      m_Logger(spdlog::stdout_color_st(std::format("UDP Server {}:{}", address, port))) {
#if defined(_DEBUG)

    m_Logger->set_level(spdlog::level::debug);

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

            auto data = PaserMessage(m_ReciveBuffer.data(), n);
            if (std::holds_alternative<Request>(data))
                ProcessRequest(std::get<Request>(data));
            else if (std::holds_alternative<Response>(data))
                ProcessResponse(std::get<Response>(data));
            else
                m_Logger->warn(
                    "discard the data from: {}:{}",
                    remote.address().to_string(),
                    remote.port());
        }
    } catch (std::exception e) {
        m_Logger->error(e.what());
    }
}

asio::awaitable<Response> UdpServer::Send(Request&& request, const asio::ip::udp::endpoint& remote) {
    auto message = GenerateMessage(std::move(request));
    auto buffer  = message.SerializeAsString();
    try {
        // co_await m_Socket.async_send_to(asio::buffer(buffer), remote, asio::use_awaitable);
    } catch (const std::exception& e) {
        m_Logger->error(e.what());
    }
    uint64_t message_id = message.messageid();

    auto x = co_await m_ResponsesPool.at(message_id);
}

KademliaMessage UdpServer::GenerateMessage(Request&& request) {
}

KademliaMessage UdpServer::GenerateMessage(Response&& response) {
}

}  // namespace Misaka
