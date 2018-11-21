set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set (sources_path "${CMAKE_CURRENT_SOURCE_DIR}/")

set (sources
    ${sources_path}/main.cpp
)

include_directories(${sources_path})

add_executable(msboot ${sources})
target_link_libraries(msboot PUBLIC hal eul)

if (${arch} STREQUAL "ARM")
    message (STATUS "Configure specific ARM properties")
    set_target_properties(msboot PROPERTIES LINK_DEPENDS ${linker_script})

    include(GenerateBinary)
    generate_binary(msboot ${vendor})
else ()
endif ()

