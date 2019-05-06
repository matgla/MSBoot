set(library_name msboot_core)

add_library(${library_name})

target_sources(${library_name}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/time_provider.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/stdout_stream.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/time_provider.cpp
)

target_include_directories(${library_name}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${library_name} eul hal)