file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(base ${sources} ${headers})

target_link_libraries(base crypto event)

install(FILES 
        ${PROJECT_SOURCE_DIR}/base/base.h
        ${PROJECT_SOURCE_DIR}/base/string.h
        ${PROJECT_SOURCE_DIR}/base/hash.h
        ${PROJECT_SOURCE_DIR}/base/rand.h
        DESTINATION /usr/local/include/base/)
install(TARGETS base ARCHIVE DESTINATION /usr/local/lib/)