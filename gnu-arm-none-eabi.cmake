include(CMakeForceCompiler)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR "cortex-m4" CACHE STRING "Choose target procesor core family")

find_program(ARM_CC arm-none-eabi-gcc)
find_program(ARM_CXX arm-none-eabi-g++)

set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER ${ARM_CC})
set(CMAKE_CXX_COMPILER ${ARM_CXX})

CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)

set(CMAKE_C_FLAGS
  "${CMAKE_C_FLAGS}"
  "-std=gnu99 -g -O3 -Wall -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m4"
)
set(CMAKE_C_FLAGS
  "${CMAKE_C_FLAGS}"
  " -fsingle-precision-constant -Wdouble-promotion -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Iinc -Ilib -Ilib/inc -Ilib/inc/core -Ilib/inc/peripherals "
)

set(CMAKE_C_FLAGS
  "${CMAKE_C_FLAGS}"
  " -DUSE_STDPERIPH_DRIVER -D HSE_VALUE=8000000 -DSTM32F429_439xx -DUSE_FULL_ASSERT"
)

set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS}"
  "-std=c++11 -g -O3 -Wall -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m4"
)
set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS}"
  " -fsingle-precision-constant -Wdouble-promotion -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Iinc -Ilib -Ilib/inc -Ilib/inc/core -Ilib/inc/peripherals "
)

set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS}"
  " -DUSE_STDPERIPH_DRIVER -D HSE_VALUE=8000000 -DSTM32F429_439xx -DUSE_FULL_ASSERT"
)


string(REGEX REPLACE ";" " " CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "")
string(REGEX REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "")



set(CMAKE_EXE_LINKER_FLAGS 
	"${CMAKE_EXE_LINKER_FLAGS}"
	"-Llib -lstm32 -static -lm"
)

string(REGEX REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" CACHE STRING "")

set(CMAKE_ASM_FLAGS "-std=gnu99 -g -O3 -Wall -mlittle-endian -mthumb -mthumb-interwork -march=armv7e-m -nostartfiles -mcpu=cortex-m4" CACHE STRING "")
