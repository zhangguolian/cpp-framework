#include <logs/log.hpp>
#include <utils/utils.h>

int main() {
    //printf("\033[31mhello world\033[5m\n");
    LOG_DEBUG("%d\n", 1);
    LOG_INFO("%d\n", 2);
    LOG_ERROR("%d\n", 3);

    return 0;
}