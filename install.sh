#!/bin/bash

git submodule add https://github.com/pybind/pybind11.git pybind11/
pip install -r requirements.txt
mkdir build
cd build
cmake ..
make
cd ..
pip install .

