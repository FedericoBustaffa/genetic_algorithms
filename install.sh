#!/bin/bash

git submodule update --init
py -m venv .env
source .env/bin/activate
pip install -r requirements.txt
mkdir build
cd build
cmake ..
make -j
cd ..
pip install .

