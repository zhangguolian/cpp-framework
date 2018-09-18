file(GLOB rpc_test_sources "*.cpp")
file(GLOB rpc_test_headers "*.h")

add_subdirectory(server)
add_subdirectory(client)