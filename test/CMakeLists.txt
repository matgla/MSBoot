include(ExternalProject)

# variables to help keep track of gtest paths
set(GTEST_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gtest")
set(GTEST_LOCATION "${GTEST_PREFIX}/src/GTestExternal-build")
set(GTEST_INCLUDES "${GTEST_PREFIX}/src/GTestExternal/include")

ExternalProject_Add(GTestExternal
    URL https://github.com/google/googletest/archive/release-1.7.0.zip
    PREFIX "${GTEST_PREFIX}"

    # cmake arguments
    CMAKE_ARGS -Dgtest_force_shared_crt=ON

    # Disable install step
    INSTALL_COMMAND ""

    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    )

# variables defining the import location properties for the generated gtest and
# gtestmain libraries
if (MSVC)
    set(GTEST_IMPORTED_LOCATION
        IMPORTED_LOCATION_DEBUG           "${GTEST_LOCATION}/Debug/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}"
        IMPORTED_LOCATION_RELEASE         "${GTEST_LOCATION}/Release/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}"
        )
    set(GTESTMAIN_IMPORTED_LOCATION
        IMPORTED_LOCATION_DEBUG           "${GTEST_LOCATION}/Debug/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}"
        IMPORTED_LOCATION_RELEASE         "${GTEST_LOCATION}/Release/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}"
        )
else()
    set(GTEST_IMPORTED_LOCATION
        IMPORTED_LOCATION                 "${GTEST_LOCATION}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}")
    set(GTESTMAIN_IMPORTED_LOCATION
        IMPORTED_LOCATION                 "${GTEST_LOCATION}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}")
endif()

# the gtest include directory exists only after it is build, but it is used/needed
# for the set_target_properties call below, so make it to avoid an error
file(MAKE_DIRECTORY ${GTEST_INCLUDES})

# define imported library GTest
add_library(GTest IMPORTED STATIC GLOBAL)
set_target_properties(GTest PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES     "${GTEST_INCLUDES}"
    IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
    ${GTEST_IMPORTED_LOCATION}
    )

# define imported library GTestMain
add_library(GTestMain IMPORTED STATIC GLOBAL)
set_target_properties(GTestMain PROPERTIES
    IMPORTED_LINK_INTERFACE_LIBRARIES GTest
    ${GTESTMAIN_IMPORTED_LOCATION}
    )

# make GTest depend on GTestExternal

include_directories(GTEST_INCLUDES)

add_dependencies(GTest GTestExternal)

add_subdirectory(os_tests)