cmake_minimum_required(VERSION 3.5.1)

project(cpp_framework VERSION "1.0.0")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DDEBUG)
else()
    set(CMAKE_BUILD_TYPE "Release")
endif (CMAKE_BUILD_TYPE MATCHES "Debug")

message("-- Current Mode: " ${CMAKE_BUILD_TYPE})

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_definitions(-std=c++11)

find_package(Boost REQUIRED COMPONENTS system thread filesystem program_options)

#Global include path for all libs.
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})  

add_subdirectory(base)
add_subdirectory(http)
add_subdirectory(async)
add_subdirectory(sql)
add_subdirectory(logs)
add_subdirectory(rpc)
add_subdirectory(args)
add_subdirectory(errors)
add_subdirectory(reflect)
add_subdirectory(tests)