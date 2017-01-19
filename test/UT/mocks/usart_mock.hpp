#pragma once

#include "mock.hpp"

#include "stm32f4xx_usart.h"


DECLARE_NICEMOCK_FUNCTION(ITStatus, USART_GetITStatus, USART_TypeDef*, uint16_t);
DECLARE_NICEMOCK_FUNCTION(FlagStatus, USART_GetFlagStatus, USART_TypeDef*, uint16_t);
DECLARE_NICEMOCK_VOID_FUNCTION(USART_SendData, USART_TypeDef*, uint16_t);

void expectSendData(u8 fd, char data);
void expectSendData(u8 fd, const char* data);
void expectClocksConfiguration();
void expectGpioInit();
void expectNvicInit();
void expectInitialization();
