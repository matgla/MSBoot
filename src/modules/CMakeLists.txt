set (library_name msboot_modules)

add_library (${library_name} INTERFACE)

add_subdirectory(booting)

target_link_libraries(${library_name}
    INTERFACE
        msboot_modules_booting
)