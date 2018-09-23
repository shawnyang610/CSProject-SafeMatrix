cmake_minimum_required(VERSION 3.12)
project(safe_matrix)

set(CMAKE_CXX_STANDARD 11)
add_executable(safe_matrix main.cpp safe_array.hpp safe_matrix.hpp)