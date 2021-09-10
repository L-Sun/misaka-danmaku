#pragma once

#include <asio/io_context.hpp>
#include <asio/co_spawn.hpp>
#include <asio/awaitable.hpp>
#include <asio/detached.hpp>

template <typename F>
auto co_test(asio::io_context& io_context, F&& func) {
    asio::co_spawn(
        io_context,
        [&]() -> asio::awaitable<void> {
            co_await func();
            io_context.stop();
        },
        asio::detached);
    io_context.run();
}