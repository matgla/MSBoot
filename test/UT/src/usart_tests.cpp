#include "stm32f4xx_usart.h"

#include "gtest/gtest.h"

#include "gpio_mock.hpp"
#include "misc_mock.hpp"
#include "rcc_mock.hpp"
#include "usart_mock.hpp"

#include "usart.hpp"

class UsartShould : public ::testing::Test
{
  public:
    UsartShould()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
        VERIFY_MOCK(RCC_AHB1PeriphClockCmd);
        VERIFY_MOCK(RCC_APB2PeriphClockCmd);
        VERIFY_MOCK(GPIO_PinAFConfig);
        VERIFY_MOCK(GPIO_Init);
        VERIFY_MOCK(NVIC_Init);
        VERIFY_MOCK(USART_SendData);
        VERIFY_MOCK(USART_GetFlagStatus);
        VERIFY_MOCK(USART_GetITStatus);
    }

    void expectClocksConfiguration()
    {
        EXPECT_CALL(RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOA, ENABLE);
        EXPECT_CALL(RCC_APB2PeriphClockCmd, RCC_APB2Periph_USART1, ENABLE);
    }

    GPIO_InitTypeDef expectedGpioInitialization;
    GPIO_InitTypeDef expectedGpio2Initialization;
    NVIC_InitTypeDef init;

    void expectGpioInit()
    {
        EXPECT_CALL(GPIO_PinAFConfig, GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

        expectedGpioInitialization.GPIO_Pin = GPIO_Pin_9;
        expectedGpioInitialization.GPIO_Mode = GPIO_Mode_AF;
        expectedGpioInitialization.GPIO_OType = GPIO_OType_PP;
        expectedGpioInitialization.GPIO_Speed = GPIO_Low_Speed;
        expectedGpioInitialization.GPIO_PuPd = GPIO_PuPd_UP;
        EXPECT_CALL(GPIO_Init, GPIOA, &expectedGpioInitialization);

        expectedGpio2Initialization.GPIO_Pin = GPIO_Pin_10;
        expectedGpio2Initialization.GPIO_Mode = GPIO_Mode_AF;
        expectedGpio2Initialization.GPIO_OType = GPIO_OType_PP;
        expectedGpio2Initialization.GPIO_Speed = GPIO_Low_Speed;
        expectedGpio2Initialization.GPIO_PuPd = GPIO_PuPd_UP;

        EXPECT_CALL(GPIO_PinAFConfig, GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
        EXPECT_CALL(GPIO_Init, GPIOA, &expectedGpio2Initialization);
    }

    void expectNvicInit()
    {
        init.NVIC_IRQChannel = USART1_IRQn;
        init.NVIC_IRQChannelCmd = ENABLE;
        init.NVIC_IRQChannelPreemptionPriority = 6;
        init.NVIC_IRQChannelSubPriority = 0;

        EXPECT_CALL(NVIC_Init, &init);
    }

    void expectInitialization()
    {
        expectClocksConfiguration();
        expectGpioInit();
        expectNvicInit();
    }
};

// CAUTION this test must be first, because USART class is singleton
TEST_F(UsartShould, InitializeHardwareCorrectly)
{
    expectInitialization();

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();
}

TEST_F(UsartShould, HandleIrqRequestCorrect)
{
    const u16 EXPECTED_VALUE = 4;
    USART1->DR = EXPECTED_VALUE;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();
    EXPECT_CALL(USART_GetITStatus, USART1, USART_IT_RXNE).willReturn(RESET);
    USART1_IRQHandler();
    EXPECT_EQ(usart.getBuffer().size(), 0);

    EXPECT_CALL(USART_GetITStatus, USART1, USART_IT_RXNE).willReturn(SET);
    USART1_IRQHandler();
    EXPECT_EQ(usart.getBuffer().size(), 1);
    EXPECT_EQ(usart.getBuffer().getByte(), EXPECTED_VALUE);
    EXPECT_EQ(usart.getBuffer().size(), 0);
}

TEST_F(UsartShould, SendByteCorrectly)
{
    char EXPECTED_SEND_DATA = 156;
    u8 EXPECTED_FD = 1;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    expectSendData(EXPECTED_FD, EXPECTED_SEND_DATA);

    usart.send(EXPECTED_FD, EXPECTED_SEND_DATA);
}