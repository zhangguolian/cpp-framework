#include <utils/map.h>

namespace utils {

std::string Map2UrlQuery(const std::map<std::string, std::string> params) {
    std::string str_params = "";
    for (auto iter = params.begin(); iter != params.end(); iter++) {
        if (str_params == "") {
            str_params += iter->first + "=" + iter->second;
        } else {
            str_params += "&" + iter->first + "=" + iter->second;
        }
    }

    return str_params;
}

}