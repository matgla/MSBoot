rmdir /Q /S bin
mkdir bin
cd bin
cmake .. -G"Unix Makefiles" -DSTM32_LIBRARY_ROOT_DIR="D:/libs/en.stm32f4_dsp_stdperiph_lib/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/Libraries"
cd ..