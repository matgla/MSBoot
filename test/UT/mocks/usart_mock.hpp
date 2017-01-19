#pragma once

#include "mock.hpp"

#include "stm32f4xx_usart.h"

DECLARE_NICEMOCK_FUNCTION(ITStatus, USART_GetITStatus, USART_TypeDef*, uint16_t);
DECLARE_NICEMOCK_FUNCTION(FlagStatus, USART_GetFlagStatus, USART_TypeDef*, uint16_t);
DECLARE_NICEMOCK_VOID_FUNCTION(USART_SendData, USART_TypeDef*, uint16_t);

void expectSendData(u8 fd, char data)
{
    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
    EXPECT_CALL(USART_SendData, USART1, fd);
    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
    EXPECT_CALL(USART_SendData, USART1, 1);
    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
    EXPECT_CALL(USART_SendData, USART1, data);
    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
}

void expectSendData(u8 fd, const char* data)
{
    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
    EXPECT_CALL(USART_SendData, USART1, fd);
    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
    EXPECT_CALL(USART_SendData, USART1, strlen(data));
    for (int i = 0; i < strlen(data); ++i)
    {
        EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
        EXPECT_CALL(USART_SendData, USART1, data[i]);
    }
}