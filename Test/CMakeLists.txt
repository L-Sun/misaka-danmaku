include(GoogleTest)

add_library(TestUtils INTERFACE)
target_link_libraries(TestUtils INTERFACE asio::asio GTest::gtest)

add_executable(KademliaTest KademliaTest.cpp)
target_link_libraries(KademliaTest PRIVATE Kademlia TestUtils)
gtest_discover_tests(KademliaTest)

add_executable(ServerTest ServerTest.cpp)
target_link_libraries(ServerTest PRIVATE Server TestUtils)
gtest_discover_tests(ServerTest)

add_executable(CoreTest CoreTest.cpp)
target_link_libraries(CoreTest PRIVATE Core TestUtils)
gtest_discover_tests(CoreTest)