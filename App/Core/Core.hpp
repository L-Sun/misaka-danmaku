#pragma once
#include "Server.hpp"

#include <asio/io_context.hpp>
#include <spdlog/logger.h>

#include <memory>

namespace Misaka {
class Core {
public:
    Core();

    void ConnectToNetwork(std::string_view host);
    void PublishDamaku(std::string damaku);

private:
    Kademlia::ID     m_ID;
    asio::io_context m_IOContext;

    std::shared_ptr<spdlog::logger> m_Logger;
};

}  // namespace Misaka