cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(unknown "Unknown" CACHE STRING "Unknown Tag" FORCE)
set(BUILD_UT ${unknown} CACHE STRING "build UT's")

if (NOT ${BUILD_TESTS})
    message (STATUS "Build: target")

    set(linker_scripts_directory "${CMAKE_CURRENT_SOURCE_DIR}/linker_scripts" CACHE STRING "Path to linker scripts")
    message (STATUS "Linker script directory: ${linker_scripts_directory}")

    unset(BUILD_TESTS CACHE)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/hal")

    project(MsBoot CXX C ASM)

    add_subdirectory(lib)
    add_subdirectory(src)

elseif (${BUILD_TESTS})
    set(BUILD_UT OFF)

    message(STATUS "Build: UT")

    set(BOARD "x86_mock")
    set(CMAKE_CXX_STANDARD 17)

    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/hal")

    project(MsBoot_UTs CXX C ASM)

    add_subdirectory(lib)
    add_subdirectory(src)
    add_subdirectory(test)
endif()

