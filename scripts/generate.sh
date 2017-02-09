#!/bin/bash
cd ..
rm -rf bin
mkdir bin
cd bin
cmake .. -G"Unix Makefiles" -DBUILD_TARGET=ON
cd ..