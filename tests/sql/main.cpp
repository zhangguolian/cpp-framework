
#include <iostream>
#include <sql/sql.h>
#include <logs/logs.hpp>

int main()
{
    sql::SqlBase* sql = new sql::Mysql();
    sql->Init(3306, "localhost", "root", "root", "exchange_server");
    LOG_INFO("QueryRow.");
    sql::SQL_ROW row;
    if (!sql->QueryRow("select * from adver_info", row)) {
        LOG_ERROR("sql->QueryRow fail.");
        return -1;
    }

    for (auto iter = row.begin(); iter != row.end(); iter++) {
        LOG_INFO("name:%s, value:%s.", iter->first.c_str(), iter->second.c_str());
    } 

    LOG_INFO("QueryRows.");
    sql::SQL_ROWS rows;
    if (!sql->QueryRows("select * from adver_info", rows)) {
        LOG_ERROR("sql->QueryRows fail.");
        return -1;
    }

    for (size_t i = 0; i < rows.size(); i++) {
        for (auto iter = rows[i].begin(); iter != rows[i].end(); iter++) {
            LOG_INFO("name:%s, value:%s.", iter->first.c_str(), iter->second.c_str());
        } 
    }

    return 0;
}
