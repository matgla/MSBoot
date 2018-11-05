cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)


set (unknown "Unknown" CACHE STRING "Unknown Tag" FORCE)
set(BUILD_UT ${unknown} CACHE STRING "build UT's")

if (NOT ${BUILD_UT})
    message (STATUS "Build: target")
    include(cmake/ConfigureProject.cmake)
#    if (${vendor} STREQUAL "STM32")
#        set(linker_script "${CMAKE_CURRENT_SOURCE_DIR}/lkr/STM32F103C8Tx_FLASH.ld")
#        message(STATUS "Linker script: ${linker_script}")
#    endif()
    
    project(MsBoot CXX C ASM)

    add_subdirectory(lib)
    add_subdirectory(src)

elseif (${BUILD_UT})
    message (STATUS "Build: UT")

    project(MsBoot CXX C ASM)
    
    add_subdirectory(lib)
    add_subdirectory(src)
    add_subdirectory(test)
endif()

