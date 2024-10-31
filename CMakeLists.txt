# TODO: migrate from .sh
# CLion forces me to use CMake... fun

cmake_minimum_required(VERSION 3.29)
project(osdev)

set(CMAKE_CXX_STANDARD 14)

add_executable(osdev kernel.cpp)
