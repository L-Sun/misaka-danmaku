#include <iostream>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <asio/co_spawn.hpp>
#include <asio/io_context.hpp>
#include <asio/detached.hpp>

int main(int argc, char const* argv[]) {
    asio::io_context io_context(1);

    auto logger = spdlog::stdout_color_st("Test");

    asio::co_spawn(
        io_context, [&]() -> asio::awaitable<void> {
            logger->warn("Hello");
            co_return;
        },
        asio::detached);

    io_context.run();
    system("PAUSE");
    return 0;
}