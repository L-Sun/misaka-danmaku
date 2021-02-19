cmake_minimum_required(VERSION 3.15.0)
project(MisakaDanmuku VERSION 0.1.0)

set(cm)

include(CTest)
enable_testing()

add_executable(MisakaDanmuku main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
