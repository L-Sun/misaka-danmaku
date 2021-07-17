#include "Core.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Misaka {
Core::Core(Kademlia::ID id)
    : m_IOContext(1),
      m_Server(m_ID, m_IOContext),
      m_Logger(spdlog::stdout_color_st("Core")) {
}

}  // namespace Misaka