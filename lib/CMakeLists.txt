message(STATUS "Adding libraries")

unset(BUILD_TESTS CACHE)

include (../cmake/GitModules.cmake)

fetch_module_with_path(lib/msmp ${CMAKE_CURRENT_SOURCE_DIR}/msmp ${PROJECT_SOURCE_DIR})
