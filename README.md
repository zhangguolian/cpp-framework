## Introduction

> The cpp-framework is a c++ framework,
> Which includes http, thread pool, timer, json,
> database, encryption, reflection and so on.

| Module                  | Introduction                                         |
|-------------------------|------------------------------------------------------|
| args                    | Console parameter parsing framework                  |
| async                   | Thread pool and timer framework                      |
| base                    | Encryption, hash, json and so on base framework      |
| http                    | Asynchronous http framework                          |
| logs                    | Log framework                                        |
| reflect                 | Reflection framework                                 |
| rpc                     | RPC server and client framework                      |
| sql                     | Database framework                                   |
| tests                   | Test cases for all modules, with detailed usage notes|

## Getting Started

Operating system | Status
---------------- | ----------
Linux            | [![AppVeyor](https://img.shields.io/appveyor/ci/ethereum/cpp-ethereum/develop.svg)](https://ci.appveyor.com/project/ethereum/cpp-ethereum)
Windows          | [![TravisCI](https://img.shields.io/travis/ethereum/cpp-ethereum/develop.svg)](https://travis-ci.org/ethereum/cpp-ethereum)

## Building from source (Ubuntu)

### Get the source code

Git and GitHub are used to maintain the source code. Clone the repository by:

```shell
git clone https://github.com/Guolian-Zhang/cpp-framework.git
cd cpp-framework
```

### Install CMake

```shell
sudo apt-get install cmake
```

### Install GRPC

RPC library is based on GRCP implementation. If you do not need RPC, 
you can delete add_subdirectory(rpc) in all CMakeLists.txt.
```shell
sudo apt-get install pkg-config
sudo apt-get install autoconf automake libtool make g++ unzip 
sudo apt-get install libgflags-dev libgtest-dev 
sudo apt-get install clang libc++-dev

git clone https://github.com/grpc/grpc.git
cd grpc && git submodule update --init

cd third_party/protobuf/
git submodule update --init --recursive
sudo ./autogen.sh
sudo ./configure
make && sudo make install
sudo ldconfig

cd ../..
make && sudo make install
```

### Install dependencies

```shell
sudo apt-get install libboost-all-dev libevent-dev libssl-dev libcurl4-openssl-dev libmysqlclient-dev libjsoncpp-dev
```

### Build

Configure the project build with the following command to create the 
`build` directory with the configuration.

```shell
mkdir build && cd build    # Create a build directory.
cmake ..                   # Configure the project.
make && sudo make install  # Build all default targets.
```

## Example

### Json example

```c++
#include <iostream>
#include <base/base.h>

struct Data {
    // Define reflect params
    REFLECT_DEFINE(int, a);
    REFLECT_DEFINE(std::string, b);
};

int main() {
    Data data;
    data.a = 1;
    data.b = "test";

    // Json serialization of data
    std::string json_data = base::JsonMarShal(data);
    // Output json string
    std::cout << base::JsonMarShal(data) << std::endl;

    Data data1;
    // Parse the json string into data1
    if (!base::JsonUnmarshal(json_data, data1)) {
        std::cout << "JsonUnmarshal fail" << std::endl;
        return -1;
    } else {
        printf("a:%d, b:%s\n", data1.a, data1.b.c_str());
    }

    return 0;
}
```
```shell
{
   "a" : 1,
   "b" : "test"
}

a:1, b:test
```

### Thread and Timer example
```c++
#include <iostream>
#include <async/async.h>

void Printf(const char* data) {
    printf("%s\n", data);
}

int main() {
    // Init thread
    std::shared_ptr<async::Thread> thread;
    thread.reset(new async::Thread());

    // Create a thread task to printf Hello
    thread->PostTask(boost::bind(&Printf, "Hello"));

    // Init timer
    async::Timer timer;

    // Create a 2 second single timer task
    timer.CreateOnceTimerTask(boost::bind(Printf, "World"), boost::posix_time::seconds(1), thread);

    // Waiting for thread to end
    thread->Join();

    return 0;
}
```
```shell
Hello
World
```

### Http example
```c++
#include <iostream>
#include <http/http.h>

class HttpTest : public http::HttpRequest::Delegate {
public:
    // Handle http response, callback in http thread 
    void OnHttpRequestComplete(std::shared_ptr<http::HttpRequest> request) override {
        printf("res:%s\n", request->response().c_str());
    }

    // Start http request
    void Start() {
        // Create http request
        request_.reset(new http::HttpRequest(
            http::HttpRequest::HttpMode::POST,
            "http://localhost:8080", 
            this));

        // Add request params
        request_->add_params("key", "test");

        // Start http request
        START_HTTP_REQUEST(request_);
    }

private:
    std::shared_ptr<http::HttpRequest> request_;
};

int main() {
    // Init http module
    HTTP_INIT();

    // Start http request
    HttpTest http_test;
    http_test.Start();

    // Blocking the main thread
    while(true) {

    }

    return 0;
}
```
