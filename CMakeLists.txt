
cmake_minimum_required(VERSION 2.6)
project(SquareEquationSolver)

set(CMAKE_CXX_FLAGS "-std=c++14")
add_executable(solver main.cpp)
add_executable(tests test.cpp)
