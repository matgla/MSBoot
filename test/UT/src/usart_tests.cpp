#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "usart.hpp"

class UsartTests : public ::testing::Test
{
    virtual void SetUp() {}
    virtual void TearDown()
    {
    }
};

TEST_F(UsartTests, initializationShouldSetGPIOAndNVIC)
{
    hw::USART<hw::USARTS::USART1_PP1>::getUsart();
}