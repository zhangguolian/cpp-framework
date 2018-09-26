file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(errors ${sources} ${headers})

install(FILES 
        ${PROJECT_SOURCE_DIR}/errors/errors.h
        DESTINATION /usr/local/include/errors/)
install(TARGETS errors ARCHIVE DESTINATION /usr/local/lib/)