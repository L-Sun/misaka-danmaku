#pragma once
#include "kademlia.pb.h"
#include "Carrier.hpp"

#include <asio/awaitable.hpp>
#include <asio/ip/udp.hpp>
#include <asio/steady_timer.hpp>

#include <spdlog/logger.h>

#include <array>
#include <variant>
#include <unordered_map>
#include <chrono>

namespace Misaka::Network {

using Endpoint = asio::ip::udp::endpoint;

class UdpServer {
public:
    UdpServer(asio::io_context& io_context, std::string_view address, uint16_t port);

    inline auto GetEndpoint() const noexcept { return m_Socket.local_endpoint(); }

    // Set request processor
    inline void SetRequestProcessor(std::function<Response(Request req, Endpoint remote)> processor) noexcept {
        m_RequestProcessor = processor;
    }

    asio::awaitable<void> Listen();

    asio::awaitable<std::optional<Response>> Send(Request              request,
                                                  const Endpoint&      remote,
                                                  std::chrono::seconds timeout = std::chrono::seconds(3));

private:
    asio::awaitable<void> ProcessMessage(uint8_t* data, size_t n, const Endpoint& remote);

    KademliaMessage GenerateMessage(std::variant<Request, Response> payload,
                                    std::optional<uint64_t>         message_id = std::nullopt);

    // asio
    asio::ip::udp::socket     m_Socket;
    std::array<uint8_t, 8192> m_ReciveBuffer;
    Carrier<Response>         m_Carrier;

    std::function<Response(Request, Endpoint)> m_RequestProcessor;
    std::shared_ptr<spdlog::logger>            m_Logger;
};

}  // namespace Misaka::Network