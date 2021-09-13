#include <misaka/lru_cache.hpp>

#include <array>

#include <gtest/gtest.h>

using namespace misaka;

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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}