cmake_minimum_required(VERSION 3.0)
project(cpu2)

set(SRC 
        src/cpu2.cpp
        src/clock.cpp
        src/register.cpp
        src/ram.cpp
        src/counter.cpp
    )

set(HEADERS 
        include/cpu2.h
        include/clock.h
        include/register.h
        include/ram.h
        include/counter.h
    )

set(TEST
        test/main.cpp
    )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(cpu2 ${SRC} ${HEADER} ${TEST})
target_include_directories(cpu2 PRIVATE include)

