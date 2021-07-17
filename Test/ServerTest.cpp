#include "Server.hpp"

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

#include <gtest/gtest.h>

#include <list>

using namespace Misaka::Network;
using namespace std::chrono_literals;

class ServerTest : public ::testing::Test {
protected:
    ServerTest()
        : io_context(1),
          offline_endpoint(asio::ip::make_address("127.0.0.2"), 62312) {}
    ~ServerTest() {
        io_context.run();
    }

    UdpServer& create_server_for_test() {
        thread_local uint16_t port   = 4000;
        auto&                 server = servers.emplace_back(io_context, "127.0.0.1", port++);
        asio::co_spawn(io_context, server.Listen(), asio::detached);
        return server;
    }

    template <typename F>
    void co_test(F&& func) {
        asio::co_spawn(
            io_context, [&]() -> asio::awaitable<void> {
                co_await func();
                io_context.stop();
            },
            asio::detached);
    }

    asio::ip::udp::endpoint offline_endpoint;
    asio::io_context        io_context;
    std::list<UdpServer>    servers;
};

TEST_F(ServerTest, MessageTest) {
    co_test([&]() -> asio::awaitable<void> {
        auto& s1 = create_server_for_test();
        auto& s2 = create_server_for_test();

        s1.SetRequestProcessor([](Request req, asio::ip::udp::endpoint) -> Response {
            Response res;
            res.mutable_ping()->set_state(PingResponse_State_RUNNING);
            return res;
        });

        Request req;
        auto    res = co_await s2.Send(req, s1.Endpoint());
        EXPECT_TRUE(res.has_value()) << "must have response if send a message to online client";

        res = co_await s2.Send(req, offline_endpoint, 1s);
        EXPECT_FALSE(res.has_value()) << "it should not have response if the remote is offline.";
    });
}

int main(int argc, char** argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};