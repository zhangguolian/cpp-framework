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

#pragma once 

#include <iostream>
#include <string>

inline bool is_debug() {
#ifdef DEBUG
    return true;
#endif
    return false;    
}

#define LOG(type, format, ...)\
    {\
    time_t tt = time(NULL);\
    tm* t= localtime(&tt);\
    printf("%d-%02d-%02d %02d:%02d:%02d ",\
        t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);\
    printf("[%s] [%s:%d]:", #type, __FUNCTION__, __LINE__);\
    printf(format, ##__VA_ARGS__);\
    printf("\n");\
    fflush(stdout);\
    }

#define LOG_DEBUG(format, ...)\
    if (is_debug()) {\
        LOG(debug, format, ##__VA_ARGS__);\
    }   

#define LOG_INFO(format, ...)\
    LOG(info, format, ##__VA_ARGS__)

#define LOG_ERROR(format, ...)\
    LOG(error, format, ##__VA_ARGS__)


