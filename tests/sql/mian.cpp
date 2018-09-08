
#include <iostream>
#include <mysql/mysql.h>
 
using namespace std;
 
int main(int argc, char* argv[])
{
    MYSQL mysql;
    mysql_init( &mysql );
    mysql_real_connect(
        &mysql,
        "127.0.0.1",
        "root",
        "root",
        "exchange_server",
        3306,
        NULL,
        0  
    );
 
    string sql = "select * from adver_info";
    mysql_query( &mysql, sql.c_str() );
     
    MYSQL_RES *result = NULL;
    result = mysql_store_result( &mysql );
     
    //得到查询出来所有数据的条数
    int row_count = mysql_num_rows( result );
    cout << "all data number: " << row_count << endl;
 
    //得到字段的个数和字段的名字
    int field_count = mysql_num_fields( result );
    cout << "field count : " << field_count << endl;
 
    //得到所有字段的名字
    MYSQL_FIELD* field = NULL;
    for( int i = 0; i < field_count; ++i)
    {
        field = mysql_fetch_field_direct( result, i );
        cout << field->name << "\t";
    }
    cout << endl;
 
    //显示表中的所有数据
    MYSQL_ROW row = NULL;
    row = mysql_fetch_row( result );
    while ( NULL != row )
    {
        for( int i = 0; i < field_count; ++i)
        {
            cout << row[i] << "\t";
        }
        cout << endl;
 
        row = mysql_fetch_row( result );
    }
    
    mysql_free_result(result);
 
    mysql_close( &mysql );
     
    return 0;
}
