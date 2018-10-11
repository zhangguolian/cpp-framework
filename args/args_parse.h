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

#include <memory>
#include <boost/program_options.hpp>

using boost::program_options::value;
using boost::program_options::store;
using boost::program_options::notify;
using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::parse_command_line;
using boost::program_options::error_with_no_option_name;  

namespace args {

class ArgsParse {
public:
    ArgsParse();
    ArgsParse(const std::string& usage);
    ~ArgsParse();

    void Parse(int argc, char* argv[]);
    void PrintfDescription();

    std::shared_ptr<bool> Get(const std::string& name,
                              const std::string& description);
             
    template<typename T>
    std::unique_ptr<T> Get(const std::string& name,
                           const T& default_value,
                           const std::string& description) {
        std::unique_ptr<T> result;
        result.reset(new T());

        desc_.add_options()(
            name.c_str(), 
            value<T>(result.get())->default_value(default_value), 
            description.c_str()
        );

        return result;
    }

private:
    variables_map args_list_;
    options_description desc_;
    std::map<std::string, std::shared_ptr<bool>> option_list_;
};

};