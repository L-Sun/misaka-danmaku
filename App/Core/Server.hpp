#pragma once
#include "kademlia.pb.h"
#include "RouteTable.hpp"

#include <asio/awaitable.hpp>
#include <asio/ip/udp.hpp>
#include <spdlog/logger.h>

#include <array>
#include <variant>

namespace Misaka {

class UdpServer {
public:
    UdpServer(
        asio::io_context&                              io_context,
        Kademlia::RouteTable<asio::ip::udp::endpoint>& route_table,
        std::string_view                               address = "127.0.0.1",
        uint16_t                                       port    = 8000);

    // Bind endpoint to udp server
    void Bind(std::string_view address, uint16_t port);
    // Set request processor
    inline void SetRequestProcessor(std::function<void(const Request&)> processor) noexcept {
        m_RequestProcessor = processor;
    }

    asio::awaitable<void>     Listen();
    asio::awaitable<Response> Send(Request request);

private:
    static std::variant<std::monostate, Request, Response> PaserMessage(uint8_t* data, size_t size);

    void ProcessRequest(const Request& request);
    void ProcessResponse(const Response& response);

    // asio
    asio::ip::udp::socket     m_Socket;
    std::array<uint8_t, 8192> m_ReciveBuffer;

    // route table
    Kademlia::RouteTable<asio::ip::udp::endpoint>& m_RouteTable;

    std::function<void(const Request&)> m_RequestProcessor;
    std::shared_ptr<spdlog::logger>     m_Logger;
};

}  // namespace Misaka