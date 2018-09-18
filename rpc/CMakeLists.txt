file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(rpc ${sources} ${headers})

target_link_libraries(rpc base grpc++)

install(FILES 
        ${PROJECT_SOURCE_DIR}/rpc/rpc.h
        ${PROJECT_SOURCE_DIR}/rpc/server.h
        DESTINATION /usr/local/include/rpc/)
install(TARGETS rpc ARCHIVE DESTINATION /usr/local/lib/)