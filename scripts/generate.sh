#!/bin/bash
cd ..
rm -rf bin
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
mkdir bin
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd bin
cmake .. -G"Unix Makefiles" -DBUILD_TARGET=ON
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd ..