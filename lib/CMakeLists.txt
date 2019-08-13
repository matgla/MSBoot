message(STATUS "Adding libraries")

unset(BUILD_TESTS CACHE)

include (../cmake/GitModules.cmake)

fetch_module_via_branch(lib/msmp ${PROJECT_SOURCE_DIR}/lib/msmp ${PROJECT_SOURCE_DIR} "master")
fetch_module_via_tag(lib/crcpp/crcpp ${PROJECT_SOURCE_DIR}/lib/crcpp ${PROJECT_SOURCE_DIR} "release-0.2.0.6")
