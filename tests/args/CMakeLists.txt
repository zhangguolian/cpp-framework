file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(args_test ${sources} ${headers})

target_link_libraries(args_test args)