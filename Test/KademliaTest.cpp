#include "Kademlia.hpp"

#include <gtest/gtest.h>

using namespace Misaka::Kademlia;

TEST(DistanceTest, DifferentID) {
    std::bitset<8> id1, id2;

    id1 = 0b10110100;
    id2 = 0b00100010;
    ASSERT_EQ(cpl(id1, id2), 0);

    id1 = 0b01001011;
    id2 = 0b01001101;
    ASSERT_EQ(cpl(id1, id2), 5);

    id1 = 0b01001011;
    id2 = 0b01001010;
    ASSERT_EQ(cpl(id1, id2), 7);
}

TEST(DistanceTest, SameID) {
    std::bitset<8> id1, id2;

    id1 = 0b10110100;
    id2 = 0b10110100;
    ASSERT_EQ(cpl(id1, id2), 8);
}

class LRUTest : public ::testing::Test {
protected:
    LRUTest() {
        for (size_t i = 0; i < 8; i++)
            EXPECT_NO_THROW(cache.Add(i, i));
    }
    LRUCache<int, int, 8> cache;
};

TEST_F(LRUTest, Add) {
    EXPECT_NO_THROW(cache.Add(5, 5));
    EXPECT_NO_THROW(cache.Add(16, 16));
}

TEST_F(LRUTest, Get) {
    EXPECT_EQ(cache.Get(0), 0);
    EXPECT_EQ(cache.Get(9), std::nullopt);
}

TEST_F(LRUTest, WeedOut) {
    cache.Add(9, 9);
    EXPECT_EQ(cache.Get(0), std::nullopt);
}

TEST_F(LRUTest, Sequence) {
    int i = 7;
    for (const auto& [key, value] : cache) {
        EXPECT_EQ(value, i--);
    }

    for (i = 7; i >= 0; i--)
        cache.Add(i, i);

    i = 0;
    for (const auto& [key, value] : cache)
        EXPECT_EQ(value, i++);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}