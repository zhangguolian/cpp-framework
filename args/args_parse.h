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

// Console parameter parsing class.
// It can parse the parameters of the main function 
// passed in when the program starts.
class ArgsParse {
public:
    typedef std::map<std::string, std::shared_ptr<bool>> OPTION_LIST;

    ArgsParse();
    // Output instructions contains usage, 
    // like Usage: args_test [options...]
    ArgsParse(const std::string& usage);
    ~ArgsParse();

    // Parsing command line arguments.
    // param argc and param argv are the main function parameter.
    void Parse(int argc, char* argv[]);

    // Output an introduction to all parameters.
    void PrintfDescription();

    // Add a parameter with no value.
    // Param name is parameter name.
    // Param description is introduction of parameter.
    // Return a pointer of type bool, after calling the parse function,
    // true if this argument is passed in, otherwise false
    std::shared_ptr<bool> Get(const std::string& name,
                              const std::string& description);

    // Add a value parameter.
    // Param name is parameter name.
    // Param default_value is default value of the parameter.
    // Param description is introduction of parameter.
    // Return a pointer of type T, after calling the parse function,
    // will get the value passed in.
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

    // Save a list of parameters with no values, 
    // assign true or false.
    OPTION_LIST option_list_;
};

}; // namespace args