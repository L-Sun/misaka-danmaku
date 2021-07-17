#pragma once
#include "Server.hpp"

namespace Misaka::Kademlia {
class KademliaServer : private Network::Server {
public:
    KademliaServer();
    ~KademliaServer();

private:
};

}  // namespace Misaka::Kademlia