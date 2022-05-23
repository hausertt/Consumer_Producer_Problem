cmake_minimum_required(VERSION 3.21)
project(Betriebssysteme_C)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(Betriebssysteme_C main.cpp)
