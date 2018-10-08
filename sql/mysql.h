#pragma once 

#include <sql/sql_base.h>
#include <mysql/mysql.h>

namespace sql {

class Mysql : public SqlBase {
public:
    Mysql();
    virtual ~Mysql();

    bool Init(int db_port,
              const std::string& db_host,
              const std::string& db_user,
              const std::string& db_pass,
              const std::string& db_name) override;
    bool Exec(const std::string& sql) override;

private:
    bool query_row(const std::string& sql,
                   SQL_ROW& row) override;
    bool query_rows(const std::string& sql,
                    SQL_ROWS& rows) override;

private:
    MYSQL* mysql_;
};

};