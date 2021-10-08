#include "utils.hpp"

#include <misaka/net/udp_server.hpp>

#include <gtest/gtest.h>

#include <list>

using namespace misaka::net;
using namespace std::chrono_literals;

class ServerTest : public ::testing::Test {
protected:
    ServerTest()
        : io_context(1),
          offline_endpoint(asio::ip::make_address("127.0.0.2"), 62312) {}

    UdpServer& create_server_for_test() {
        thread_local uint16_t port   = 8000;
        auto&                 server = servers.emplace_back(io_context, "127.0.0.1", port++);
        server.Listen();
        return server;
    }

    Endpoint             offline_endpoint;
    asio::io_context     io_context;
    std::list<UdpServer> servers;
};

TEST_F(ServerTest, MessageTest) {
    co_test(io_context, [&]() -> asio::awaitable<void> {
        auto& s1 = create_server_for_test();
        auto& s2 = create_server_for_test();

        s1.SetRequestProcessor([](const Context& context) -> Response {
            Response res;
            res.mutable_ping()->set_state(PingResponse_State_RUNNING);
            return res;
        });

        Request req;
        auto    res = co_await s2.Send(req, s1.GetEndpoint());
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
