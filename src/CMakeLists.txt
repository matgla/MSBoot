
set (sources_path "${CMAKE_CURRENT_SOURCE_DIR}/")

set (sources 
    ${sources_path}/main.cpp
)

include_directories(${sources_path})

add_subdirectory(hal)

add_executable(msboot ${sources}) 
target_link_libraries(msboot stm32 stm32_hal_common)

target_compile_options(stm32 PUBLIC
    -fno-builtin
    -fdata-sections
    -fdata-sections 
    -ffunction-sections
    $<$<COMPILE_LANGUAGE:C>:-std=gnu99 -Wno-implicit-function-declaration>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-threadsafe-statics>
)

include(../cmake/GenerateBinary.cmake)
generate_binary(msboot)