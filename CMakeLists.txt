cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(unknown "Unknown" CACHE STRING "Unknown Tag" FORCE)
set(BUILD_UT ${unknown} CACHE STRING "build UT's")

if (NOT ${BUILD_UT})
    message (STATUS "Build: target")

    set(linker_scripts_directory "${CMAKE_CURRENT_SOURCE_DIR}/linker_scripts" CACHE STRING "Path to linker scripts")
    message (STATUS "Linker script directory: ${linker_scripts_directory}")    
    
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
    set(HAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/hal")
    find_package(EmbeddedHAL REQUIRED)

    project(MsBoot CXX C ASM)

    add_subdirectory(lib)
    add_subdirectory(src)

elseif (${BUILD_UT})
    message(STATUS "Build: UT")

    project(MsBoot CXX C ASM)

    add_subdirectory(lib)
    add_subdirectory(src)
    add_subdirectory(test)
endif()

