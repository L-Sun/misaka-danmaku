#include <misaka/core/kademlia_engine.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <fmt/format.h>

#include <queue>

template <class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

namespace misaka::core {

using namespace std::chrono_literals;

KadEngine::KadEngine(std::shared_ptr<net::Server> server)
    : m_RouteTable(GenerateRandomID<IDsize>()),
      m_Server(server),
      m_Logger(spdlog::stdout_color_st(fmt::format("KadEngine[{}]", m_RouteTable.GetID().to_string()))) {
    m_Server->SetRequestProcessor(
        [&](const net::Context& context) -> Response {
            auto [request, remote] = context;
            // TODO black list may be used in here for those abused requests

            m_RouteTable.Add(KadID(request.originid()), remote);

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

asio::awaitable<bool> KadEngine::ConnectToNetwork(const net::Endpoint& remote) {
    Request ping_request;
    ping_request.mutable_ping();
    auto response = co_await m_Server->Send(ping_request, remote);

    if (!response.has_value())
        co_return false;

    if (!response->has_ping()) {
        m_Logger->warn("Recive a unexpect message from remote {}:{}", remote.address().to_string(), remote.port());
        co_return false;
    }

    co_await FindMe(remote);

    co_return true;
}

asio::awaitable<void> KadEngine::FindMe(const net::Endpoint& seed) {
    if (m_RouteTable.Full()) co_return;

    // waiting for sending message
    // TODO use unique container to decline unnecessary request
    std::queue<net::Endpoint> remote_queue;
    remote_queue.push(seed);

    // TODO use asio::experimental::parallel_group to speed up the population of route
    while (!(m_RouteTable.Full() || remote_queue.empty())) {
        auto remote = std::move(remote_queue.front());
        remote_queue.pop();

        FindNodeRequest request;
        request.set_id(m_RouteTable.GetID().to_string());
        auto result = co_await m_Server->Send(WrapRequest(request), remote);

        if (!result.has_value()) continue;

        KadID remote_id(result->originid());

        if (!result->has_findnode()) {
            m_Logger->warn("ReUnexpected message from remote[{}]", remote_id.to_string());
            continue;
        }

        if (m_RouteTable.Has(remote_id)) continue;

        // We add this node after checking if there is a correct response,
        // because remote endpoint may has a incorrect implementatio of kademlia engine or orther reasons.
        m_RouteTable.Add(std::move(remote_id), remote);

        // TODO use the k good quality nodes, avoid long watting.
        for (auto&& node : result->findnode().nodes()) {
            remote_queue.push(
                net::Endpoint{asio::ip::make_address(node.address()),
                              static_cast<uint16_t>(node.port())});
        }
    }
}

PingResponse KadEngine::HandlePingRequest(const PingRequest& request) {
    PingResponse result;
    result.set_state(PingResponse_State::PingResponse_State_RUNNING);
    return result;
}

FindNodeResponse KadEngine::HandleFindNodeRequest(const FindNodeRequest& request) {
    FindNodeResponse result;

    for (auto&& [id, endpoint] : m_RouteTable.GetBucket(KadID(request.id()))) {
        auto node = result.add_nodes();
        node->set_id(id.to_string());
        node->set_address(endpoint.address().to_string());
        node->set_port(endpoint.port());
    }

    return result;
}

Request KadEngine::WrapRequest(std::variant<PingRequest, StoreRequest, FindNodeRequest, FindValueRequest> request) {
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

Response KadEngine::WrapResponse(std::variant<PingResponse, StoreResponse, FindNodeResponse, FindValueResponse> response) {
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

}  // namespace misaka::core