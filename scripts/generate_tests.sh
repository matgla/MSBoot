#!/bin/bash
cd ..
rm -rf bin_test
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
mkdir bin_test
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd bin_test
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cmake .. -DBUILD_TESTS=ON
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd ..