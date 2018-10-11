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

#include <iostream>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code& err, boost::asio::deadline_timer* pt)
{
    std::cout<<"hello,world!\n";
    pt->expires_at(pt->expires_at() + boost::posix_time::seconds(2)) ;
    pt->async_wait(boost::bind(print, _1, pt));
}

typedef boost::function<int(void)> Func;

int main() {
    boost::asio::io_service io;

    boost::asio::deadline_timer t(io, boost::posix_time::seconds(2));
    t.async_wait(boost::bind(print, _1, &t));
    io.run();
    
    return 0;
}