cmake_minimum_required(VERSION 3.5...3.27)

project(genetic_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SOURCE_DIR ..)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_subdirectory(pybind11)
pybind11_add_module(genetic ${SOURCES} ${HEADERS})
# target_link_libraries(genetic PRIVATE pybind11::pybind11)

target_compile_options(genetic PRIVATE -Wall -O3)

set(stubgen "${CMAKE_SOURCE_DIR}/.env/bin/stubgen")
add_custom_command(
  TARGET genetic
  POST_BUILD
  COMMAND ${stubgen} -m genetic -o ..
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
