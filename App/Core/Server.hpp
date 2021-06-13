#pragma once
#include "kademlia.pb.h"

#include <asio/awaitable.hpp>
#include <asio/ip/udp.hpp>
#include <spdlog/logger.h>

#include <array>
#include <optional>
#include <chrono>

namespace Misaka {

class UdpServer {
public:
    UdpServer(std::string_view address, uint16_t port);
    // Bind endpoint to udp server
    void Bind(std::string_view address, uint16_t port);
    // Set a request timeout
    void SetTimeout(std::chrono::duration timeout);

    asio::awaitable<void>     Listen();
    asio::awaitable<Response> SendRequest(Request request);

private:
    void                ParseMessage(std::string_view message, const asio::ip::udp::endpoint& endpoint);
    KademliaMessage     GenerateMessage();
    cppcoro::task<void> SendMessage(const cppcoro::net::ip_endpoint& remote, const KademliaMessage& message);
    uint64_t            GenerateMessageID();

    std::function<void(const Request&)> m_RequestProcessor;

    std::shared_ptr<spdlog::logger> m_Logger;
};

}  // namespace Misaka