set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set (sources_path "${CMAKE_CURRENT_SOURCE_DIR}/")

set (sources 
    ${sources_path}/main.cpp
)

include_directories(${sources_path})

add_executable(msboot ${sources}) 
target_link_libraries(msboot hal eul)

target_compile_options(msboot PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-std=gnu99>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z -fconcepts -Wall -Werror>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)

# target_compile_options(msboot PUBLIC
#     -fno-builtin
#     -fdata-sections
#     -fdata-sections 
#     -ffunction-sections
#     $<$<COMPILE_LANGUAGE:C>:-std=gnu99 -Wno-implicit-function-declaration>
#     $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-threadsafe-statics>
#     $<$<CONFIG:DEBUG>:-Og -g>
#     $<$<CONFIG:RELEASE>:-Os>
# )

# include(../cmake/GenerateBinary.cmake)
# generate_binary(msboot)