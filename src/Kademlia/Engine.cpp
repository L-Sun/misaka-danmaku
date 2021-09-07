#include "Engine.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <fmt/format.h>

template <class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

namespace Misaka::Kademlia {

using namespace std::chrono_literals;

Engine::Engine(std::shared_ptr<Network::Server> server)
    : m_RouteTable(random_bitset<IDsize>()),
      m_Server(server),
      m_Logger(spdlog::stdout_color_st(fmt::format("Engine[{}]", m_RouteTable.GetID().to_string()))) {
    m_Server->SetRequestProcessor(
        [&](const Network::Context& context) -> Response {
            auto [request, remote] = context;
            // TODO black list may be used in here for those abused requests

            m_RouteTable.Add(ID(request.originid()), remote);

            switch (request.request_case()) {
                case Request::RequestCase::kPing:
                    return WrapResponse(HandlePingRequest(request.ping()));
                /* 
                 TODO uncomment after impletement this member function
                case Request::RequestCase::kStore:
                    return WrapResponse(HandleStoreRequest(request.store()));
                case Request::RequestCase::kFindNode:
                    return WrapResponse(HandleFindNodeRequest(request.findnode()));
                case Request::RequestCase::kFindValue:
                    return WrapResponse(HandleFindValueRequest(request.findvalue()));
                */
                default:
                    m_Logger->warn("unkown request case, return default response");
                    return {};
            }
        });

    m_Server->Listen();
}

asio::awaitable<bool> Engine::ConnectToNetwork(std::string_view address, uint16_t port) {
    Network::Endpoint remote(asio::ip::make_address(address), port);

    Request ping_request;
    ping_request.mutable_ping();
    auto response = co_await m_Server->Send(ping_request, remote);

    if (!response.has_value())
        co_return false;

    if (!response->has_ping()) {
        m_Logger->warn("Recive a unexpect message from remote {}:{}", address, port);
        co_return false;
    }

    m_RouteTable.Add(ID(response->originid()), remote);

    co_return true;
}

// TODO call FindNode to find myself, and then populate the route table
void Engine::FindMe() {
}

PingResponse Engine::HandlePingRequest(const PingRequest& request) {
    PingResponse result;
    result.set_state(PingResponse_State::PingResponse_State_RUNNING);
    return result;
}

FindNodeResponse Engine::HandleFindNodeRequest(const FindNodeRequest& request) {
    FindNodeResponse result;

    for (auto&& [id, endpoint] : m_RouteTable.GetBucket(ID(request.id()))) {
        auto node = result.add_nodes();
        node->set_id(id.to_string());
        node->set_address(endpoint.address().to_string());
        node->set_port(endpoint.port());
    }

    return result;
}

Request Engine::WrapRequest(std::variant<PingRequest, StoreRequest, FindNodeRequest, FindValueRequest> request) {
    Request result;
    result.set_originid(m_RouteTable.GetID().to_string());
    std::visit(overloaded{
                   [&](PingRequest&& request) {
                       (*result.mutable_ping()) = std::move(request);
                   },
                   [&](StoreRequest&& request) {
                       (*result.mutable_store()) = std::move(request);
                   },
                   [&](FindNodeRequest&& request) {
                       (*result.mutable_findnode()) = std::move(request);
                   },
                   [&](FindValueRequest&& request) {
                       (*result.mutable_findvalue()) = std::move(request);
                   }},
               std::move(request));

    return result;
}

Response Engine::WrapResponse(std::variant<PingResponse, StoreResponse, FindNodeResponse, FindValueResponse> response) {
    Response result;
    result.set_originid(m_RouteTable.GetID().to_string());
    std::visit(overloaded{
                   [&](PingResponse&& response) {
                       (*result.mutable_ping()) = std::move(response);
                   },
                   [&](StoreResponse&& response) {
                       (*result.mutable_store()) = std::move(response);
                   },
                   [&](FindNodeResponse&& response) {
                       (*result.mutable_findnode()) = std::move(response);
                   },
                   [&](FindValueResponse&& response) {
                       (*result.mutable_findvalue()) = std::move(response);
                   }},
               std::move(response));

    return result;
}

}  // namespace Misaka::Kademlia