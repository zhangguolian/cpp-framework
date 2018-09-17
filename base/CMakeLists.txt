file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(base ${sources} ${headers})

target_link_libraries(base crypto)

install(FILES 
        ${PROJECT_SOURCE_DIR}/base/base.h
        ${PROJECT_SOURCE_DIR}/base/string.h
        ${PROJECT_SOURCE_DIR}/base/hash.h
        DESTINATION /usr/local/include/base/)
install(TARGETS base ARCHIVE DESTINATION /usr/local/lib/)