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

#include <list>
#include <map>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>

namespace async {

class Thread {
public:
    Thread(int thread_num = 1);
    ~Thread();

    void Join();
    void PostTask(const boost::function<void(void)>& task);

    boost::asio::io_service& io_service();

    bool operator==(const boost::thread::id& id) const;
    bool operator!=(const boost::thread::id& id) const;

private:
    void TaskThread();

private:
    std::vector<std::unique_ptr<boost::thread>> thread_list_;
    boost::asio::io_service io_service_;
};

};