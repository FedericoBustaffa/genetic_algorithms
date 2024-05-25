cmake_minimum_required(VERSION 3.5...3.27)

project(genetic_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SOURCE_DIR ..)

file(GLOB_RECURSE SOURCES "bind/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_subdirectory(pybind11)
pybind11_add_module(genetic ${SOURCES} ${HEADERS})

target_compile_options(genetic PRIVATE -Wall -O3)
include_directories(genetic PRIVATE include)
target_link_libraries(genetic PRIVATE pybind11::pybind11)
