cmake_minimum_required(VERSION 3.6)
project(Project5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Project5.cpp Set.h)
add_executable(Project5 ${SOURCE_FILES})