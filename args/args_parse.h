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