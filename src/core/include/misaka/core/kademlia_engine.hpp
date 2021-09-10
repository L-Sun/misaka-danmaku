#pragma once
#include <misaka/net/server.hpp>
#include <misaka/core/route_table.hpp>

#include <spdlog/logger.h>

#include <memory>
#include <variant>

namespace misaka::core {
class KadEngine {
public:
    KadEngine(std::shared_ptr<Network::Server> server);

    asio::awaitable<bool> ConnectToNetwork(std::string_view address, uint16_t port);

private:
    void FindMe();

    PingResponse      HandlePingRequest(const PingRequest& request);
    StoreResponse     HandleStoreRequest(const StoreRequest& request);
    FindNodeResponse  HandleFindNodeRequest(const FindNodeRequest& request);
    FindValueResponse HandleFindValueRequest(const FindValueRequest& request);

    Request  WrapRequest(std::variant<PingRequest, StoreRequest, FindNodeRequest, FindValueRequest> request);
    Response WrapResponse(std::variant<PingResponse, StoreResponse, FindNodeResponse, FindValueResponse> response);

    RouteTable<Network::Endpoint>    m_RouteTable;
    std::shared_ptr<Network::Server> m_Server;

    std::shared_ptr<spdlog::logger> m_Logger;
};

}  // namespace misaka::core