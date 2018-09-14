#pragma once 

#include <iostream>
#include <utils/utils.h>

bool is_debug() {
#ifdef DEBUG
    return true;
#endif
    return false;    
}

#define LOG(type, format, ...)\
    printf("%s [%s] [%s:%d]:", utils::GetDate().c_str(), #type, __FUNCTION__, __LINE__);\
    printf(format, __VA_ARGS__);

#define LOG_DEBUG(format, ...)\
    if (is_debug())\
        LOG(debug, format, __VA_ARGS__);

#define LOG_INFO(format, ...)\
    LOG(info, format, __VA_ARGS__)

#define LOG_ERROR(format, ...)\
    LOG(error, format, __VA_ARGS__)


