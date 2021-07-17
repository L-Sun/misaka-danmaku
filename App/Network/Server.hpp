#pragma once
#include "kademlia.pb.h"
#include "RouteTable.hpp"
#include "Carrier.hpp"

#include <asio/awaitable.hpp>
#include <asio/ip/udp.hpp>
#include <asio/steady_timer.hpp>

#include <spdlog/logger.h>

#include <array>
#include <variant>
#include <unordered_map>
#include <chrono>

namespace Misaka {

class UdpServer {
public:
    UdpServer(
        Kademlia::ID      id,
        asio::io_context& io_context,
        std::string_view  address = "127.0.0.1",
        uint16_t          port    = 8000);

    // Bind endpoint to udp server
    void Bind(std::string_view address, uint16_t port);

    inline auto Endpoint() const noexcept { return m_Socket.local_endpoint(); }

    inline auto& RouteTable() noexcept { return m_RouteTable; }

    // Set request processor
    inline void SetRequestProcessor(std::function<Response(const Request&)> processor) noexcept {
        m_RequestProcessor = processor;
    }

    asio::awaitable<void>                    Listen();
    asio::awaitable<std::optional<Response>> Send(Request              request,
                                                  const Kademlia::ID&  remote,
                                                  std::chrono::seconds timeout = std::chrono::seconds(30));

private:
    asio::awaitable<void> ProcessMessage(uint8_t* data, size_t n, const asio::ip::udp::endpoint& remote);

    KademliaMessage GenerateMessage(std::variant<Request, Response> payload,
                                    std::optional<uint64_t>         message_id = std::nullopt);

    // asio
    asio::ip::udp::socket     m_Socket;
    std::array<uint8_t, 8192> m_ReciveBuffer;
    Carrier<Response>         m_Carrier;

    // route table
    Kademlia::RouteTable<asio::ip::udp::endpoint> m_RouteTable;

    std::function<Response(const Request&)> m_RequestProcessor;
    std::shared_ptr<spdlog::logger>         m_Logger;
};

}  // namespace Misaka