cmake_minimum_required(VERSION 3.16)
project(YHabteab_trainee_cpp_sort)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-g")

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

add_executable(YHabteab_trainee_cpp_sort main.cpp)