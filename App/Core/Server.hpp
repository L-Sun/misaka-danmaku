#pragma once
#include "kademlia.pb.h"

#include <cppcoro/task.hpp>
#include <cppcoro/io_service.hpp>
#include <cppcoro/cancellation_source.hpp>
#include <cppcoro/net/socket.hpp>

#include <spdlog/logger.h>

#include <array>
#include <optional>

namespace Misaka {

class UdpServer {
public:
    UdpServer(std::string_view address, uint16_t port);

    cppcoro::task<void> Listen();
    void                Stop();

    inline cppcoro::net::ip_endpoint GetEndpoint() noexcept { return m_Endpoint; }

    cppcoro::task<NodeState> Ping(const cppcoro::net::ip_endpoint& remote);
    cppcoro::task<Response>  SendRequest(Request request, const cppcoro::net::ip_endpoint& remote);

    inline void SetHandleRequestProcessor(std::function<void(const Request&)>&& processor) noexcept {
        m_RequestProcessor = std::move(processor);
    }

private:
    // Function
    void                ParseMessage(std::string_view message, const cppcoro::net::ip_endpoint& endpoint);
    KademliaMessage     GenerateMessage();
    cppcoro::task<void> SendMessage(const cppcoro::net::ip_endpoint& remote, const KademliaMessage& message);
    uint64_t            GenerateMessageID();

    // Variable
    cppcoro::io_service          m_IOService;
    cppcoro::cancellation_source m_Canceller;
    cppcoro::net::ip_endpoint    m_Endpoint;
    cppcoro::net::socket         m_Socket;

    std::array<char, 128> m_Buffer;

    std::function<void(const Request&)> m_RequestProcessor;

    std::shared_ptr<spdlog::logger> m_Logger;
};

}  // namespace Misaka