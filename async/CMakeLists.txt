file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(async ${sources} ${headers})

target_link_libraries(async)

install(FILES 
        ${PROJECT_SOURCE_DIR}/async/async.h
        ${PROJECT_SOURCE_DIR}/async/thread.h
        ${PROJECT_SOURCE_DIR}/async/timer.h 
        DESTINATION /usr/local/include/async/)
install(TARGETS async ARCHIVE DESTINATION /usr/local/lib/)