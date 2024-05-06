cmake_minimum_required(VERSION 3.10)

project(maze)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(maze src/maze_solver.cpp src/maze.hpp)
target_include_directories(maze PUBLIC ../../include/)
