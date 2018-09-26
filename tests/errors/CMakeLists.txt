file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(errors_test ${sources} ${headers})

target_link_libraries(errors_test errors)