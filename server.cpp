#include <asio.hpp>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using asio::ip::udp;

auto logger = spdlog::stderr_color_st("Server");

class UdpServer {
public:
    UdpServer(asio::io_context& io_context) : m_Socket(io_context, udp::endpoint(udp::v4(), 13)) {
        StartRecive();
    }

private:
    void StartRecive() {
        m_Socket.async_receive_from(
            asio::buffer(m_RecvBuffer),
            m_RemoteEndpoint,
            [this](auto&&... args) { HandleRecive(std::forward<decltype(args)>(args)...); });
    }

    void HandleRecive(asio::error_code error, size_t bytes_transferred) {
        if (!error) {
            logger->info("Remote: {}", std::string(m_RecvBuffer.data(), bytes_transferred));

            auto message = std::make_shared<std::string>("2021/2/28");
            m_Socket.async_send_to(
                asio::buffer(*message),
                m_RemoteEndpoint,
                // extend life time of message
                [message, this](auto&&... args) { HandleSend(std::forward<decltype(args)>(args)...); });

            StartRecive();
        } else {
            logger->error(error.message());
        }
    }

    void HandleSend(asio::error_code error, size_t bytes_transferred) {
        if (!error) {
        } else {
            logger->error(error.message());
        }
    }

    udp::socket           m_Socket;
    std::array<char, 128> m_RecvBuffer;
    udp::endpoint         m_RemoteEndpoint;
};

int main(int argc, char const* argv[]) {
    try {
        asio::io_context io_context;
        UdpServer        server(io_context);

        io_context.run();
    } catch (const std::exception& e) {
        logger->error(e.what());
    }

    return 0;
}
