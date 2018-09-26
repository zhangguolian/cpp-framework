#include <sql/mysql.h>

#include <iostream>
#include <logs/logs.hpp>

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
        LOG_ERROR("Mysql::Init mysql repeat init.");
        return false;
    }

    mysql_ = new MYSQL();
    if (mysql_init(mysql_) == NULL) {
        LOG_ERROR("Mysql::Init mysql_init fail.");
        return false;
    }

    if (mysql_real_connect(mysql_, db_host.c_str(), db_user.c_str(),
        db_pass.c_str(), db_name.c_str(), db_port, NULL, 0) == NULL) {
        LOG_ERROR("Mysql::Init mysql_real_connect fail.");
        return false;
    }

    return true;
}
bool Mysql::Exec(const std::string& sql) {
    if (mysql_query(mysql_, sql.c_str())) {
        LOG_ERROR("Mysql::Exec mysql_query fail, error:%s.", mysql_error(mysql_));
        return false;
    }

    return true;
}
bool Mysql::QueryRow(const std::string& sql,
                     SQL_ROW& row) {
    bool is_success = false;

    if (mysql_query(mysql_, sql.c_str())) {
        LOG_ERROR("Mysql::QueryRow mysql_query fail, error:%s.", mysql_error(mysql_));
        return false;
    }

    MYSQL_RES* result = NULL;
    result = mysql_store_result(mysql_);

    if (mysql_num_rows(result) == 0) {
        goto exit;
    }

    {
        int field_count = mysql_num_fields(result);
        MYSQL_ROW mysql_row = NULL;
        mysql_row = mysql_fetch_row(result);
        if (mysql_row == NULL) {
            LOG_ERROR("Mysql::QueryRow mysql_fetch_row fail.");
            goto exit;
        }

        for (int i = 0; i < field_count; i++) {
            MYSQL_FIELD* field = NULL;
            field = mysql_fetch_field_direct(result, i);
            if (field == NULL) {
                continue;
            }

            row[field->name] = mysql_row[i];
        }
    }

    is_success = true;

exit:
    if (result != NULL) {
        mysql_free_result(result);
    }

    return is_success;
}
bool Mysql::QueryRows(const std::string& sql,
                      SQL_ROWS& rows) {
    bool is_success = false;

    if (mysql_query(mysql_, sql.c_str())) {
        LOG_ERROR("Mysql::QueryRow mysql_query fail, error:%s.", mysql_error(mysql_));
        return false;
    }

    MYSQL_RES* result = NULL;
    result = mysql_store_result(mysql_);

    if (mysql_num_rows(result) == 0) {
        goto exit;
    }

    {
        int field_count = mysql_num_fields(result);
        MYSQL_ROW mysql_row = NULL;
        mysql_row = mysql_fetch_row(result);
        if (mysql_row == NULL) {
            LOG_ERROR("Mysql::QueryRow mysql_fetch_row fail.");
            goto exit;
        }

        while (NULL != mysql_row) {
            SQL_ROW row;
            for(int i = 0; i < field_count; i++) {
                MYSQL_FIELD* field = NULL;
                field = mysql_fetch_field_direct(result, i);
                if (field == NULL) {
                    continue;
                }

                row[field->name] = mysql_row[i];
            }

            rows.push_back(row); 
            mysql_row = mysql_fetch_row(result);
        }
    }
              
    is_success = true;

exit:
    if (result != NULL) {
        mysql_free_result(result);
    }

    return is_success;
}

}