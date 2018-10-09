file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(httpex ${sources} ${headers})

target_link_libraries(httpex base curl ${Boost_LIBRARIES})

install(FILES 
        ${PROJECT_SOURCE_DIR}/httpex/http.h
        ${PROJECT_SOURCE_DIR}/httpex/http_request.h
        ${PROJECT_SOURCE_DIR}/httpex/http_manager.h 
        DESTINATION /usr/local/include/httpex/)
install(TARGETS httpex ARCHIVE DESTINATION /usr/local/lib/)