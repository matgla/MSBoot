#include "gtest/gtest.h"

#include "stm32f4xx_rcc.h"

#include "rcc_mock.hpp"

MOCK_VOID_FUNCTION(RCC_AHB1PeriphClockCmd, (a, b),
    (uint32_t a, FunctionalState b),
    uint32_t, FunctionalState);

MOCK_VOID_FUNCTION(RCC_APB2PeriphClockCmd, (a, b),
    (uint32_t a, FunctionalState b),
    uint32_t, FunctionalState);