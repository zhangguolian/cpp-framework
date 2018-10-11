/*
 *
 * Copyright 2018 Guolian Zhang.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <sql/sql.h>
#include <logs/logs.hpp>
#include <reflect/reflect.h>

struct AdverInfo {
    AdverInfo() {
        REFLECT_REGIST(this, int64_t, id);
        REFLECT_REGIST(this, std::string, adver_name);
        REFLECT_REGIST(this, std::string, adver_url);
        REFLECT_REGIST(this, int, type);
    }
    ~AdverInfo() {
        REFLECT_UNREGIST(this);
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
