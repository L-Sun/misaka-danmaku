#include "Server.hpp"

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

#include <gtest/gtest.h>

#include <list>

using namespace Misaka;

class ServerTest : public ::testing::Test {
protected:
    ServerTest() : io_context(1) {}
    ~ServerTest() {
        io_context.run();
    }

    Misaka::UdpServer& create_server_for_test() {
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

    asio::io_context             io_context;
    std::list<Misaka::UdpServer> servers;
};

TEST_F(ServerTest, PingTest) {
    co_test([&]() -> asio::awaitable<void> {
        auto& s1 = create_server_for_test();
        auto& s2 = create_server_for_test();
        s2.RouteTable().Add(s1.RouteTable().GetID(), s1.Endpoint());

        s1.SetRequestProcessor([](const Request& req) -> Response {
            Response res;
            EXPECT_TRUE(req.has_ping());
            res.mutable_ping()->set_state(PingResponse_State::PingResponse_State_RUNNING);
            return res;
        });

        Request req;
        req.mutable_ping();
        auto res = co_await s2.Send(req, s1.RouteTable().GetID());
        if (!res.has_value()) {
            ADD_FAILURE() << "the ping request expect has value";
        } else
            EXPECT_TRUE(res->ping().state() == PingResponse_State::PingResponse_State_RUNNING);
    });
}

int main(int argc, char** argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};