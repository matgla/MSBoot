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
    SAFE_MOCK(RCC_AHB1PeriphClockCmd, rcc1Mock_);
    SAFE_MOCK(RCC_APB2PeriphClockCmd, rcc2Mock_);
    SAFE_MOCK(GPIO_PinAFConfig, gpioAfMock_);
    SAFE_MOCK(GPIO_Init, gpioInitMock_);
    SAFE_MOCK(NVIC_Init, nvicInitMock_);
    SAFE_MOCK(USART_SendData, usartSendMock_);
    SAFE_MOCK(USART_GetFlagStatus, usartGetFlagMock_);
    SAFE_MOCK(USART_GetITStatus, usartGetItMock_);

    UsartShould()
        : rcc1Mock_(GET_MOCK(RCC_AHB1PeriphClockCmd)),
          rcc2Mock_(GET_MOCK(RCC_APB2PeriphClockCmd)),
          gpioAfMock_(GET_MOCK(GPIO_PinAFConfig)),
          gpioInitMock_(GET_MOCK(GPIO_Init)),
          nvicInitMock_(GET_MOCK(NVIC_Init)),
          usartSendMock_(GET_MOCK(USART_SendData)),
          usartGetFlagMock_(GET_MOCK(USART_GetFlagStatus)),
          usartGetItMock_(GET_MOCK(USART_GetITStatus))
    {
    }


    virtual void SetUp()
    {
        if (!hw::USART<hw::USARTS::USART1_PP1>::initialized())
        {
            expectInitialization();
        }
    }

    virtual void TearDown()
    {
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