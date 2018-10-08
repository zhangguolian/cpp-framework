file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(sql ${sources} ${headers})

target_link_libraries(sql base mysqlclient)

install(FILES 
        ${PROJECT_SOURCE_DIR}/sql/sql.h
        ${PROJECT_SOURCE_DIR}/sql/sql_base.h
        ${PROJECT_SOURCE_DIR}/sql/mysql.h
        DESTINATION /usr/local/include/sql/)
install(TARGETS sql ARCHIVE DESTINATION /usr/local/lib/)