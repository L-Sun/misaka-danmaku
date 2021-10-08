#pragma once
#include <misaka/net/server.hpp>
#include <misaka/core/route_table.hpp>

#include <spdlog/logger.h>

#include <memory>
#include <variant>

namespace misaka::core {
class KadEngine {
public:
    KadEngine(std::shared_ptr<net::Server> server);

    inline asio::awaitable<bool> ConnectToNetwork(std::string_view address, uint16_t port) {
        net::Endpoint remote(asio::ip::make_address(address), port);
        co_return co_await ConnectToNetwork(remote);
    }

    asio::awaitable<bool> ConnectToNetwork(const net::Endpoint& endpoint);
    asio::awaitable<bool> Store(std::string_view key, std::string_view value);

private:
    asio::awaitable<void> FindMe(const net::Endpoint& seed);

    PingResponse      HandlePingRequest(const PingRequest& request);
    StoreResponse     HandleStoreRequest(const StoreRequest& request);
    FindNodeResponse  HandleFindNodeRequest(const FindNodeRequest& request);
    FindValueResponse HandleFindValueRequest(const FindValueRequest& request);

    Request  WrapRequest(std::variant<PingRequest, StoreRequest, FindNodeRequest, FindValueRequest> request);
    Response WrapResponse(std::variant<PingResponse, StoreResponse, FindNodeResponse, FindValueResponse> response);

    RouteTable<net::Endpoint>    m_RouteTable;
    std::shared_ptr<net::Server> m_Server;

    std::shared_ptr<spdlog::logger> m_Logger;
};

}  // namespace misaka::core