file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(sql ${sources} ${headers})

target_link_libraries(sql mysqlclient)