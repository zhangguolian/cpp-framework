file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(args ${sources} ${headers})

target_link_libraries(args ${Boost_LIBRARIES})

install(FILES 
        ${PROJECT_SOURCE_DIR}/args/args.h
        ${PROJECT_SOURCE_DIR}/args/args_parse.h
        DESTINATION /usr/local/include/args/)
install(TARGETS args ARCHIVE DESTINATION /usr/local/lib/)