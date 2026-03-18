cmake_minimum_required(VERSION 4.1)
project(programming_assignment_2__expression_engine)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(programming_assignment_2__expression_engine
        ArrayStack.h
        main.cpp)
