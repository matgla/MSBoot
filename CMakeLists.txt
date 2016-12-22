if (BUILD_TARGET)
    include(gnu-arm-none-eabi.cmake)
endif(BUILD_TARGET)

cmake_minimum_required (VERSION 2.8)
project(msos C CXX ASM)

file(GLOB_RECURSE C_SRCS "src/*.c" "src/*.cpp" "src/*.hpp" "src/*.h" "lib/*.S")

include_directories("inc")
include_directories("src")

include("cmake_header.txt")
 
option (BUILD_TESTS "build ut tests" OFF)
option (BUILD_TARGET "build target" OFF)
option (LEAK_SANITIZER "enable leak sanitizer" OFF)
option (ADDRESS_SANITIZER "enable address sanitizer" OFF)

if (LEAK_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
endif(LEAK_SANITIZER)

if (ADDRESS_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif(ADDRESS_SANITIZER)

include_directories("lib/inc/core")
include_directories("lib/inc/peripherals")

if(BUILD_TESTS)
	add_subdirectory("test")
	add_executable(OnionFlyer EXCLUDE_FROM_ALL ${C_SRCS})
endif(BUILD_TESTS)

if(BUILD_TARGET)
	add_subdirectory("lib")

	file(COPY "${PROJECT_SOURCE_DIR}/stm32_flash.ld" DESTINATION ${PROJECT_BINARY_DIR}) 
	add_executable(msos ${C_SRCS})
    target_link_libraries(msos stm32 m)
	generate_arm_binary(msos)
endif(BUILD_TARGET)



