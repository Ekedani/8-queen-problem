cmake_minimum_required(VERSION 3.16)
project(8_queen_problem)

set(CMAKE_CXX_STANDARD 20)

add_executable(8_queen_problem main.cpp solution_tree.cpp solution_tree.h input_output_class.cpp input_output_class.h)