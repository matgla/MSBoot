set(library_name msboot_modules_bootloader)

add_library(${library_name})
message (STATUS "Adding library: ${library_name}")

target_sources(${library_name}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/bootloader_module.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/bootloader_module.cpp
)

target_link_libraries(${library_name}
    PRIVATE
        eul
        gsl
        hal
)

target_include_directories(${library_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)