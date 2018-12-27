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

#include <base/cmd.h>
#include <logs/logs.hpp>

namespace base {

bool ExecuteCMD(const std::string& cmd, 
                std::string& result) {
    char buffer[1024];
    FILE* file = NULL;

    if ((file = popen(cmd.c_str(), "r")) == NULL) {
        LOG_ERROR("ExecuteCMD popen fail, cmd:%s\n", cmd.c_str());
        return false;
    }

    while (fgets(buffer, 1024, file) != NULL) {
        result.append(buffer);
    }

    pclose(file);
    file = NULL;

    return true;
}

}