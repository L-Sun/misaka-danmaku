#include "Core.hpp"

#include <gtest/gtest.h>

using namespace Misaka;

class CoreTest : public ::testing::Test {
protected:
    CoreTest() {
    }

    ~CoreTest() {
    }

    Core                 seed;
    std::array<Core, 10> clients;
};

TEST_F(CoreTest, ConnectSuccessfully) {
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}