cmake_minimum_required(VERSION 3.19)
project(CudaSql)

set(CMAKE_CXX_STANDARD 11)

add_executable(CudaSql main.cpp DataTree.cpp DataTree.h)