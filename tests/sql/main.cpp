
#include <iostream>
#include <sql/sql.h>

 
int main()
{
    sql::SqlBase* sql = new sql::Mysql();
    sql->Init(3306, "localhost", "root", "root", "exchange_server");
    sql::SqlBase::SQL_ROW row;
    sql->QueryRow("select * from adver_info", row);
    for (auto iter = row.begin(); iter != row.end(); iter++) {
        printf("name:%s, value:%s\n", iter->first.c_str(), iter->second.c_str());
    } 
     
    return 0;
}
