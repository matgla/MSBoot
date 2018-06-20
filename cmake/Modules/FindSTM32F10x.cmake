if (DEFINED $ENV{STM32_LIBRARIES_ROOT_DIR})
    file(TO_CMAKE_PATH $ENV{STM32_LIBRARIES_ROOT_DIR} stm32_libraries_root_dir_converted)
    set(stm32_libraries_root_dir ${stm32_library_root_dir_converted})
elseif (DEFINED STM32_LIBRARIES_PATH)
    set(stm32_libraries_root_dir ${STM32_LIBRARIES_PATH})
endif()

if (stm32_libraries_root_dir)
    message("-- STM32 Libraries path: ${stm32_libraries_root_dir}")
else ()
    message(FATAL_ERROR "STM32 Libraries can't be found. Please set environment variable: STM32_LIBRARIES_ROOT_DIR or pass path to cmake with -DSTM32_LIBRARIES_PATH")
endif ()


#find_path(stm32_library_path
#    NAMES
#        "Libraries/CMSIS/CM3/CoreSupport/core_cm3.c"
#        "Libraries/STM32F10x_StdPeriph_Driver/inc/misc.h"
#    PATHS 
#        ${stm32_libraries_path}
#)

message("startup: ${stm32_libraries_root_dir}/**.s")

file(GLOB_RECURSE stm32_startup_file ${stm32_libraries_root_dir}/**/startup_stm32f40xx.s)
message("startup file: ${stm32_startup_file}")

if (NOT EXISTS ${stm32_startup_file})
    message(FATAL_ERROR "Can't find gcc_ride7/startup_stm32f10x_${device_class}.s under: ${stm32_library_path}")
endif ()

set(std_periph_include_path ${stm32_library_path}/Libraries/STM32F10x_StdPeriph_Driver/inc)
set(cmsis_include_path ${stm32_library_path}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x)
set(core_include_path ${stm32_library_path}/Libraries/CMSIS/CM3/CoreSupport)


set(sources_path ${stm32_library_path}/Libraries/STM32F10x_StdPeriph_Driver/src)

file(GLOB sources 
    ${sources_path}/*.c 
    ${std_periph_include_path}/*.h 
    ${cmsis_include_path}/*.c
    ${cmsis_include_path}/*.h
    ${core_include_path}/*.h    
    ${stm32_startup_file}
)

string(TOUPPER ${device_class} device_class_uppercased)
add_definitions(-DSTM32F10X_${device_class_uppercased})

SET(CMAKE_C_FLAGS "-mthumb -mcpu=cortex-m3 -fno-builtin -Wall -std=gnu99 -fdata-sections -ffunction-sections -mfloat-abi=soft " CACHE INTERNAL "c compiler flags")
SET(CMAKE_CXX_FLAGS "-mthumb -mcpu=cortex-m3 -fno-builtin -Wall -std=c++1z -fdata-sections -ffunction-sections -mfloat-abi=soft -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-threadsafe-statics" CACHE INTERNAL "cxx compiler flags")
SET(CMAKE_ASM_FLAGS "-mthumb -mcpu=cortex-m3" CACHE INTERNAL "asm compiler flags")

SET(CMAKE_EXE_LINKER_FLAGS "-nostartfiles -Wl,--gc-sections -mthumb -mcpu=cortex-m3 -T${CMAKE_SOURCE_DIR}/lkr/STM32F103C8Tx_FLASH.ld --specs=nano.specs" CACHE INTERNAL "exe link flags")


add_library(stm32 ${sources} )

target_include_directories(stm32 PUBLIC 
    ${std_periph_include_path}
    ${cmsis_include_path}
    ${core_include_path}
)
# find_package(PackageHandleStandardArgs)
# find_package_handle_standard_args(CMSIS DEFAULT_MSG
#     STM32_LIBRARY_ROOT_DIR
#     STM32_STARTUP_SOURCE
#     STM32_SOURCES
#     STM32_INCLUDE_DIRS
# )

