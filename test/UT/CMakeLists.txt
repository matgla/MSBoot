include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

file (GLOB_RECURSE SRCS src/*.c
                        src/*.cpp)

file (GLOB PROD_SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp
                     ${PROJECT_SOURCE_DIR}/src/*.hpp
                     ${PROJECT_SOURCE_DIR}/src/*.c
                     ${PROJECT_SOURCE_DIR}/src/*.h)

file (GLOB_RECURSE CPP_FREE_SRCS ${PROJECT_SOURCE_DIR}/test/libs/CppFreeMock/*.cpp
                                 ${PROJECT_SOURCE_DIR}/test/libs/CppFreeMock/*.hpp
                                 ${PROJECT_SOURCE_DIR}/test/libs/CppFreeMock/*.c
                                 ${PROJECT_SOURCE_DIR}/test/libs/CppFreeMock/*.h)

file (GLOB_RECURSE STUB_SRCS ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.cpp
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.c
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.hpp
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.h)

include_directories(${PROJECT_SOURCE_DIR}/test/libs/CppFreeMock)
include_directories(${PROJECT_SOURCE_DIR}/test/UT/hw_stub/)

# remove production main.cpp
list (REMOVE_ITEM PROD_SRCS ${PROJECT_SOURCE_DIR}/src/main.cpp)

if (NOT TARGET_NAME)
    set (TARGET_NAME, "bootloader_tests")
endif()

add_executable (${TARGET_NAME} ${SRCS} ${PROD_SRCS} ${STUB_SRCS})

target_link_libraries (${TARGET_NAME} pthread gtest gmock gtest_main)