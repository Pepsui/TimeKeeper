#!/bin/bash -ex

if [ -d build ]; then
   rm -r build
fi

if [ -d saved_charges ]; then
   rm -r saved_charges
fi