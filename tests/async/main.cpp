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

#include <async/async.h>

void print(int a, int b) {
    std::cout<< "print:" << a+b << std::endl;
}

void print1(int a, int b) {
    std::cout<< "print1:" << a+b << std::endl;
}

void print_once(int a, int b) {
    std::cout<< "print_once:" << a+b << std::endl;
}

int main() {
    // Init thread
    std::shared_ptr<async::Thread> main_thread;
    main_thread.reset(new async::Thread());

    // Init timer
    async::Timer timer; 
    async::Timer timer1; 

    // Create a 2 second timer task
    timer.CreateTimerTask(boost::bind(print, 1, 2), boost::posix_time::seconds(2), main_thread);

    // Create a 2 millisecond single timer task
    timer.CreateOnceTimerTask(boost::bind(print_once, 1, 2), boost::posix_time::millisec(2), main_thread);

    // Create a 6 second timer task
    timer1.CreateTimerTask(boost::bind(print1, 1, 2), boost::posix_time::seconds(6), main_thread);

    // Waiting for thread to end
    main_thread->Join();
    
    return 0;
}