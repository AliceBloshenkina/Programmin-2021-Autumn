cmake_minimum_required(VERSION 3.20)
project(pop)

set(CMAKE_CXX_STANDARD 14)

add_executable(pop
        lab1.cpp DynamicArray.h Sequence.h LinkedList.h)
