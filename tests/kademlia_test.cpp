#include "utils.hpp"

#include <misaka/core/kademlia_engine.hpp>
#include <misaka/net/udp_server.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <unordered_set>

using namespace misaka::core;

auto create_id(const char (&str)[200]) {
    std::string result(str);
    result.erase(std::remove(result.begin(), result.end(), '\''), result.end());
    return KadID(result, 0, result.size(), '_', '*');
}

TEST(IDTest, GenerateRandomID) {
    std::unordered_set<KadID> ids;
    for (size_t i = 0; i < 1000; i++) {
        ASSERT_NO_THROW(ids.emplace(GenerateRandomID<160>()));
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

TEST(TableTest, Add) {
    RouteTable<int> table(GenerateRandomID<IDsize>());
    auto            id = GenerateRandomID<IDsize>();
    table.Add(id, 32);
    EXPECT_TRUE(table.GetBucket(id).Get(id).has_value());
    EXPECT_EQ(table.GetBucket(id).Get(id).value(), 32);
}

TEST(TableTest, AddSameID) {
    RouteTable<int> table(GenerateRandomID<IDsize>());
    auto            id = GenerateRandomID<IDsize>();
    table.Add(id, 32);
    EXPECT_TRUE(table.GetBucket(id).Get(id).has_value());
    EXPECT_EQ(table.GetBucket(id).Get(id).value(), 32);

    table.Add(id, 31);

    EXPECT_TRUE(table.GetBucket(id).Get(id).has_value());
    EXPECT_EQ(table.GetBucket(id).Get(id).value(), 31);
}

TEST(TableTest, GetBucket) {
    RouteTable<int> table(0);
    EXPECT_EQ(table.GetBucket(0).Size(), 0);

    auto peer1 = create_id(
        "____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'___*");
    auto peer2 = create_id(
        "____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'__*_");
    table.Add(peer1, 1);
    table.Add(peer2, 2);
    table.Add(peer2, 2);
    EXPECT_EQ(table.GetBucket(peer1).Size(), 2);
    EXPECT_EQ(table.GetBucket(peer2).Size(), 2);

    auto peer3 = create_id(
        "____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'__**");
    table.Add(peer3, 3);
    EXPECT_EQ(table.GetBucket(peer3).Size(), 3);

    KadID id = 0;
    for (size_t i = 0; i < BucketSize + 10; i++) {
        id.set(IDsize - 1 - i, true);
        table.Add(id, i);
    }

    EXPECT_EQ(table.GetBucket(id).Size(), BucketSize) << "should split to two bucket(right tree 20 nodes, left tree 3 nodes)";
    EXPECT_EQ(table.GetBucket(0).Size(), 3) << "should split to two bucket(right tree 20 nodes, left tree 3 nodes)";

    auto peer4 = create_id(
        "____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'____'_*__");
    table.Add(peer4, 4);
    EXPECT_EQ(table.GetBucket(peer3).Size(), 4) << "should contain 4 nodes beacause of it exsist in right tree";
}

class KademliaTest : public ::testing::Test {
protected:
    constexpr static uint16_t num_clients = 2;
    KademliaTest()
        : io_context(1),
          seedServer(std::make_shared<misaka::Network::udp_server>(io_context, "127.0.0.1", 5000)),
          clients{create_clients<num_clients>(io_context, 4000)} {
        seedServer->SetRequestProcessor([](const misaka::Network::Context& context) -> Response {
            auto [request, remote] = context;
            Response response;
            if (request.has_ping()) {
                response.mutable_ping()->set_state(PingResponse_State::PingResponse_State_RUNNING);
            }
            return response;
        });

        seedServer->Listen();
    }

    ~KademliaTest() {}

    asio::io_context                         io_context;
    std::shared_ptr<misaka::Network::Server> seedServer;
    std::array<KadEngine, num_clients>       clients;

private:
    template <uint16_t N>
    static std::array<KadEngine, N> create_clients(asio::io_context& io_context, uint16_t portBase) {
        constexpr auto impl = []<uint16_t... I>(asio::io_context & io_context, uint16_t portBase, std::integer_sequence<uint16_t, I...>) {
            return std::array{
                KadEngine(std::make_shared<misaka::Network::udp_server>(io_context, "127.0.0.1", portBase + I))...};
        };
        return impl(io_context, portBase, std::make_integer_sequence<uint16_t, N>{});
    }
};

TEST_F(KademliaTest, ConnectNetwork) {
    co_test(io_context, [&]() -> asio::awaitable<void> {
        EXPECT_TRUE(co_await clients[0].ConnectToNetwork("127.0.0.1", 5000)) << "it should be successful to connect to network.";
        EXPECT_FALSE(co_await clients[1].ConnectToNetwork("127.0.0.1", 5001)) << "it should be failed to connect unexsist network.";
    });
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}