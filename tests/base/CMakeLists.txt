file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(base_test ${sources} ${headers})

target_link_libraries(base_test base jsoncpp)