cmake_minimum_required(VERSION 3.0)
project(cpu2)

set(SRC 
        src/main.cpp
        src/clock.cpp
        src/register.cpp
    )
set(HEADERS 
        include/cpu2/clock.h
        include/cpu2/register.h
    )

set(CMAKE_MODULE_PATH "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(cpu2 ${SRC} ${HEADER})
target_include_directories(cpu2 PRIVATE include/cpu2)

