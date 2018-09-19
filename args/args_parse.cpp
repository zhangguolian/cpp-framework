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

void ArgsParse::Parse(int argc, char* argv[]) {
    try {
        store(parse_command_line(argc, argv, desc_), args_list_);
    } catch(error_with_no_option_name& ex) {
        LOG_ERROR("ArgsParse::Parse fail, error:%s.", ex.what());
    }

    notify(args_list_);
}
bool ArgsParse::IsExist(const std::string& name) {
    return args_list_.count(name) > 0;
}
void ArgsParse::PrintfDescription() {
    std::cout << desc_ << std::endl;
}

void ArgsParse::Add(const std::string& name,
                    const std::string& description) {
    desc_.add_options()(
            name.c_str(),  
            description.c_str()
    );
}

}