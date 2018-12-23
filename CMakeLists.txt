cmake_minimum_required(VERSION 3.0)
project(cpu)

set(SRC 
        src/cpu.cpp
        src/clock.cpp
        src/register.cpp
        src/ram.cpp
        src/counter.cpp
        src/tools.cpp
    )

set(HEADERS 
        include/cpu.h
        include/clock.h
        include/register.h
        include/ram.h
        include/counter.h
        include/tools.h
        
        lib/termcolor.hpp
    )

set(TEST
        test/main.cpp
    )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(cpu ${SRC} ${HEADER} ${TEST})
target_include_directories(cpu PRIVATE include lib)

