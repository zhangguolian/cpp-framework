#include <iostream>
#include <string>
#include <utils/utils.h>

int main() {
    std::cout << utils::StringPrintf("test%d, test%s", 1, "2") << std::endl;

    return 0;
}