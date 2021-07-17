#include "Kademlia.hpp"
#include "TestUtils.hpp"

#include <gtest/gtest.h>

#include <unordered_set>

using namespace Misaka::Kademlia;

auto create_id(const char (&str)[200]) {
    std::string result(str);
    result.erase(std::remove(result.begin(), result.end(), '\''), result.end());
    return ID(result, 0, result.size(), '_', '*');
}

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

    id1 = 0b11001011;
    id2 = 0b01001010;
    ASSERT_EQ(cpl(id1, id2), 0);

    id1 = decltype(id1){"00000000"};
    id2 = decltype(id1){"00000001"};
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
    RouteTable<int> table(random_bitset<IDsize>());
    auto            id = random_bitset<IDsize>();
    table.Add(id, 32);
    EXPECT_TRUE(table.GetBuckets(id).Get(id).has_value());
    EXPECT_EQ(table.GetBuckets(id).Get(id).value(), 32);
}

TEST(TableTest, AddSameID) {
    RouteTable<int> table(random_bitset<IDsize>());
    auto            id = random_bitset<IDsize>();
    table.Add(id, 32);
    EXPECT_TRUE(table.GetBuckets(id).Get(id).has_value());
    EXPECT_EQ(table.GetBuckets(id).Get(id).value(), 32);

    table.Add(id, 31);
    EXPECT_TRUE(table.GetBuckets(id).Get(id).has_value());
    EXPECT_EQ(table.GetBuckets(id).Get(id).value(), 31);
}

TEST(TableTest, GetBucket) {
    RouteTable<int> table(0);
    EXPECT_THROW(table.GetBuckets(0).Size(), std::out_of_range) << "itself can not exsist in its buckets";

    auto peer1 = create_id(
        "____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'___*");
    auto peer2 = create_id(
        "____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'__*_");
    table.Add(peer1, 1);
    table.Add(peer2, 2);
    table.Add(peer2, 2);
    EXPECT_EQ(table.GetBuckets(peer1).Size(), 1);
    EXPECT_EQ(table.GetBuckets(peer2).Size(), 1);

    auto peer3 = create_id(
        "____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'__**");
    table.Add(peer3, 3);
    EXPECT_EQ(table.GetBuckets(peer3).Size(), 2);

    ID id = 0;
    for (size_t i = 0; i < BucketSize + 10; i++) {
        id.set(IDsize - 1 - i, true);
        table.Add(id, i);
    }

    EXPECT_EQ(table.GetBuckets(id).Size(), BucketSize);
}

class KademliaTest : public ::testing::Test {
protected:
    constexpr static size_t num_clients = 2;
    KademliaTest()
        : io_context(1),
          seedServer(10086, io_context, "127.0.0.1", 10086),
          clients{create_clients<num_clients>(io_context, 4000)} {
        /* Init here */
    }

    ~KademliaTest() {
        io_context.run();
    }
    asio::io_context                        io_context;
    KademliaEngine                          seedServer;
    std::array<KademliaEngine, num_clients> clients;

private:
    template <size_t N>
    static auto create_clients(asio::io_context& io_context, uint16_t portBase) {
        constexpr auto impl = []<size_t... I>(asio::io_context & io_context, uint16_t portBase, std::index_sequence<I...>) {
            return std::array{KademliaEngine(I, io_context, "127.0.0.1", portBase + I)...};
        };
        return impl(io_context, portBase, std::make_index_sequence<N>{});
    }
};

TEST_F(KademliaTest, ConnectNetwork) {
    co_test(io_context, [&]() -> asio::awaitable<void> {
        EXPECT_TRUE(co_await clients[0].ConnectToNetwork("127.0.0.1", 10086)) << "it should be successful to connect to network";
        EXPECT_FALSE(co_await clients[1].ConnectToNetwork("127.0.0.1", 10087)) << "it should be failed to connect unexsist network";
    });
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}