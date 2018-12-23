set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(sources_path "${PROJECT_SOURCE_DIR}/src")
set(target_name "msboot")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${target_name})

target_sources(${target_name} PRIVATE
    ${sources_path}/main.cpp
)

add_subdirectory(app)
add_subdirectory(request)

target_link_libraries(${target_name} PRIVATE msboot_app)

if (${arch} STREQUAL "ARM")
    message (STATUS "Configure specific ARM properties:")
    set_target_properties(${target_name} PROPERTIES LINK_DEPENDS ${linker_script})

    include(GenerateBinary)
    generate_binary(${target_name} ${vendor})
endif ()

