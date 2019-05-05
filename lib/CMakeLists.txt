message(STATUS "Adding libraries")

unset(BUILD_TESTS CACHE)

if (BUILD_TESTS)
    message(FATAL_ERROR "Before ells")
endif ()

if (NOT TARGET crcpp)
    add_subdirectory(crcpp)
endif ()

if (NOT TARGET msmp)
    add_subdirectory(msmp/msmp)
endif ()