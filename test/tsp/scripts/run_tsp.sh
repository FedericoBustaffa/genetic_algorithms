#!/bin/bash

../build/tsp $1 $2 $3 $4
python3 tsp_visualize.py

