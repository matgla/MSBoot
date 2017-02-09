#!/bin/bash
cd ../bin
make -j4 -l4
make stm32BootLoader.bin
cd ..