cmake_minimum_required(VERSION 3.10)
project(MatrixProject)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(matrix_app 
    matrix.cpp 
    interface_list.cpp 
    interface_vector.cpp
)
