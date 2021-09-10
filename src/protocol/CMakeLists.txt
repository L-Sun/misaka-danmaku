add_library(protocol)
target_link_libraries(protocol PUBLIC protobuf::libprotobuf)
target_include_directories(protocol 
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

protobuf_generate(
    LANGUAGE cpp
    TARGET protocol
    PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/misaka/protocol
    IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    PROTOS
        kademlia.proto
        request.proto
        response.proto
)