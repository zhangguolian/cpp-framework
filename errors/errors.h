#pragma once

#include <execinfo.h>
#include <signal.h>

void ErrorsSignHandler(int signum);

#define INIT_ERRORS_SIGNAL()\
    signal(SIGSEGV, ErrorsSignHandler);\
    signal(SIGABRT, ErrorsSignHandler);
