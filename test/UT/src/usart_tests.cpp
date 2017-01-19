#include "stm32f4xx_usart.h"

#include "gtest/gtest.h"

#include "gpio_mock.hpp"
#include "misc_mock.hpp"
#include "rcc_mock.hpp"

#include "usart.hpp"

class UsartShould : public ::testing::Test
{
  public:
    GET_TYPE_MOCK(RCC_AHB1PeriphClockCmd) & rccAhb1Mock;
    GET_TYPE_MOCK(RCC_APB2PeriphClockCmd) & rccApb2Mock;
    GET_TYPE_MOCK(GPIO_PinAFConfig) & gpioPinAfMock;
    GET_TYPE_MOCK(GPIO_Init) & gpioInitMock;
    GET_TYPE_MOCK(NVIC_Init) & nvicInitMock;

    UsartShould()
        : rccAhb1Mock(GET_MOCK(RCC_AHB1PeriphClockCmd)), rccApb2Mock(GET_MOCK(RCC_APB2PeriphClockCmd)), gpioPinAfMock(GET_MOCK(GPIO_PinAFConfig)), gpioInitMock(GET_MOCK(GPIO_Init)), nvicInitMock(GET_MOCK(NVIC_Init))
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
        rccAhb1Mock.verify();
        rccApb2Mock.verify();
        gpioPinAfMock.verify();
        gpioInitMock.verify();
        nvicInitMock.verify();
    }

    void expectClocksConfiguration()
    {
        EXPECT_CALL(rccAhb1Mock, RCC_AHB1Periph_GPIOA, ENABLE);
        EXPECT_CALL(rccApb2Mock, RCC_APB2Periph_USART1, ENABLE);
    }

    GPIO_InitTypeDef expectedGpioInitialization;
    GPIO_InitTypeDef expectedGpio2Initialization;
    NVIC_InitTypeDef init;

    void expectGpioInit()
    {
        EXPECT_CALL(gpioPinAfMock, GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

        expectedGpioInitialization.GPIO_Pin = GPIO_Pin_9;
        expectedGpioInitialization.GPIO_Mode = GPIO_Mode_AF;
        expectedGpioInitialization.GPIO_OType = GPIO_OType_PP;
        expectedGpioInitialization.GPIO_Speed = GPIO_Low_Speed;
        expectedGpioInitialization.GPIO_PuPd = GPIO_PuPd_UP;
        EXPECT_CALL(gpioInitMock, GPIOA, &expectedGpioInitialization);

        expectedGpio2Initialization.GPIO_Pin = GPIO_Pin_10;
        expectedGpio2Initialization.GPIO_Mode = GPIO_Mode_AF;
        expectedGpio2Initialization.GPIO_OType = GPIO_OType_PP;
        expectedGpio2Initialization.GPIO_Speed = GPIO_Low_Speed;
        expectedGpio2Initialization.GPIO_PuPd = GPIO_PuPd_UP;

        EXPECT_CALL(gpioPinAfMock, GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
        EXPECT_CALL(gpioInitMock, GPIOA, &expectedGpio2Initialization);
    }

    void expectNvicInit()
    {
        init.NVIC_IRQChannel = USART1_IRQn;
        init.NVIC_IRQChannelCmd = ENABLE;
        init.NVIC_IRQChannelPreemptionPriority = 6;
        init.NVIC_IRQChannelSubPriority = 0;

        EXPECT_CALL(nvicInitMock, &init);
    }
};

TEST_F(UsartShould, correctInitializePeripherials)
{
    expectClocksConfiguration();
    expectGpioInit();
    expectNvicInit();

    hw::USART<hw::USARTS::USART1_PP1>::getUsart();
}