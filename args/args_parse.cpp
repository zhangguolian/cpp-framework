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

#include <args/args_parse.h>

#include <logs/logs.hpp>

namespace args {

ArgsParse::ArgsParse() {
    
}
ArgsParse::ArgsParse(const std::string& usage)
          : desc_(usage) {

}
ArgsParse::~ArgsParse() {

}

bool ArgsParse::Parse(int argc, char* argv[]) {
    try {
        store(parse_command_line(argc, argv, desc_), args_list_);
    } catch(error_with_no_option_name& ex) {
        LOG_ERROR("ArgsParse::Parse fail, error:%s.", ex.what());
        return false;
    }

    // Save all parameters to args_list_
    notify(args_list_);

    // Determine if a parameter with no value exists, 
    // and if it exists, assign it to true
    for (auto iter = option_list_.begin(); iter != option_list_.end(); iter++) {
        if (args_list_.count(iter->first) > 0) {
            *iter->second = true;
        }
    }

    return true;
}

void ArgsParse::PrintfDescription() {
    std::cout << desc_ << std::endl;
}

std::shared_ptr<bool> ArgsParse::Get(const std::string& name,
                                     const std::string& description) {
    desc_.add_options()(
            name.c_str(),  
            description.c_str()
    );

    std::shared_ptr<bool> result;
    result.reset(new bool(false));
    option_list_[name] = result;

    return result;
}

} // namespace args