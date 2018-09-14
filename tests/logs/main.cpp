#include <logs/logs.hpp>
#include <utils/utils.h>

int main() {
    //printf("\033[31mhello world\033[5m\n");
    LOG_DEBUG("%d", 1);
    LOG_INFO("%d", 2);
    LOG_ERROR("test");
    return 0;
}