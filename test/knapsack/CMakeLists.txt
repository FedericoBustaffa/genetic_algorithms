cmake_minimum_required(VERSION 3.10)

project(knapsack)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(knapsack src/knapsack.cpp)
target_include_directories(knapsack PUBLIC ../../include/)
