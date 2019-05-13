set (library_name msboot_modules_settings)
add_library(${library_name})

target_sources(${library_name}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/settings_module.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/settings_module.cpp
)

target_link_libraries(${library_name}
    PUBLIC
        eul
        hal
        gsl
)

target_include_directories(${library_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)