add_executable(KademliaTest KademliaTest.cpp)
target_link_libraries(KademliaTest PRIVATE Kademlia GTest::gtest)
add_test(KademliaTest KademliaTest)

add_executable(ServerTest ServerTest.cpp)
target_link_libraries(ServerTest PRIVATE Server GTest::gtest)
add_test(ServerTest ServerTest)

add_executable(CoreTest CoreTest.cpp)
target_link_libraries(CoreTest PRIVATE Core GTest::gtest)
add_test(CoreTest CoreTest)