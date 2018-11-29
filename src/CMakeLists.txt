set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(sources_path "${PROJECT_SOURCE_DIR}/src")
set(target_name "msboot")

add_executable(msboot)

target_sources(${target_name} PRIVATE
    ${sources_path}/main.cpp
)

add_subdirectory(app)
add_subdirectory(messages)

target_link_libraries(${target_name} PRIVATE msboot_app)

if (${arch} STREQUAL "ARM")
    message (STATUS "Configure specific ARM properties")
    set_target_properties(msboot PROPERTIES LINK_DEPENDS ${linker_script})

    include(GenerateBinary)
    generate_binary(msboot ${vendor})
else ()
endif ()

