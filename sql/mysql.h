#pragma once 

#include <sql/sql_base.h>
#include <mysql/mysql.h>

namespace sql {

class Mysql : public SqlBase {
public:
    Mysql();
    ~Mysql();

    bool Init(int db_port,
              const std::string& db_host,
              const std::string& db_user,
              const std::string& db_pass,
              const std::string& db_name) override;
    bool Exec(const std::string& sql) override;
    bool QueryRow(const std::string& sql,
                  SQL_ROW& row) override;
    bool QueryRows(const std::string& sql,
                   SQL_ROWS& row) override;

private:
    MYSQL* mysql_;
};

};