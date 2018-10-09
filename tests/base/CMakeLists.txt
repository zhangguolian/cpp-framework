

add_executable(hash_test "hash.cpp")
target_link_libraries(hash_test base)

add_executable(json_test "json.cpp")
target_link_libraries(json_test base jsoncpp)

add_executable(rand_test "rand.cpp")
target_link_libraries(rand_test base)

add_executable(string_test "string.cpp")
target_link_libraries(string_test base)