#pragma once
#include "Peer.hpp"
#include "Server.hpp"

#include <spdlog/logger.h>

#include <memory>

namespace Misaka {
class App {
public:
    App(Kademlia::ID id);

    void UpdateDanmuku();
    void Republish();

    void AddSeedPeer(const Peer& peer);

private:
    void Populate(const Peer& peer);

    std::shared_ptr<spdlog::logger> m_Logger;

    Kademlia::ID               m_Id;
    Kademlia::RouteTable<Peer> m_Table;

    std::unique_ptr<UdpServerBase> m_Server;
};

}  // namespace Misaka