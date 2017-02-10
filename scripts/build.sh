#!/bin/bash
cd ../bin
make -j4 -l4
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
make stm32BootLoader.bin
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd ..