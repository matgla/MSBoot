set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set (sources_path "${CMAKE_CURRENT_SOURCE_DIR}/")

set (sources
    ${sources_path}/main.cpp
)

include_directories(${sources_path})

add_executable(msboot ${sources})
target_link_libraries(msboot hal eul)

if (${arch} STREQUAL "ARM")

    target_compile_options(msboot PRIVATE
        -fno-builtin
        -fdata-sections
        -fdata-sections
        -ffunction-sections
        $<$<COMPILE_LANGUAGE:C>:-std=gnu99 -Wno-implicit-function-declaration>
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fconcepts -fno-threadsafe-statics>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
    )

    set_target_properties(msboot PROPERTIES LINK_DEPENDS ${linker_script})

    include(../cmake/GenerateBinary.cmake)
    generate_binary(msboot)
else ()
    target_compile_options(msboot PRIVATE
        $<$<COMPILE_LANGUAGE:C>:-std=gnu99>
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z -fconcepts -Wall -Werror>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
    )
endif ()

