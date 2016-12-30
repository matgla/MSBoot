#include "usart.hpp"

#include <cstdint>

#include <stm32f4xx_gpio.h>


void USART_GPIO_init() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpioInit;

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    gpioInit.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    gpioInit.GPIO_Mode = GPIO_Mode_AF;
    gpioInit.GPIO_OType = GPIO_OType_PP;
    gpioInit.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(GPIOA, &gpioInit);
}

void USART_NVIC_init() {
    NVIC_InitTypeDef init;
    init.NVIC_IRQChannel = USART1_IRQn;
    init.NVIC_IRQChannelCmd = ENABLE;
    init.NVIC_IRQChannelPreemptionPriority = 0;
    init.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&init);
}

void USART_init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitTypeDef USART_InitStruct;

    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);
    USART_Cmd(USART1, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void usart_put(USART_TypeDef *USARTx, const char *str) {

    /* Go through entire string */

    while (*str) {

        /* Wait to be ready, buffer empty */

        USART_WAIT(USARTx);

        /* Send data */

        USARTx->DR = (uint16_t)(*str++ & 0x01FF);

        /* Wait to be ready, buffer empty */

        USART_WAIT(USARTx);
    }
}
