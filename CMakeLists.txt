cmake_minimum_required(VERSION 3.1)

set(linker_script "${CMAKE_CURRENT_SOURCE_DIR}/lkr/STM32F103C8Tx_FLASH.ld")
include(cmake/ConfigureProject.cmake)

project(MsOS_Boot CXX C ASM)

add_subdirectory(lib)
add_subdirectory(src)
