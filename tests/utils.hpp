#pragma once

#include <asio/io_context.hpp>
#include <asio/co_spawn.hpp>
#include <asio/compose.hpp>
#include <asio/awaitable.hpp>
#include <asio/detached.hpp>

#include <gmock/gmock.h>

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

template <typename T>
auto CoReturn(T&& val) {
    using ::testing::ByMove;
    using ::testing::Return;
    return Return(
        ByMove(
            asio::async_compose<decltype(asio::use_awaitable), void(T)>(
                [_val = std::move(val)](auto&& self) {
                    self.complete(_val);
                },
                asio::use_awaitable)));
}
