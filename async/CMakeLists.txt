file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(async ${sources} ${headers})

target_link_libraries(async)