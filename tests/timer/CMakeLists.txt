file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(timer_test ${sources} ${headers})

target_link_libraries(timer_test ${Boost_LIBRARIES})