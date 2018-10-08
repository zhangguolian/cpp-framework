
#include <iostream>
#include <sql/sql.h>
#include <logs/logs.hpp>
#include <reflect/reflect.hpp>

struct AdverInfo {
    AdverInfo() {
        REFLECT_REGIST(AdverInfo, this, int64_t, id, &id);
        REFLECT_REGIST(AdverInfo, this, std::string, adver_name, &adver_name);
        REFLECT_REGIST(AdverInfo, this, std::string, adver_url, &adver_url);
        REFLECT_REGIST(AdverInfo, this, int, type, &type);
    }
    ~AdverInfo() {
        REFLECT_UNREGIST(AdverInfo, this);
    }

    int64_t id;
    std::string adver_name;
    std::string adver_url;
    int type;
};

int main()
{
    sql::SqlBase* sql = new sql::Mysql();
    sql->Init(3306, "localhost", "root", "root", "exchange_server");
    LOG_INFO("QueryRow.");
    AdverInfo adver_info;
    if (!sql->QueryRow("select * from adver_info", adver_info)) {
        LOG_ERROR("sql->QueryRow fail.");
        return -1;
    }

    LOG_INFO("%ld, %s, %s, %d.", adver_info.id, adver_info.adver_name.c_str(),
        adver_info.adver_url.c_str(), adver_info.type);

    LOG_INFO("QueryRows.");
    std::vector<AdverInfo> adver_info_list;
    if (!sql->QueryRows("select * from adver_info", adver_info_list)) {
        LOG_ERROR("sql->QueryRows fail.");
        return -1;
    }

    for (size_t i = 0; i < adver_info_list.size(); i++) {
        LOG_INFO("%ld, %s, %s, %d.", adver_info_list[i].id, adver_info_list[i].adver_name.c_str(),
            adver_info_list[i].adver_url.c_str(), adver_info_list[i].type);
    }

    return 0;
}
