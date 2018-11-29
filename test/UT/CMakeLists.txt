enable_testing()

set(ut_source "${CMAKE_SOURCE_DIR}/test/UT")
set(binary_name "msboot_ut")

add_executable(${binary_name})

target_sources(${binary_name}
    PRIVATE
        ${ut_source}/empty.cpp
        ${ut_source}/main.cpp
)

target_include_directories(${binary_name} PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${binary_name} PRIVATE ${PROJECT_SOURCE_DIR}/test/UT)

target_include_directories(${binary_name} SYSTEM PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_include_directories(${binary_name} SYSTEM PRIVATE ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

set(testing_libs ${testing_libs} gmock gtest pthread)

target_link_libraries(${binary_name}
    PRIVATE
        ## testing libs
        gmock
        gtest
        pthread

        ## production
        msboot_messages
)
