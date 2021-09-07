add_library(Server UdpServer.cpp)
target_link_libraries(Server PUBLIC KadProtocol PRIVATE asio::asio spdlog::spdlog fmt::fmt)
target_include_directories(Server 
    INTERFACE
        "$<TARGET_PROPERTY:spdlog::spdlog,INTERFACE_INCLUDE_DIRECTORIES>"
        ${CMAKE_CURRENT_SOURCE_DIR}
)