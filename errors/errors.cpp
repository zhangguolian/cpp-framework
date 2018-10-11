/*
 *
 * Copyright 2018 Guolian Zhang.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

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

