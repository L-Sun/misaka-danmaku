#include "Core.hpp"

#include <gtest/gtest.h>

using namespace Misaka;

template <size_t N>
auto create_clients() {
    constexpr auto impl = []<size_t... I>(std::index_sequence<I...>) {
        return std::array{Core(I)...};
    };
    return impl(std::make_index_sequence<N>{});
}

class CoreTest : public ::testing::Test {
protected:
    CoreTest() : clients{create_clients<10>()} {
    }

    ~CoreTest() {
    }

    Core                 seed{10086};
    std::array<Core, 10> clients;
};

TEST_F(CoreTest, ConnectSuccessfully) {
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}