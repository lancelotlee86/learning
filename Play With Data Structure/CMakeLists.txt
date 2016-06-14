cmake_minimum_required(VERSION 3.3)
project(untitled1)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=g++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -lm")

set(SOURCE_FILES ./chapter5/BiTreeArray.c)
add_executable(untitled1 ${SOURCE_FILES})
target_link_libraries(untitled1 m)
