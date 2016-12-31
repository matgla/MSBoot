#include "usart.hpp"

#include <cstdint>

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

namespace hw
{

template<USARTS UsartNumber>
USART<UsartNumber>::USART()
{
}

template<USARTS UsartNumber>
void USART<UsartNumber>::init()
{
    InitClocks();
    GPIOInit(gpioPinRx_, gpioPinSourceRx_, gpioAF_, gpioPortRx_);
    GPIOInit(gpioPinTx_, gpioPinSourceTx_, gpioAF_, gpioPortTx_);
    NVICInit();
    USARTInit();
}

template<USARTS UsartNumber>
void USART<UsartNumber>::GPIOInit(u16 pin, u16 pinSource, u16 afUsart, GPIO_TypeDef* port)
{
    GPIO_InitTypeDef gpioInit;

    GPIO_PinAFConfig(port, pinSource, afUsart);

    gpioInit.GPIO_Pin = pin;
    gpioInit.GPIO_Mode = GPIO_Mode_AF;
    gpioInit.GPIO_OType = GPIO_OType_PP;
    gpioInit.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(port, &gpioInit);
}

template<USARTS UsartNumber>
void USART<UsartNumber>::NVICInit()
{
    NVIC_InitTypeDef init;
    init.NVIC_IRQChannel = usartIrqn_;
    init.NVIC_IRQChannelCmd = ENABLE;
    init.NVIC_IRQChannelPreemptionPriority = 0;
    init.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&init);
}

template<USARTS UsartNumber>
void USART<UsartNumber>::USARTInit()
{
    USART_InitTypeDef USART_InitStruct;

    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USARTx_, &USART_InitStruct);
    USART_Cmd(USARTx_, ENABLE);
    USART_ITConfig(USARTx_, USART_IT_RXNE, ENABLE);
}

template <USARTS UsartNumber>
void USART<UsartNumber>::InitClocks()
{
}

// specializations

template <>
USART<USARTS::USART1_PP1>::USART() : 
    gpioPortRx_(GPIOA),
    gpioPortTx_(GPIOA),
    gpioPinRx_(GPIO_Pin_10),
    gpioPinTx_(GPIO_Pin_9),
    gpioPinSourceRx_(GPIO_PinSource10),
    gpioPinSourceTx_(GPIO_PinSource9),
    gpioAF_(GPIO_AF_USART1),
    usartIrqn_(USART1_IRQn)
{
    USARTx_ = USART1;
}

template <>
USART<USARTS::USART2_PP1>::USART():
    gpioPortRx_(GPIOA),
    gpioPortTx_(GPIOA),
    gpioPinRx_(GPIO_Pin_3),
    gpioPinTx_(GPIO_Pin_2),
    gpioPinSourceRx_(GPIO_PinSource3),
    gpioPinSourceTx_(GPIO_PinSource2),
    gpioAF_(GPIO_AF_USART2),
    usartIrqn_(USART2_IRQn)
{
    USARTx_ = USART2;
}


template <>
void USART<USARTS::USART1_PP1>::InitClocks()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

template <>
void USART<USARTS::USART2_PP1>::InitClocks()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
}

template class
USART<USARTS::USART1_PP1>;

template class
USART<USARTS::USART2_PP1>;

}

