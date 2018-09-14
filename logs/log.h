#pragma once 

#include <iostream>
#include <utils/utils.h>

#define LOG(type, format, ...)\
    printf("%s [%s] [%s:%d]:", utils::GetDate().c_str(), #type, __FUNCTION__, __LINE__);\
    printf(format, __VA_ARGS__);

#define LOG_DEBUG(format, ...)\
    LOG(debug, format, __VA_ARGS__)

#define LOG_INFO(format, ...)\
    LOG(info, format, __VA_ARGS__)

#define LOG_ERROR(format, ...)\
    LOG(error, format, __VA_ARGS__)


