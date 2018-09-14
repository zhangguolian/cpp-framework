#pragma once 

#include <string>
#include <map>

namespace utils {

std::string Map2UrlQuery(const std::map<std::string, std::string> params);
std::string StringPrintf(const char* format,  ...);
int StringToInt(const std::string& str_value);
int64_t StringToInt64(const std::string& str_value);

std::string GetDate();

};