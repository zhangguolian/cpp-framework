file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(sql_test ${sources} ${headers})

target_link_libraries(sql_test sql)