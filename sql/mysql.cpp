#include <sql/mysql.h>

#include <iostream>


namespace sql {

Mysql::Mysql() : mysql_(NULL) {

}
Mysql::~Mysql() {
    if (mysql_ != NULL) {
        mysql_close(mysql_);
        delete mysql_;
        mysql_ = NULL;
    }
}

bool Mysql::Init(int db_port,
                 const std::string& db_host,
                 const std::string& db_user,
                 const std::string& db_pass,
                 const std::string& db_name) {
    if (mysql_ != NULL) {
        printf("Mysql::Init mysql repeat init\n");
        return false;
    }

    if (mysql_init(mysql_) == NULL) {
        printf("Mysql::Init mysql_init fail\n");
        return false;
    }

    if (mysql_real_connect(mysql_, db_host.c_str(), db_user.c_str(),
        db_pass.c_str(), db_name.c_str(), db_port, NULL, 0) == NULL) {
        printf("Mysql::Init mysql_real_connect fail\n");
        return false;
    }

    return true;
}
bool Mysql::Exec(const std::string& sql) {
    if (mysql_query(mysql_, sql.c_str())) {
        printf("Mysql::Exec mysql_query fail, error:%s\n", mysql_error(mysql_));
        return false;
    }

    return true;
}
bool Mysql::QueryRow(const std::string& sql,
                     SQL_ROW& row) {
    if (mysql_query(mysql_, sql.c_str())) {
        printf("Mysql::QueryRow mysql_query fail, error:%s\n", mysql_error(mysql_));
        return false;
    }

    MYSQL_RES* result = NULL;
    result = mysql_store_result(mysql_);

    if (mysql_num_rows(result) == 0) {
        printf("Mysql::QueryRow mysql_num_rows is 0\n");
        return false;
    }

    int field_count = mysql_num_fields(result);
    MYSQL_ROW mysql_row = NULL;
    mysql_row = mysql_fetch_row(result);
    if (mysql_row == NULL) {
        printf("Mysql::QueryRow mysql_fetch_row fail\n");
        return false;
    }

    for (int i = 0; i < field_count; i++) {
        MYSQL_FIELD* field = NULL;
        field = mysql_fetch_field_direct(result, i);
        if (field == NULL) {
            continue;
        }

        row[field->name] = mysql_row[i];
    }

    mysql_free_result(result);

    return true;
}
bool Mysql::QueryRows(const std::string& sql,
                      SQL_ROWS& rows) {
    return true;
}

}