#!/bin/bash
cd ..
rm -rf bin_test
mkdir bin_test
cd bin_test
cmake .. -DBUILD_TESTS=ON
cd ..