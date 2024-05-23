cmake_minimum_required(VERSION 3.5...3.27)

project(genetic_algorithms)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_subdirectory(pybind11)
pybind11_add_module(genetic ${SOURCES} ${HEADERS})
