#include "Server.hpp"

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

#include <gtest/gtest.h>

using namespace Misaka;

Misaka::UdpServer create_server_for_test(asio::io_context& io_context) {
    thread_local uint16_t port = 4000;
    return Misaka::UdpServer(io_context, "127.0.0.1", port++);
}

TEST(ServerTest, MessageTest) {
    auto handle_store = [&](const StoreRequest& request) -> StoreResponse {
        std::cout << "[STORE] Key: {" << request.key() << "} Value: {" << request.value() << "}" << std::endl;
        StoreResponse response;
        response.set_state(StoreResponse_State::StoreResponse_State_SUCCESS);
        return response;
    };

    auto handle_find_node = [&](const FindNodeRequest& request) -> FindNodeResponse {
        FindNodeResponse response;
        auto             node_info = response.add_nodes();
        node_info->set_id(request.id());
        node_info->set_address("127.0.0.1");
        node_info->set_port(6000);
        return response;
    };

    auto handle_find_value = [&](const FindValueRequest& request) -> FindValueResponse {
        FindValueResponse response;
        auto              data = response.add_data();
        data->set_key("Name");
        data->set_value("Haowen");
        return response;
    };

    asio::io_context io_context(1);
    auto             remote = create_server_for_test(io_context);

    remote.SetRequestProcessor(
        [&](const Request& request) {
            Response response;
            switch (request.request_case()) {
                case Request::RequestCase::kStore: {
                    auto store_res = handle_store(request.store());
                    response.set_allocated_store(&store_res);
                } break;
                case Request::RequestCase::kFindNode: {
                    auto find_node_res = handle_find_node(request.findnode());
                    response.set_allocated_findnode(&find_node_res);
                } break;
                case Request::RequestCase::kFindValue: {
                    auto find_value_res = handle_find_value(request.findvalue());
                    response.set_allocated_findvalue(&find_value_res);
                } break;
                default:
                    break;
            }
            return response;
        });

    asio::co_spawn(io_context, remote.Listen(), asio::detached);

    auto server    = create_server_for_test(io_context);
    auto remote_id = remote.RouteTable().GetID();
    server.RouteTable().Add(remote.RouteTable().GetID(), remote.Endpoint());
    asio::co_spawn(io_context, server.Listen(), asio::detached);

    asio::co_spawn(
        io_context, [&]() -> asio::awaitable<void> {
            Request ping;
            ping.mutable_ping()->set__placeholder(1);
            auto response = co_await server.Send(ping, remote_id);
            if (response.has_value()) {
                EXPECT_EQ(response->ping().state(), PingResponse_State::PingResponse_State_RUNNING);
                io_context.stop();
            } else {
            }
        },
        asio::detached);

    io_context.run();
}

int main(int argc, char** argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};