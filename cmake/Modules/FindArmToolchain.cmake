cmake_minimum_required(VERSION 3.6)

message("no! $ENV{ARM_TOOLCHAIN}")
if (EXISTS $ENV{ARM_TOOLCHAIN})
    file(TO_CMAKE_PATH $ENV{ARM_TOOLCHAIN} arm_toolchain_path_converted)
    set(arm_toolchain_path "${arm_toolchain_path_converted}/bin")
elseif (ARM_TOOLCHAIN_PATH)
    set(arm_toolchain_path "${ARM_TOOLCHAIN_PATH}/bin")
endif()

if (arm_toolchain_path)
    message("-- ARM toolchain path: ${arm_toolchain_path}")
endif()

set(binary_paths 
    "/bin" 
    "/usr/bin" 
    "${arm_toolchain_path}"
)

find_program(arm_c_compiler 
    NAMES 
        "arm-none-eabi-gcc" 
    PATHS
        ${binary_paths} 
)

find_program(arm_cxx_compiler 
    NAMES 
        "arm-none-eabi-g++" 
    PATHS
        ${binary_paths} 
)

find_program(arm_cxx_objcopy 
    NAMES 
        "arm-none-eabi-objcopy" 
    PATHS
        ${binary_paths} 
)

find_program(arm_cxx_objdump 
    NAMES 
        "arm-none-eabi-objdump" 
    PATHS
        ${binary_paths} 
)

message ("-- ARM ASM compiler: ${arm_c_compiler}")
message ("-- ARM C compiler: ${arm_c_compiler}")
message ("-- ARM CXX compiler: ${arm_cxx_compiler}")
message ("-- ARM CXX objcopy: ${arm_cxx_objcopy}")
message ("-- ARM CXX objdump: ${arm_cxx_objdump}")

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_ASM_COMPILER  ${arm_c_compiler})
set(CMAKE_C_COMPILER    ${arm_c_compiler})
set(CMAKE_CXX_COMPILER  ${arm_cxx_compiler})
set(CMAKE_OBJCOPY       ${arm_cxx_objcopy})
set(CMAKE_OBJDUMP       ${arm_cxx_objdump})

