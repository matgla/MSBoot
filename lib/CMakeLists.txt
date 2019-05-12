message(STATUS "Adding libraries")

unset(BUILD_TESTS CACHE)

include (../cmake/GitModules.cmake)

fetch_module(hal)
fetch_module(msmp)

execute_command("git submodule foreach git checkout master")
execute_command("git submodule foreach git pull")
