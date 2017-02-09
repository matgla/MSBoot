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
    virtual void SetUp()
    {
        if (!hw::USART<hw::USARTS::USART1_PP1>::initialized())
        {
            expectInitialization();
        }
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
};

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

TEST_F(UsartShould, SendStringCorrectly)
{
    char EXPECTED_SEND_DATA[100] = "DataTo send\0";
    u8 EXPECTED_FD = 1;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    expectSendData(EXPECTED_FD, EXPECTED_SEND_DATA);

    usart.send(EXPECTED_FD, EXPECTED_SEND_DATA);
}