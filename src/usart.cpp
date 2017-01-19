#include "usart.hpp"
#include "utils.hpp"

#include <cstdint>

void usart_put(USART_TypeDef* USARTx, const char* str)
{

    /* Go through entire string */

    while (*str)
    {

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

bool wasUsart1Initialized = false;

template <USARTS UsartNumber>
USART<UsartNumber>& USART<UsartNumber>::getUsart()
{
    static_assert(sizeof(UsartNumber) == 0, "Method needs to be specialized");
    static USART s;
    return s;
}

template <USARTS UsartNumber>
Buffer<BUFFER_SIZE>& USART<UsartNumber>::getBuffer()
{
    return buffer_;
}

template <USARTS UsartNumber>
void USART<UsartNumber>::send(u8 fd, char ch)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    };
    USART_SendData(USARTx_, fd);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    };
    USART_SendData(USARTx_, 1);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    };
    USART_SendData(USARTx_, ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    };
}

template <USARTS UsartNumber>
void USART<UsartNumber>::send(u8 fd, char* str)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    };
    USART_SendData(USARTx_, fd);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    };
    USART_SendData(USARTx_, strlen(str));
    for (int i = 0; i < strlen(str); ++i)
    {
        while (USART_GetFlagStatus(USARTx_, USART_FLAG_TC) == RESET)
        {
        };
        USART_SendData(USARTx_, str[i]);
    }
}

template <USARTS UsartNumber>
Message USART<UsartNumber>::getMessage()
{
    Message msg;
    msg.size_ = 1;
    int index = 0;
    bool receivedSize = false;
    bool receivedFd = false;
    while (index < msg.size_)
    {
        if (getBuffer().size())
        {
            if (!receivedFd)
            {
                msg.fd_ = getBuffer().getByte();
                receivedFd = true;
                continue;
            }

            if (!receivedSize)
            {
                msg.size_ = getBuffer().getByte();
                receivedSize = true;
                continue;
            }

            msg.payload_[index++] = getBuffer().getByte();
        }
    }

    return msg;
}

template <USARTS UsartNumber>
USART<UsartNumber>::USART()
{
    static_assert(sizeof(UsartNumber) == 0, "Method needs to be specialized");
}

template <USARTS UsartNumber>
bool USART<UsartNumber>::initialized()
{
    static_assert(sizeof(UsartNumber) == 0, "Method needs to be specialized");
    return false;
}

template <USARTS UsartNumber>
void USART<UsartNumber>::init()
{
    USART_DeInit(USARTx_);
    InitClocks();
    GPIOInit(gpioPinTx_, gpioPinSourceTx_, gpioAF_, gpioPortTx_);
    GPIOInit(gpioPinRx_, gpioPinSourceRx_, gpioAF_, gpioPortRx_);
    NVICInit();
    USARTInit();
}

template <USARTS UsartNumber>
void USART<UsartNumber>::GPIOInit(u16 pin, u16 pinSource, u16 afUsart, GPIO_TypeDef* port)
{
    GPIO_InitTypeDef gpioInit;

    GPIO_PinAFConfig(port, pinSource, afUsart);

    gpioInit.GPIO_Pin = pin;
    gpioInit.GPIO_Mode = GPIO_Mode_AF;
    gpioInit.GPIO_OType = GPIO_OType_PP;
    gpioInit.GPIO_Speed = GPIO_Low_Speed;
    gpioInit.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(port, &gpioInit);
}

uint8_t getSubPriority(USART_TypeDef* USARTx)
{
    if (USARTx == USART1)
        return 0;
    if (USARTx == USART2)
        return 1;
    if (USARTx == USART3)
        return 2;
    return 0;
}

template <USARTS UsartNumber>
void USART<UsartNumber>::NVICInit()
{
    NVIC_InitTypeDef init;
    init.NVIC_IRQChannel = usartIrqn_;
    init.NVIC_IRQChannelCmd = ENABLE;
    init.NVIC_IRQChannelPreemptionPriority = 6;
    init.NVIC_IRQChannelSubPriority = getSubPriority(USARTx_);
    NVIC_Init(&init);
}

template <USARTS UsartNumber>
void USART<UsartNumber>::USARTInit()
{
    USART_InitTypeDef USART_InitStruct;

    USART_InitStruct.USART_BaudRate = 128000;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USARTx_, &USART_InitStruct);
    USART_ITConfig(USARTx_, USART_IT_RXNE, ENABLE);
    USART_Cmd(USARTx_, ENABLE);
}

template <USARTS UsartNumber>
void USART<UsartNumber>::InitClocks()
{
    static_assert(sizeof(UsartNumber) == 0, "Method needs to be specialized");
}

/////////////////////////////////////////////
//     specializations for USART1_PP1
/////////////////////////////////////////////
template <>
USART<USARTS::USART1_PP1>::USART()
    : gpioPortRx_(GPIOA), gpioPortTx_(GPIOA), gpioPinRx_(GPIO_Pin_10), gpioPinTx_(GPIO_Pin_9), gpioPinSourceRx_(GPIO_PinSource10), gpioPinSourceTx_(GPIO_PinSource9), gpioAF_(GPIO_AF_USART1), usartIrqn_(USART1_IRQn)
{
    USARTx_ = USART1;
    init();
}

template <>
USART<USARTS::USART1_PP1>& USART<USARTS::USART1_PP1>::getUsart()
{
    static USART s1;
    wasUsart1Initialized = true;
    return s1;
}

template <>
bool USART<USARTS::USART1_PP1>::initialized()
{
    return wasUsart1Initialized;
}

template <>
void USART<USARTS::USART1_PP1>::InitClocks()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

/////////////////////////////////////////////
//     specializations for USART2_PP1
/////////////////////////////////////////////
template <>
USART<USARTS::USART2_PP1>::USART()
    : gpioPortRx_(GPIOB), gpioPortTx_(GPIOB), gpioPinRx_(GPIO_Pin_11), gpioPinTx_(GPIO_Pin_10), gpioPinSourceRx_(GPIO_PinSource11), gpioPinSourceTx_(GPIO_PinSource10), gpioAF_(GPIO_AF_USART3), usartIrqn_(USART3_IRQn)
{
    USARTx_ = USART3;
    init();
}

bool wasUsart2Initialized = false;

template <>
USART<USARTS::USART2_PP1>& USART<USARTS::USART2_PP1>::getUsart()
{
    static USART s2;
    wasUsart2Initialized = true;
    return s2;
}

template <>
bool USART<USARTS::USART2_PP1>::initialized()
{
    return wasUsart2Initialized;
}

template <>
void USART<USARTS::USART2_PP1>::InitClocks()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
}

template class
    USART<USARTS::USART1_PP1>;

template class
    USART<USARTS::USART2_PP1>;
}
// volatile u8 flag =0;
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        char c = USART1->DR;
        hw::USART<hw::USARTS::USART1_PP1>::getUsart().getBuffer().write(c);
    }
}

void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        char c = USART2->DR;
        hw::USART<hw::USARTS::USART2_PP1>::getUsart().getBuffer().write(c);
    }
}
