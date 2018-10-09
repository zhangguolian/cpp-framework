file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(curl_test ${sources} ${headers})

target_link_libraries(curl_test curl async errors ${Boost_LIBRARIES})