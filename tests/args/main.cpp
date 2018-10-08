

#include <iostream>
#include <args/args.h>
    
int main(int argc, char* argv[]) {  
    args::ArgsParse args_parse("Usage: args_test [options...]");

    std::shared_ptr<bool> help = args_parse.Get("help", "help args");
    std::unique_ptr<int> type = args_parse.Get("type", 0, "type args");

    args_parse.Parse(argc, argv);

    if (*help) {
        args_parse.PrintfDescription();
        return 0;
    }

    std::cout << "type:" << *type << std::endl;
  
    return 0;  
}  