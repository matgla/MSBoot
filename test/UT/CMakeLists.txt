include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

enable_testing()

file (GLOB_RECURSE SRCS src/*.c
                        src/*.cpp)

file (GLOB PROD_SRCS  ${PROJECT_SOURCE_DIR}/src/buffer.hpp
                      ${PROJECT_SOURCE_DIR}/src/logger.hpp
                      ${PROJECT_SOURCE_DIR}/src/logger.cpp
                      ${PROJECT_SOURCE_DIR}/src/utils.h
                      ${PROJECT_SOURCE_DIR}/src/types.h)
include_directories(${PROJECT_SOURCE_DIR}/src)
message ("Source dir: ${PROD_SRCS}")

file (GLOB_RECURSE STUB_SRCS ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.cpp
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.c
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.hpp
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.h)

include_directories(${PROJECT_SOURCE_DIR}/test/libs/CppFreeMock)
include_directories(${PROJECT_SOURCE_DIR}/test/UT/hw_stub/)

add_executable (bootloaderUTs ${SRCS} ${PROD_SRCS} ${STUB_SRCS})

target_link_libraries (bootloaderUTs gmock gtest gtest_main)