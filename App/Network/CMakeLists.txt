add_library(Server Server.cpp)
target_link_libraries(Server PUBLIC KadProtocol PRIVATE spdlog::spdlog)
target_include_directories(Server 
    INTERFACE
        "$<TARGET_PROPERTY:spdlog::spdlog,INTERFACE_INCLUDE_DIRECTORIES>"
        ${CMAKE_CURRENT_SOURCE_DIR}
)