#!/bin/bash
# compile.sh - compile and run project

set -e

echo "Compiling project..."
g++ -std=c++20 -Wall -Wextra -O2 ../src/*.cpp -o main

echo "Running program..."
./main
