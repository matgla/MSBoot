rmdir /Q /S bin
mkdir bin
cd bin
cmake .. -G"Unix Makefiles" -DSTM32_LIBRARY_ROOT_DIR="D:\programowanie\STM32F4xx_DSP_StdPeriph_Lib_V1.8.0\Libraries"
cd ..