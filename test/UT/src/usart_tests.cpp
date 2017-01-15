#include "stm32f4xx_usart.h"

#include "gtest/gtest.h"

#include "gpio_mock.hpp"
#include "misc_mock.hpp"
#include "rcc_mock.hpp"

#include "usart.hpp"

class UsartShould : public ::testing::Test {
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(UsartShould, correctInitializePeripherials)
{
    auto& rccAhb1Mock = GET_MOCK(RCC_AHB1PeriphClockCmd);
    auto& rccApb2Mock = GET_MOCK(RCC_APB2PeriphClockCmd);
    auto& gpioPinAfMock = GET_MOCK(GPIO_PinAFConfig);
    auto& gpioInitMock = GET_MOCK(GPIO_Init);
    auto& nvicInitMock = GET_MOCK(NVIC_Init);

    EXPECT_CALL(rccAhb1Mock, RCC_AHB1Periph_GPIOA, ENABLE);
    EXPECT_CALL(rccApb2Mock, RCC_APB2Periph_USART1, ENABLE);

    EXPECT_CALL(gpioPinAfMock, GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

    //EXPECT_CALL(gpioPinAfMock, GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

    GPIO_InitTypeDef expectedGpioInitialization;
    expectedGpioInitialization.GPIO_Pin = GPIO_Pin_9;
    expectedGpioInitialization.GPIO_Mode = GPIO_Mode_AF;
    expectedGpioInitialization.GPIO_OType = GPIO_OType_PP;
    expectedGpioInitialization.GPIO_Speed = GPIO_Low_Speed;
    expectedGpioInitialization.GPIO_PuPd = GPIO_PuPd_UP;
    EXPECT_CALL(gpioInitMock, GPIOA, &expectedGpioInitialization);

    GPIO_InitTypeDef expectedGpio2Initialization;
    expectedGpio2Initialization.GPIO_Pin = GPIO_Pin_10;
    expectedGpio2Initialization.GPIO_Mode = GPIO_Mode_AF;
    expectedGpio2Initialization.GPIO_OType = GPIO_OType_PP;
    expectedGpio2Initialization.GPIO_Speed = GPIO_Low_Speed;
    expectedGpio2Initialization.GPIO_PuPd = GPIO_PuPd_UP;

    EXPECT_CALL(gpioPinAfMock, GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    EXPECT_CALL(gpioInitMock, GPIOA, &expectedGpio2Initialization);

    hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    rccAhb1Mock.verify();
    rccApb2Mock.verify();
}