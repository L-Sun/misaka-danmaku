add_library(Core Core.cpp)
target_link_libraries(Core PRIVATE Kademlia spdlog::spdlog)
target_include_directories(Core
    INTERFACE 
        "$<TARGET_PROPERTY:Kademlia,INTERFACE_INCLUDE_DIRECTORIES>"
        ${CMAKE_CURRENT_SOURCE_DIR}
)