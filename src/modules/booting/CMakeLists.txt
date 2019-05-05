set(library_name msboot_modules_booting)

add_library(${library_name})
message (STATUS "Adding library: ${library_name}")

target_sources(${library_name}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/booting_events.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/booting_module.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/booting_module.cpp
)

target_link_libraries(${library_name}
    PRIVATE
        eul
)