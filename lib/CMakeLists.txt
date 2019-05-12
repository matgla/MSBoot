message(STATUS "Adding libraries")

unset(BUILD_TESTS CACHE)

include (../cmake/GitModules.cmake)

fetch_module_with_path(lib/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal ${PROJECT_SOURCE_DIR})
fetch_module_with_path(lib/msmp ${CMAKE_CURRENT_SOURCE_DIR}/msmp ${PROJECT_SOURCE_DIR})

execute_command("git submodule foreach git checkout master" ${PROJECT_SOURCE_DIR})
execute_command("git submodule foreach git pull" ${PROJECT_SOURCE_DIR})
