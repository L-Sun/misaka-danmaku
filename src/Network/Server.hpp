#pragma once
#include "kademlia.pb.h"
#include "Carrier.hpp"

#include <asio/awaitable.hpp>
#include <asio/ip/udp.hpp>

#include <chrono>

namespace Misaka::Network {

using Endpoint = asio::ip::udp::endpoint;
using Context  = std::tuple<Request, Endpoint>;

class Server {
public:
    virtual void Listen()     = 0;
    virtual void StopListen() = 0;

    // use processor to handle recived request
    virtual void                                     SetRequestProcessor(std::function<Response(const Context&)> processor) = 0;
    virtual asio::awaitable<std::optional<Response>> Send(Request              request,
                                                          const Endpoint&      remote,
                                                          std::chrono::seconds timeout = std::chrono::seconds(3))           = 0;
};
}  // namespace Misaka::Network