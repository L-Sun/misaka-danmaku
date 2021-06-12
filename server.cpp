#include <asio/co_spawn.hpp>
#include <asio/io_context.hpp>
#include <asio/detached.hpp>
#include <asio/ip/udp.hpp>

#include <memory>
#include <format>
#include <iostream>

asio::awaitable<void> echo(asio::ip::udp::socket socket) {
    try {
        const size_t buffer_size = 1024;
        auto         buffer      = std::make_unique<uint8_t[]>(buffer_size);

        asio::ip::udp::endpoint remote;
        while (true) {
            size_t n = co_await socket.async_receive_from(asio::buffer(buffer.get(), buffer_size), remote, asio::use_awaitable);
            std::cout << std::string_view(reinterpret_cast<char*>(buffer.get()), n) << std::endl;
            co_await socket.async_send_to(asio::buffer(buffer.get(), n), remote, asio::use_awaitable);
        }
    } catch (const std::exception& e) {
        std::cerr << std::format("[Error]: {}", e.what()) << std::endl;
    }
}

auto make_endpoint_from_string(std::string_view s) {
    auto colon_pos = s.find(':');
    if (colon_pos == std::string_view::npos) {
        throw std::invalid_argument("colon symbol is missing, please input correct format like {host}:{port}");
    }

    auto address = asio::ip::make_address(s.substr(0, colon_pos));

    auto is_digit    = [](char c) -> bool { return c >= '0' && c <= '9'; };
    auto digit_value = [](char c) -> uint8_t { return static_cast<std::uint8_t>(c - '0'); };

    uint32_t port = 0;
    for (auto c : s.substr(colon_pos + 1)) {
        if (!is_digit(c)) throw std::invalid_argument("the value of port must be a number");
        port = port * 10 + digit_value(c);
        if (port > 0xFFFFu) throw std::invalid_argument("the value of port is exceed standar.");
    }

    return asio::ip::udp::endpoint(address, static_cast<uint16_t>(port));
}

int main(int argc, char const* argv[]) {
    if (argc != 2) return -1;
    auto endpoint = make_endpoint_from_string(argv[1]);

    try {
        asio::io_context io_context(1);

        asio::ip::udp::socket local(io_context, endpoint);

        asio::co_spawn(io_context, echo(std::move(local)), asio::detached);

        io_context.run();

    } catch (const std::exception& e) {
    }

    return 0;
}
