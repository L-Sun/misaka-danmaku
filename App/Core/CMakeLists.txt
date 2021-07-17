add_library(Core Core.cpp)
target_link_libraries(Core PRIVATE Server spdlog::spdlog)
target_include_directories(Core
    INTERFACE 
        "$<TARGET_PROPERTY:Server,INTERFACE_INCLUDE_DIRECTORIES>"
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(Server Server.cpp)
target_link_libraries(Server PUBLIC Kademlia KadProtocol PRIVATE spdlog::spdlog)
target_include_directories(Server 
    INTERFACE
        "$<TARGET_PROPERTY:spdlog::spdlog,INTERFACE_INCLUDE_DIRECTORIES>"
        ${CMAKE_CURRENT_SOURCE_DIR}
)