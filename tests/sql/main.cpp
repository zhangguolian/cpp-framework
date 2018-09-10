
#include <iostream>
#include <sql/sql.h>

 
int main()
{
    sql::SqlBase* sql = new sql::Mysql();
    sql->Init(3306, "localhost", "root", "root", "exchange_server");
    printf("QueryRow\n");
    sql::SQL_ROW row;
    if (!sql->QueryRow("select * from adver_info", row)) {
        printf("sql->QueryRow fail\n");
        return -1;
    }

    for (auto iter = row.begin(); iter != row.end(); iter++) {
        printf("name:%s, value:%s\n", iter->first.c_str(), iter->second.c_str());
    } 

    printf("QueryRows\n");
    sql::SQL_ROWS rows;
    if (!sql->QueryRows("select * from adver_info", rows)) {
        printf("sql->QueryRows fail\n");
        return -1;
    }

    for (int i = 0; i < rows.size(); i++) {
        printf("row:%d\n", i);
        for (auto iter = rows[i].begin(); iter != rows[i].end(); iter++) {
            printf("name:%s, value:%s\n", iter->first.c_str(), iter->second.c_str());
        } 
    }

    return 0;
}
