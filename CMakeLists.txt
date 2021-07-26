cmake_minimum_required(VERSION 3.20)
project(MisakaDanmaku VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
include(CTest)
enable_testing()

find_package(asio CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(Test)

add_executable(echo_server server.cpp)
target_link_libraries(echo_server PRIVATE asio)

add_executable(client client.cpp)
target_link_libraries(client PRIVATE asio)

add_executable(playground playground.cpp)
target_link_libraries(playground PRIVATE asio spdlog::spdlog)