file(GLOB_RECURSE SRCS
     *.cpp
)

file(GLOB_RECURSE PROD_SRCS
     "${PROJECT_SOURCE_DIR}/src/*.hpp"
     "${PROJECT_SOURCE_DIR}/inc/*.hpp"
     "${PROJECT_SOURCE_DIR}/src/memoryManagement.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/core")
message(${PROD_SRCS})
list(REMOVE_ITEM PROD_SRCS ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(romfs_core_tests ${SRCS} ${PROD_SRCS})

target_link_libraries(romfs_core_tests GTest)

install(TARGETS romfs_core_tests DESTINATION ${CMAKE_BINARY_DIR})
