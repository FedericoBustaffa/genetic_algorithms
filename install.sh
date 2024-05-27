#!/bin/bash

git submodule update --init
pip install -r requirements.txt
mkdir build
cd build
cmake ..
make -j
cd ..
pip install .

