#!/bin/bash -ex

export CXX=/usr/bin/clang++

if [ ! -d build ]; then
   mkdir build
fi

cd build
cmake ..
make -j8