file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(reflect ${sources} ${headers})

install(FILES 
        ${PROJECT_SOURCE_DIR}/reflect/reflect.h
        ${PROJECT_SOURCE_DIR}/reflect/member.hpp
        DESTINATION /usr/local/include/reflect/)