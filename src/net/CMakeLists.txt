add_library(server udp_server.cpp)
target_link_libraries(server PUBLIC protocol utils PRIVATE asio::asio spdlog::spdlog fmt::fmt)
target_include_directories(server 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    INTERFACE
        "$<TARGET_PROPERTY:spdlog::spdlog,INTERFACE_INCLUDE_DIRECTORIES>"
)