#include "utils.hpp"
#include "mock/server.hpp"

#include <misaka/core/kademlia_engine.hpp>
#include <misaka/net/udp_server.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <unordered_set>

using namespace misaka::core;
using namespace ::testing;

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
    KademliaTest() : io_context(1), server(std::make_shared<MockServer>()) {}

    asio::io_context            io_context;
    std::shared_ptr<MockServer> server;
};

TEST_F(KademliaTest, InitEngine) {
    using ::testing::_;
    EXPECT_CALL(*server, Listen()).Times(1);
    EXPECT_CALL(*server, SetRequestProcessor(_)).Times(1);

    KadEngine engine(server);
}

TEST_F(KademliaTest, ConnectToNetwork) {
    co_test(io_context, [&]() -> asio::awaitable<void> {
        misaka::net::Endpoint alive_endpoint{asio::ip::make_address("127.0.0.1"), 1234};
        Request               req;
        req.mutable_ping();

        {
            Response res;
            res.mutable_ping()->set_state(PingResponse_State::PingResponse_State_RUNNING);

            EXPECT_CALL(
                *server,
                Send(
                    Property(&Request::request_case, Request::RequestCase::kPing),
                    alive_endpoint,
                    _))
                .WillOnce(CoReturn(std::make_optional<Response>(res)));
        }

        {
            Response res1;
            for (size_t i = 0; i < 3; i++) {
                auto node = res1.mutable_findnode()->add_nodes();
                node->set_address("127.0.0.2");
                node->set_port(1235 + i);
                node->set_id(GenerateRandomID().to_string());
            }

            Response res2;
            res2.CopyFrom(res1);
            res2.mutable_findnode()->clear_nodes();
            EXPECT_CALL(
                *server,
                Send(
                    Property(&Request::request_case, Request::RequestCase::kFindNode),
                    _,
                    _))
                .Times(4)
                .WillOnce(CoReturn(std::make_optional(res1)))
                .WillRepeatedly(CoReturn(std::make_optional(res2)));
        }

        KadEngine engine(server);
        EXPECT_TRUE(co_await engine.ConnectToNetwork(alive_endpoint.address().to_string(), alive_endpoint.port()));
    });
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}