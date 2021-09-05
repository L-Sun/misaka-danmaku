add_library(Kademlia KademliaServer.cpp)
target_link_libraries(Kademlia PRIVATE Server asio::asio spdlog::spdlog fmt::fmt)
target_include_directories(Kademlia
    INTERFACE
        "$<TARGET_PROPERTY:Server,INTERFACE_INCLUDE_DIRECTORIES>"
        ${CMAKE_CURRENT_SOURCE_DIR}
)

