file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(thread ${sources} ${headers})

target_link_libraries(thread)