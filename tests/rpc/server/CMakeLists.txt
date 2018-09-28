file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(rpc_server_test 
    ${rpc_test_sources} ${rpc_test_headers}    
    ${sources} ${headers})

target_link_libraries(rpc_server_test rpc protobuf jsoncpp)
