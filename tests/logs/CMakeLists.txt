file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(logs_test ${sources} ${headers})

target_link_libraries(logs_test utils)
