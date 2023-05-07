#!/bin/bash

rm -rf build html
mkdir build && cd build
cmake -S ../ -B ./
cmake --build ./ -j8

exit 0