#include <iostream>
#include <string>
#include <base/base.h>

int main(int argc, char** argv) {
    std::cout << base::StringPrintf("test%d, test%s", 1, "2") << std::endl;
    std::cout << base::StringToInt("1") << std::endl;
    std::cout << base::StringToInt64("2") << std::endl;
    std::cout << base::StringToUInt("3") << std::endl;
    std::cout << base::StringToUInt64("4") << std::endl;
    std::cout << base::StringToFloat("5.0") << std::endl;
    std::cout << base::StringToDouble("6.0") << std::endl;
    std::cout << base::StringToBool("true") << std::endl;

    return 0;
}