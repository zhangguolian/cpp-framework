file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(utils_test ${sources} ${headers})

target_link_libraries(utils_test utils)