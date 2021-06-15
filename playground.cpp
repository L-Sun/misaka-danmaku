#include <asio/io_context.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/steady_timer.hpp>
#include <asio/async_result.hpp>
#include <asio/use_awaitable.hpp>

#include <chrono>
#include <iostream>

int main(int argc, char const* argv[]) {
    asio::io_context io_context;

    asio::async_result result();

    asio::co_spawn(
        io_context, [&]() -> asio::awaitable<void> {
            try {
                std::cout << "OK" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }
        },
        asio::detached);

    asio::co_spawn(
        io_context, [&]() -> asio::awaitable<void> {
            asio::steady_timer temp_timer(io_context, std::chrono::seconds(3));
            co_await temp_timer.async_wait(asio::use_awaitable);
        },
        asio::detached);

    io_context.run();
    return 0;
}
