cmake_minimum_required(VERSION 3.21.0)
project(MisakaDanmaku VERSION 0.1.0)

if(MSVC)
    add_compile_options(/std:c++latest)
    add_compile_definitions(_WIN32_WINNT=_WIN32_WINNT_WIN10)
else()
    add_compile_options(-std=c++20)
endif()

include(CTest)
enable_testing()

find_package(asio CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(Test)