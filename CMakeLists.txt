cmake_minimum_required(VERSION 3.20)
project(MisakaDanmuku VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
include(CTest)
enable_testing()

find_package(cppcoro CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_subdirectory(KadProtocol)
add_subdirectory(App)
add_subdirectory(Test)

