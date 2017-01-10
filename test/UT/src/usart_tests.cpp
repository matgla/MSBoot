#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "usart.hpp"

#include "mock.hpp"

class UsartTests : public ::testing::Test
{
    virtual void SetUp() {}
    virtual void TearDown()
    {
    }
};

TEST_F(UsartTests, initializationShouldSetGPIOAndNVIC)
{
    auto& mock = Mock::get();
    EXPECT_F_CALL(&RCC_AHB1PeriphClockCmd);
    hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    mock.verify();
}