file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(bind_test ${sources} ${headers})

target_link_libraries(bind_test ${Boost_LIBRARIES})