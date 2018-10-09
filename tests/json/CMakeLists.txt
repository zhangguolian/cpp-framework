file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(json_test ${sources} ${headers})

target_link_libraries(json_test reflect jsoncpp)