cmake_minimum_required(VERSION 3.0)
project(cpu2)

set(SRC 
        main.cpp
        clock.cpp
    )
set(HEADERS 
        clock.h
    )
include_directories(headers)

set(CMAKE_MODULE_PATH "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(cpu2 ${SRC} ${HEADER})
