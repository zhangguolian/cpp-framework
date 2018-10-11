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

#pragma once

#include <map>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>

namespace async {

class Thread;

class TimerDevice {
private:
    TimerDevice();
    ~TimerDevice();

    void TimerThread();

    boost::thread thread_;
    boost::asio::io_service io_service_;

    friend class Timer;
};

class Timer {
public:
    Timer();
    ~Timer();
  
    int CreateTimerTask(const boost::function<void(void)>& task, 
                        const boost::posix_time::time_duration& expiry_time,
                        const std::shared_ptr<Thread>& task_thread);
    void CancelTimerTask(int timer_id);
    void CreateOnceTimerTask(const boost::function<void(void)>& task, 
                             const boost::posix_time::time_duration& expiry_time,
                             const std::shared_ptr<Thread>& task_thread);

private:
    void TimerCallBack(const boost::system::error_code& err, 
                       const std::shared_ptr<boost::asio::deadline_timer>& timer,
                       int timer_id,
                       const boost::posix_time::time_duration& expiry_time,
                       const boost::function<void(void)>& task,
                       const std::shared_ptr<Thread>& task_thread);

private:
    int timer_id_;
    boost::mutex mutex_;
    std::map<int, std::shared_ptr<boost::asio::deadline_timer>> timer_list_;
    static TimerDevice timer_device_;
};

};