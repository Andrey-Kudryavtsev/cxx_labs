cmake_minimum_required(VERSION 3.17)
project(CSVParser)

set(CMAKE_CXX_STANDARD 20)

add_executable(CSVParser main.cpp Parser.h printTuple.h ParserExceptions.h ParserExceptions.cpp)