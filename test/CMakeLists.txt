add_subdirectory(libs/googletest)

if (BUILD_TESTS)
    add_subdirectory(UT)
endif()