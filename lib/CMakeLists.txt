message(STATUS "Adding libraries")

unset(BUILD_TESTS CACHE)

if (NOT TARGET msmp)
    add_subdirectory(msmp)
endif ()

if (NOT TARGET eul)
    add_subdirectory(eul)
endif ()