cmake_minimum_required(VERSION 3.17)
project(GoogleTestExample)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

add_executable(GoogleTestExample main.cpp RNA.cpp RNA.h)
target_link_libraries(GoogleTestExample gtest gtest_main)