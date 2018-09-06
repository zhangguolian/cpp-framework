file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(thread_test ${sources} ${headers})

target_link_libraries(thread_test thread ${Boost_LIBRARIES})