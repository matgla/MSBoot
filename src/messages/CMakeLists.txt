set(sources_dir "${PROJECT_SOURCE_DIR}/src/messages")
set(library_name "msboot_messages")

add_library(${library_name})

target_sources(${library_name}
    PUBLIC
        # HPP
        ${sources_dir}/handshake.hpp
    PRIVATE
        # CPP
        ${sources_dir}/handshake.cpp
)

target_include_directories(${library_name} PRIVATE "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(${library_name}
    PUBLIC
        gsl
)
