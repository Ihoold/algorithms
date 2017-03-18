cmake_minimum_required(VERSION 3.6)
project(algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        tests/test.cpp)


set(SOURCE_FILES_ALL
        tests/test_all.cpp)

add_executable(algorithms_test ${SOURCE_FILES})
add_executable(algorithms_test_all ${SOURCE_FILES_ALL})