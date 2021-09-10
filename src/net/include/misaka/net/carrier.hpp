#pragma once
#include <asio/io_context.hpp>
#include <asio/awaitable.hpp>
#include <asio/use_awaitable.hpp>
#include <asio/steady_timer.hpp>
#include <asio/redirect_error.hpp>

#include <chrono>
#include <optional>
#include <unordered_map>

namespace misaka {

template <typename T>
class Carrier {
    using Item = std::pair<std::optional<T>, asio::steady_timer>;

public:
    Carrier(asio::io_context& io_context) : m_IOContext(io_context) {}

    void Set(uint64_t id, T value) {
        auto&& [_value, timer] = m_Goods.at(id);
        _value                 = std::move(value);
        timer.expires_after(std::chrono::seconds(0));
    }

    asio::awaitable<std::optional<T>> Get(uint64_t id, std::chrono::steady_clock::duration timeout) {
        if (m_RefCounters.count(id) != 0)
            m_RefCounters.at(id)++;
        else {
            m_Goods.emplace(id, std::make_pair(std::nullopt, asio::steady_timer(m_IOContext.get(), timeout)));
            m_RefCounters.emplace(id, 1);
        }

        auto&& [value, timer] = m_Goods.at(id);
        size_t& ref           = m_RefCounters.at(id);

        asio::error_code ec;
        co_await timer.async_wait(asio::redirect_error(asio::use_awaitable, ec));

        if (ref > 1) {
            ref--;
            co_return value;
        } else {
            auto temp = std::move(value);
            m_Goods.erase(id);
            m_RefCounters.erase(id);
            co_return temp;
        }
    }

private:
    std::reference_wrapper<asio::io_context> m_IOContext;
    std::unordered_map<uint64_t, Item>       m_Goods;
    std::unordered_map<uint64_t, size_t>     m_RefCounters;
};

}  // namespace misaka
