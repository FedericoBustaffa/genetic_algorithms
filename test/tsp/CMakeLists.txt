cmake_minimum_required(VERSION 3.10)

project(tsp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(tsp src/tsp.cpp)
target_include_directories(tsp PUBLIC ../../include/)
