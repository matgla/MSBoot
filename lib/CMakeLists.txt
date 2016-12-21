include_directories("inc/core")
include_directories("inc/peripherals")

file(GLOB_RECURSE LIB_SRCS "*.c")

add_library(stm32 ${LIB_SRCS})