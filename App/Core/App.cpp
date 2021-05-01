#include "App.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Misaka {
App::App(Kademlia::ID id)
    : m_Logger(spdlog::stdout_color_st("App")),
      m_Id(std::move(id)),
      m_Table(m_Id) {
    m_Server->SetRequestProcessor(
        [&](const PingRequest&) -> void {
            m_Logger->debug("PingRequest");
        },
        [&](const FindNodeRequest&) -> void {
            m_Logger->debug("FindNodeRequest");
        },
        [&](const StoreRequest&) -> void {
            m_Logger->debug("StoreRequest");
        },
        [&](const FindValueRequest&) -> void {
            m_Logger->debug("FindValueRequest");
        });
}

void App::AddSeedPeer(const Peer& peer) {
    // peer is online
    if (auto id = peer.GetID()) {
        m_Table.Add(std::move(*id), peer);
        Populate(peer);
    }
}

void App::Populate(const Peer& peer) {
    if (m_Table.Full()) return;

    for (auto&& _peer : peer.FindNode(m_Id)) {
        // peer is online
        if (auto id = _peer.GetID()) {
            m_Table.Add(std::move(*id), _peer);
            Populate(_peer);
        }
    }
}

}  // namespace Misaka