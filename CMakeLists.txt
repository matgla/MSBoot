cmake_minimum_required(VERSION 3.9)

set(linker_script "${CMAKE_CURRENT_SOURCE_DIR}/lkr/STM32F103C8Tx_FLASH.ld")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(cmake/ConfigureProject.cmake)

project(MsBoot CXX C ASM)

add_subdirectory(lib)
add_subdirectory(src)
