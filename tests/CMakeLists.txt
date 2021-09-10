include(GoogleTest)

add_library(test_utils INTERFACE)
target_link_libraries(test_utils INTERFACE asio::asio GTest::gtest)

add_executable(utils_test utils_test.cpp)
target_link_libraries(utils_test PRIVATE server test_utils)
gtest_discover_tests(utils_test)

add_executable(kademlia_test kademlia_test.cpp)
target_link_libraries(kademlia_test PRIVATE kademlia test_utils)
gtest_discover_tests(kademlia_test)

add_executable(server_test server_test.cpp)
target_link_libraries(server_test PRIVATE server test_utils)
gtest_discover_tests(server_test)
