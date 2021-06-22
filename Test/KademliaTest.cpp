#include "Kademlia.hpp"

#include <gtest/gtest.h>

#include <unordered_set>

using namespace Misaka::Kademlia;

TEST(IDTest, RandomID) {
    std::unordered_set<ID> ids;
    for (size_t i = 0; i < 1000; i++) {
        ASSERT_NO_THROW(ids.emplace(random_bitset<160>()));
    }
}

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

    LRUCache<int, int, 8> cache2;
    cache2.Add(0, 1);
    EXPECT_EQ(cache2.Get(0), 1);
    EXPECT_EQ(cache2.Get(0), 1);
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

    std::array get_seq = {5, 3, 2, 7, 0, 2, 1, 6};
    for (auto&& e : get_seq)
        EXPECT_EQ(cache.Get(e), e);

    std::array seq = {6, 1, 2, 0, 7, 3, 5, 4};
    i              = 0;
    for (const auto& [key, value] : cache)
        EXPECT_EQ(value, seq[i++]);
}

TEST(TableTest, Add) {
    RouteTable<int> table;
    auto            id = random_bitset<IDsize>();
    table.Add(id, 32);
    EXPECT_TRUE(table.Get(id).Get(id).has_value());
    EXPECT_EQ(table.Get(id).Get(id).value(), 32);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}