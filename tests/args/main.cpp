

#include <iostream>
#include <args/args.h>
    
int main(int argc, char* argv[])  
{  
    args::ArgsParse args_parse("Usage");

    args_parse.Add("help", "help args");
    std::unique_ptr<int> type = args_parse.Get<int>("type", 0, "type args");

    args_parse.Parse(argc, argv);

    if (args_parse.IsExist("help")) {
        args_parse.PrintfDescription();
        return 0;
    }

    std::cout << "type:" << *type << std::endl;
  
    return 0;  
}  