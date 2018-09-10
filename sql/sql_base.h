#pragma once 

#include <map>
#include <string>
#include <vector>

namespace sql {

class SqlBase {
public:
    typedef std::map<std::string, std::string> SQL_ROW;
    typedef std::vector<std::map<std::string, std::string>> SQL_ROWS;

    virtual bool Init(int db_port,
                      const std::string& db_host,
                      const std::string& db_user,
                      const std::string& db_pass,
                      const std::string& db_name) = 0;
    virtual bool Exec(const std::string& sql) = 0;
    virtual bool QueryRow(const std::string& sql,
                          SQL_ROW& row) = 0;
    virtual bool QueryRows(const std::string& sql,
                           SQL_ROWS& row) = 0;
};

};