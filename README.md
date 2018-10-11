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
sudo apt-get install libboost-all-dev libevent-dev libcrypto++-dev libcurl4-openssl-dev libmysqlclient-dev
```

### Build

Configure the project build with the following command to create the 
`build` directory with the configuration.

```shell
mkdir build && cd build    # Create a build directory.
cmake ..                   # Configure the project.
make && sudo make install  # Build all default targets.
```

