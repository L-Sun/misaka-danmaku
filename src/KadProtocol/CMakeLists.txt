add_library(KadProtocol)
target_link_libraries(KadProtocol PUBLIC protobuf::libprotobuf)
target_include_directories(KadProtocol INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/output)

protobuf_generate(
    LANGUAGE cpp
    TARGET KadProtocol
    PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output
    IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    PROTOS
        kademlia.proto
        request.proto
        response.proto
)