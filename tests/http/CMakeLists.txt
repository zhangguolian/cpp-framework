file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(http_test ${sources} ${headers})

target_link_libraries(http_test http jsoncpp)