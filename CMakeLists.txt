cmake_minimum_required(VERSION 3.5.1)

project(cpp_framework VERSION "1.0.0")

add_definitions(-std=c++11)

find_package(Boost REQUIRED COMPONENTS system thread filesystem)

#Global include path for all libs.
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})  

add_subdirectory(utils)
add_subdirectory(http)
add_subdirectory(async)
add_subdirectory(tests)