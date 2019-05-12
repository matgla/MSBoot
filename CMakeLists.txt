cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(unknown "Unknown" CACHE STRING "Unknown Tag" FORCE)

set (MSBOOT_BUILD_TESTS off)
if (BUILD_TESTS)
    set (MSBOOT_BUILD_TESTS on)
    unset (BUILD_TESTS CACHE)
endif ()

include(cmake/GitModules.cmake)
fetch_module_with_path(lib/hal "" ${CMAKE_CURRENT_SOURCE_DIR})

execute_command("git submodule foreach git checkout master" ${CMAKE_CURRENT_SOURCE_DIR})
execute_command("git submodule foreach git pull" ${CMAKE_CURRENT_SOURCE_DIR})

if (NOT ${MSBOOT_BUILD_TESTS})
    message (STATUS "Build: target")

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    set(linker_scripts_directory "${CMAKE_CURRENT_SOURCE_DIR}/linker_scripts" CACHE STRING "Path to linker scripts")
    message (STATUS "Linker script directory: ${linker_scripts_directory}")

    add_subdirectory(lib/hal)

    project(MsBoot CXX C ASM)

    add_subdirectory(lib)
    add_subdirectory(src)

elseif (${MSBOOT_BUILD_TESTS})
    message(STATUS "Build: UT")

    set(BOARD "x86_mock")
    set(CMAKE_CXX_STANDARD 17)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/hal)

    project(MsBoot_UTs CXX C ASM)

    add_subdirectory(lib)
    add_subdirectory(src)
    add_subdirectory(test)
endif()

