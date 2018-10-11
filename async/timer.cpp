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

#include <async/timer.h>

#include <async/thread.h>

namespace async {

TimerDevice Timer::timer_device_;

TimerDevice::TimerDevice() {
    thread_ = boost::thread(boost::bind(
                &TimerDevice::TimerThread, this));
}
TimerDevice::~TimerDevice() {

}

void TimerDevice::TimerThread() {
    boost::asio::io_service::work work(io_service_);
    io_service_.run();
    
    return;
}

Timer::Timer()
      : timer_id_(1) {

}
Timer::~Timer() {

}

int Timer::CreateTimerTask(const boost::function<void(void)>& task, 
                           const boost::posix_time::time_duration& expiry_time,
                           const std::shared_ptr<Thread>& task_thread) {
    mutex_.lock();
    int timer_id = timer_id_++;
    mutex_.unlock();

    std::shared_ptr<boost::asio::deadline_timer> timer;
    timer.reset(new boost::asio::deadline_timer(timer_device_.io_service_, expiry_time));
    timer->async_wait(boost::bind(&Timer::TimerCallBack, this, _1, timer, 
        timer_id, expiry_time, task, task_thread));

    mutex_.lock();
    timer_list_[timer_id] = timer;
    mutex_.unlock();

    return timer_id; 
}
void Timer::CancelTimerTask(int timer_id) {
    mutex_.lock();
    timer_list_.erase(timer_id);
    mutex_.unlock();

    return;
}
void Timer::CreateOnceTimerTask(const boost::function<void(void)>& task,
                                const boost::posix_time::time_duration& expiry_time,
                                const std::shared_ptr<Thread>& task_thread) {
    std::shared_ptr<boost::asio::deadline_timer> timer;
    timer.reset(new boost::asio::deadline_timer(timer_device_.io_service_, expiry_time));
    timer->async_wait(boost::bind(&Timer::TimerCallBack, this, _1, timer, 
        0, expiry_time, task, task_thread));
}

void Timer::TimerCallBack(const boost::system::error_code& err, 
                          const std::shared_ptr<boost::asio::deadline_timer>& timer,
                          int timer_id,
                          const boost::posix_time::time_duration& expiry_time,
                          const boost::function<void(void)>& task,
                          const std::shared_ptr<Thread>& task_thread) {
    mutex_.lock();
    if (timer_id != 0 && timer_list_.find(timer_id) == timer_list_.end()) {
        mutex_.unlock();
        return;
    }
    mutex_.unlock();

    task_thread->PostTask(task);

    if (timer_id != 0) {
        timer->expires_at(timer->expires_at() + expiry_time) ;
        timer->async_wait(boost::bind(&Timer::TimerCallBack, this, _1, timer, 
            timer_id, expiry_time, task, task_thread));
    }

    return;
}

}