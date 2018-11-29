message(STATUS "Adding libraries")
remove_definitions(-DBUILD_TESTS)
add_subdirectory(gsl)
add_subdirectory(eul)