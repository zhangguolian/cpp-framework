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

#include <async/thread.h>

namespace async {

Thread::Thread(int thread_num) 
       : is_running_(false) {
    Start(thread_num);
}
Thread::~Thread() {
    Stop();
}

void Thread::Start(int thread_num) {
    if (is_running_) {
        return;
    }

    is_running_ = true;
    for (int i = 0; i < thread_num; i++) {
        boost::thread* task_thread = new boost::thread(boost::bind(
            &Thread::TaskThread, this));
        thread_list_.push_back(std::unique_ptr<boost::thread>());
        thread_list_[thread_list_.size()-1].reset(task_thread);
    } 

    return;
}

void Thread::Stop() {
    if (!is_running_) {
        return;
    }
    
    is_running_ = false;
    io_service_.stop();

    return;
}

void Thread::Join() {
    for (size_t i = 0; i < thread_list_.size(); i++) {
        thread_list_[i]->join();
    }

    return;
}

void Thread::PostTask(const boost::function<void(void)>& task) {
    io_service_.post(task);

    return;
}

boost::asio::io_service& Thread::io_service() {
    return io_service_;
}

bool Thread::operator==(const boost::thread::id& id) const {
    for (size_t i = 0; i < thread_list_.size(); i++) {
        if (thread_list_[i]->get_id() == id) {
            return true;
        }
    }

    return false;
}
bool Thread::operator!=(const boost::thread::id& id) const {
    for (size_t i = 0; i < thread_list_.size(); i++) {
        if (thread_list_[i]->get_id() == id) {
            return false;
        }
    }

    return true;
}

void Thread::TaskThread() {
    if (!is_running_) {
        return;
    }

    boost::asio::io_service::work work(io_service_);
    io_service_.run();
    
    return;
}

} // namespace async
