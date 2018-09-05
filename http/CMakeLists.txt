file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(http ${sources} ${headers})

target_link_libraries(http utils curl ${Boost_LIBRARIES})