include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

enable_testing()

file (GLOB_RECURSE SRCS src/*.c
                        src/*.cpp)

file (GLOB PROD_SRCS "")

file (GLOB_RECURSE STUB_SRCS ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.cpp
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.c
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.hpp
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.h)

include_directories(${PROJECT_SOURCE_DIR}/test/libs/CppFreeMock)
include_directories(${PROJECT_SOURCE_DIR}/test/UT/hw_stub/)

# remove production main.cpp
list (REMOVE_ITEM PROD_SRCS ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable (bootloaderUTs ${SRCS} ${PROD_SRCS} ${STUB_SRCS})

target_link_libraries (bootloaderUTs gmock gtest gtest_main)