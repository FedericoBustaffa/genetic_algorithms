cmake_minimum_required(VERSION 3.5...3.27)

project(genetic_algorithms LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_subdirectory(pybind11)
pybind11_add_module(genetic ${SOURCES} ${HEADERS})
