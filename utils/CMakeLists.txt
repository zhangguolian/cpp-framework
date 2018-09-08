file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(utils ${sources} ${headers})

target_link_libraries(utils)

install(FILES 
        ${PROJECT_SOURCE_DIR}/utils/utils.h
        ${PROJECT_SOURCE_DIR}/utils/string.h
        DESTINATION /usr/local/include/utils/)
install(TARGETS utils ARCHIVE DESTINATION /usr/local/lib/)