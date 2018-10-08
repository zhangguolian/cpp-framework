file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(reflect_test ${sources} ${headers})