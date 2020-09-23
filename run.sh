#!/bin/sh
rm -r build
mkdir build
cd build
cmake -G Unix\ Makefiles ..
make
./breakout