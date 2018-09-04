cmake_minimum_required(VERSION 3.5.1)

project(sign_machine VERSION "1.0.0")

add_definitions(-std=c++11)

#Global include path for all libs.
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})  