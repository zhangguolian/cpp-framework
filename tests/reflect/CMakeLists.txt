file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(reflect_test ${sources} ${headers})

target_link_libraries(reflect_test jsoncpp)