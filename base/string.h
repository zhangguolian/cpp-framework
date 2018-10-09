#pragma once 

#include <string>
#include <map>

namespace base {

std::string StringPrintf(const char* format,  ...);
int StringToInt(const std::string& data);
int64_t StringToInt64(const std::string& data);
uint StringToUInt(const std::string& data);
uint64_t StringToUInt64(const std::string& data);
float StringToFloat(const std::string& data);
double StringToDouble(const std::string& data);
bool StringToBool(const std::string& data);

};