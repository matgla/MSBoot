message(STATUS "Adding libraries")

unset(BUILD_TESTS CACHE)

include (../cmake/GitModules.cmake)

fetch_module_with_path(hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)
fetch_module_with_path(msmp ${CMAKE_CURRENT_SOURCE_DIR}/msmp)

execute_command("git submodule foreach git checkout master")
execute_command("git submodule foreach git pull")
