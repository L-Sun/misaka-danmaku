add_library(kademlia kademlia_engine.cpp)
target_link_libraries(kademlia PRIVATE server asio::asio spdlog::spdlog fmt::fmt)
target_include_directories(kademlia
    PUBLIC
        "$<TARGET_PROPERTY:server,INTERFACE_INCLUDE_DIRECTORIES>"
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

