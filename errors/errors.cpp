#include <errors/errors.h>

#include <execinfo.h>
#include <signal.h>
#include <logs/logs.hpp>

void ErrorsSignHandler(int signum) {
    signal(signum, SIG_DFL);

    void *array[10];
    size_t size = backtrace(array, 10);
    char** strings = (char**)backtrace_symbols(array, size);
    for (size_t i = 0; i < size; i++) {
        LOG_ERROR("%lu %s", i, strings[i]);
    }

    free(strings);
    exit(-1);
}

