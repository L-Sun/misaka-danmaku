#pragma once
#include <misaka/net/server.hpp>

#include <spdlog/logger.h>

#include <array>
#include <variant>
#include <unordered_map>

namespace misaka::net {
class UdpServer : public Server {
public:
    UdpServer(asio::io_context& io_context, std::string_view address, uint16_t port);

    void Listen() final;
    void StopListen() final;

    // Set request processor
    void                                     SetRequestProcessor(std::function<Response(const Context&)> processor) final;
    asio::awaitable<std::optional<Response>> Send(Request              request,
                                                  const Endpoint&      remote,
                                                  std::chrono::seconds timeout = std::chrono::seconds(3)) final;

    inline auto GetEndpoint() const noexcept { return m_Socket.local_endpoint(); }

private:
    asio::awaitable<void> ProcessMessage(uint8_t* data, size_t n, const Endpoint& remote);

    KademliaMessage GenerateMessage(std::variant<Request, Response> payload,
                                    std::optional<uint64_t>         message_id = std::nullopt);

    // asio
    asio::io_context&         m_IOContext;
    asio::ip::udp::socket     m_Socket;
    std::array<uint8_t, 8192> m_ReciveBuffer;
    Carrier<Response>         m_Carrier;
    bool                      m_Running = false;
    asio::steady_timer        m_RunningTimer;

    std::function<Response(const Context&)> m_RequestProcessor;
    std::shared_ptr<spdlog::logger>         m_Logger;
};

}  // namespace misaka::net
