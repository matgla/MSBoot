set(library_name "msboot_context")

add_library(${library_name})

target_sources(${library_name}
    PUBLIC
        # HPP
        ${CMAKE_CURRENT_SOURCE_DIR}/context.hpp
    PRIVATE
        # CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/context.cpp
)

target_include_directories(${library_name} PUBLIC "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(${library_name}
    PUBLIC
        hal

    PRIVATE
        msboot_core
)
