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
        else
        {
            hw::USART<hw::USARTS::USART1_PP1>::getUsart().flush();
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

TEST_F(UsartShould, ShoudAckAfterReceive)
{
    const u16 EXPECTED_VALUE = 4;
    const u16 EXPECTED_SIZE = 1;
    USART1->DR = EXPECTED_SIZE;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    EXPECT_CALL(USART_GetITStatus, USART1, USART_IT_RXNE).willReturn(SET);
    USART1_IRQHandler();

    USART1->DR = EXPECTED_VALUE;
    EXPECT_CALL(USART_GetITStatus, USART1, USART_IT_RXNE).willReturn(SET);

    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
    EXPECT_CALL(USART_SendData, USART1, static_cast<u8>(Messages::ACK));
    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);

    USART1_IRQHandler();

    EXPECT_EQ(usart.getBuffer().size(), 2);
    EXPECT_EQ(usart.getBuffer().getByte(), EXPECTED_SIZE);
    EXPECT_EQ(usart.getBuffer().getByte(), EXPECTED_VALUE);
    EXPECT_EQ(usart.getBuffer().size(), 0);
}

TEST_F(UsartShould, SendByteCorrectly)
{
    char EXPECTED_SEND_DATA = 156;
    u8 EXPECTED_FD = 1;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    expectSendData(EXPECTED_FD, EXPECTED_SEND_DATA);
    usart.getBuffer().write(static_cast<u8>(Messages::ACK));

    usart.send(EXPECTED_SEND_DATA);
}

TEST_F(UsartShould, SendStringCorrectly)
{
    char EXPECTED_SEND_DATA[100] = "DataTo send\0";
    u8 EXPECTED_FD = 1;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    usart.getBuffer().write(static_cast<u8>(Messages::ACK));
    expectSendData(EXPECTED_FD, EXPECTED_SEND_DATA);

    usart.send(EXPECTED_SEND_DATA);
}

TEST_F(UsartShould, SendDataCorrectlyWhenBufferIsNotEmpty)
{
    char DATA_IN_BUFFER[15] = "1Ab2a\0";
    char EXPECTED_SEND_DATA[15] = "DataTo send\0";
    u8 EXPECTED_FD = 1;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();
    usart.getBuffer().write(DATA_IN_BUFFER);

    usart.getBuffer().write(static_cast<u8>(Messages::ACK));

    expectSendData(EXPECTED_FD, EXPECTED_SEND_DATA);

    usart.send(EXPECTED_SEND_DATA);

    std::string data;

    while (usart.getBuffer().size())
    {
        data += usart.getBuffer().getByte();
    }

    EXPECT_EQ(DATA_IN_BUFFER, data);
}

TEST_F(UsartShould, SendDataCorrectlyWhenDataArriveAfterAck)
{
    char DATA_IN_BUFFER[15] = "1Ab2a\0";
    char DATA_AFTER_ACK[15] = "aaabsd\0";
    char EXPECTED_SEND_DATA[15] = "DataTo send\0";
    std::string EXPECTED_OUTPUT = DATA_IN_BUFFER;
    EXPECTED_OUTPUT += DATA_AFTER_ACK;
    u8 EXPECTED_FD = 1;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();
    usart.getBuffer().write(DATA_IN_BUFFER);

    usart.getBuffer().write(static_cast<u8>(Messages::ACK));

    usart.getBuffer().write(DATA_AFTER_ACK);

    expectSendData(EXPECTED_FD, EXPECTED_SEND_DATA);

    usart.send(EXPECTED_SEND_DATA);

    std::string data;

    while (usart.getBuffer().size())
    {
        data += usart.getBuffer().getByte();
    }

    EXPECT_EQ(EXPECTED_OUTPUT, data);
}