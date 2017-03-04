cmake_minimum_required(VERSION 3.6)
project(algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        tests/test.cpp)

add_executable(algorithms ${SOURCE_FILES})