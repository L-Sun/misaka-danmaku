#pragma once
#include "Server.hpp"
#include "RouteTable.hpp"

#include <variant>

namespace Misaka::Kademlia {
class KademliaEngine {
public:
    KademliaEngine(ID id, asio::io_context& io_context, std::string_view address, uint16_t port);

    asio::awaitable<bool> ConnectToNetwork(std::string_view address, uint16_t port);

private:
    PingResponse      HandlePingRequest(const PingRequest& req);
    StoreResponse     HandleStoreRequest(const StoreRequest& req);
    FindNodeResponse  HandleFindNodeRequest(const FindNodeRequest& req);
    FindValueResponse HandleFindValueRequest(const FindValueRequest& req);

    Request  WrapRequest(std::variant<PingRequest, StoreRequest, FindNodeRequest, FindValueRequest> request);
    Response WrapResponse(std::variant<PingResponse, StoreResponse, FindNodeResponse, FindValueResponse> response);

    RouteTable<Network::Endpoint> m_RouteTable;
    Network::UdpServer            m_Server;

    std::shared_ptr<spdlog::logger> m_Logger;
};

}  // namespace Misaka::Kademlia