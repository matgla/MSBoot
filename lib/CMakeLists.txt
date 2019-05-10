message(STATUS "Adding libraries")

unset(BUILD_TESTS CACHE)

if (NOT TARGET msmp)
    add_subdirectory(msmp)
endif ()

if (NOT TARGET embedded_utility_libraries)
    add_subdirectory(eul)
endif ()