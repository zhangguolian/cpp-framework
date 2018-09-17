file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(http ${sources} ${headers})

target_link_libraries(http base curl ${Boost_LIBRARIES})

install(FILES 
        ${PROJECT_SOURCE_DIR}/http/http.h
        ${PROJECT_SOURCE_DIR}/http/http_buffer.h
        ${PROJECT_SOURCE_DIR}/http/http_request.h
        ${PROJECT_SOURCE_DIR}/http/http_manager.h 
        DESTINATION /usr/local/include/http/)
install(TARGETS http ARCHIVE DESTINATION /usr/local/lib/)