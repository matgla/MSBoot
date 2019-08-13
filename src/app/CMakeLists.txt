set(sources_dir "${PROJECT_SOURCE_DIR}/src/app")
set(library_name "msboot_app")

add_library(${library_name})

target_sources(${library_name}
    PUBLIC
        # HPP
        ${sources_dir}/app.hpp
    PRIVATE
        # CPP
        ${sources_dir}/app.cpp
)

target_include_directories(${library_name} PUBLIC "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(${library_name}
    PUBLIC
        hal
        crcpp
        eul
        msmp_usart

    PRIVATE
        msboot_core
        msboot_context

)
