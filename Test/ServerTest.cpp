#include "Server.hpp"
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/when_all.hpp>
#include <gtest/gtest.h>

class ServerTest : public testing::Test {
protected:
    ServerTest() : server("127.0.0.1", 8000) {}
    Misaka::UdpServer server;

    static Misaka::UdpServer remote;
};

Misaka::UdpServer ServerTest::remote = Misaka::UdpServer("127.0.0.1", 6000);

TEST_F(ServerTest, MessageTest) {
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
        node_info->set_ipv4(cppcoro::net::ipv4_address::from_string("127.0.0.1")->to_integer());
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

    remote.SetHandleRequestProcessor(
        [&](const Request& request) {
            Response response;
            response.set_origin("Haowen");
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
        });

    cppcoro::sync_wait(cppcoro::when_all_ready(
        [&]() -> cppcoro::task<> {
            co_await remote.Listen();
        }(),
        [&]() -> cppcoro::task<> {
            EXPECT_EQ(co_await server.Ping(remote.GetEndpoint()), NodeState::RUNNING);

            remote.Stop();
        }()));
}

int main(int argc, char** argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};