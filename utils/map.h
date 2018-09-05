#pragma once 

#include <string>
#include <map>

namespace utils {

std::string Map2UrlQuery(const std::map<std::string, std::string> params);

};