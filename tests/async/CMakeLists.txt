file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(async_test ${sources} ${headers})

target_link_libraries(async_test async ${Boost_LIBRARIES})