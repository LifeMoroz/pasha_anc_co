# cmake_minimum_required(VERSION <specify CMake version here>)
project(project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp map.cpp map.h chain.cpp chain.h point.h global.h)
add_executable(project ${SOURCE_FILES})