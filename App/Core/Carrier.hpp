#include <coroutine>
#include <optional>

namespace Misaka {
template <typename T>
class Carrier {
public:
    constexpr bool has_value() const noexcept {
        return m_value.has_value();
    }

    void set(const T& value) noexcept {
        m_value = value;
        m_awaiter.resume();
    }

    auto operator co_await() noexcept {
        class awaiter {
        public:
            awaiter(Carrier& carrier) : m_carrier(carrier) {}
            bool await_ready() const noexcept {
                return m_carrier.has_value();
            }

            bool await_suspend(std::coroutine_handle<> awaiter) {
                m_carrier.m_awaiter = awaiter;
                return true;
            }

            T await_resume() {
                return m_carrier.m_value.value();
            }

        private:
            Carrier& m_carrier;
        };

        return awaiter{*this};
    }

private:
    std::optional<T>        m_value;
    std::coroutine_handle<> m_awaiter;
};
}  // namespace Misaka