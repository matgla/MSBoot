#include "stm32f4xx_usart.h"

#include <vector>

#include "mock.hpp"

USART_TypeDef usart1;

NICEMOCK_FUNCTION(ITStatus, USART_GetITStatus, USART_TypeDef*, uint16_t);
NICEMOCK_FUNCTION(FlagStatus, USART_GetFlagStatus, USART_TypeDef*, uint16_t);
NICEMOCK_VOID_FUNCTION(USART_SendData, USART_TypeDef*, uint16_t);

void USART_DeInit(USART_TypeDef* USARTx)
{
}

void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
}

void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
}

void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
}

void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
}

void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler)
{
}

void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
}

void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
}

void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp)
{
}

void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength)
{
}

void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_SendBreak(USART_TypeDef* USARTx)
{
}

void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime)
{
}

void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode)
{
}

void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState)
{
}

void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState)
{
}

void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
}


void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT)
{
}
