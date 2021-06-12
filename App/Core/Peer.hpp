#pragma once
#include "Kademlia.hpp"
#include <asio.hpp>

#include <optional>

namespace Misaka {
class Peer {
public:
    Peer(asio::ip::udp::endpoint endpoint) : m_Endpoint(std::move(endpoint)) {}

    std::optional<Kademlia::ID> GetID() const;
    std::vector<Peer>           FindNode(const Kademlia::ID& id) const;

private:
    asio::ip::udp::endpoint m_Endpoint;
};

}  // namespace Misaka