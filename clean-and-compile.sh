#!/bin/bash

rm -rf build html
rm include/Sprites.hpp
mkdir build && cd build
cmake -S ../ -B ./
cmake --build ./ -j8

exit 0