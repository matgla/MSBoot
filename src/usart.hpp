#include "utils.hpp"
#include <cstdint>
#include <system_stm32f4xx.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_gpio.h>

#include "buffer.hpp"
#include "messages.hpp"

#define USART_WAIT(USARTx) do { while (!((USARTx)->SR & USART_FLAG_TXE)); } while (0)
#define BUFFER_SIZE 100

void USART_GPIO_init(void);
void USART_NVIC_init(void);
void USART_init(void);
void usart_put(USART_TypeDef* USARTx, const char *str);

namespace hw
{
enum class USARTS
{
    USART1_PP1,
    USART2_PP1
};

template <USARTS UsartNumber>
class USART
{
public:
    static USART& getUsart();
    Buffer<BUFFER_SIZE>& getBuffer();
    void send(u8 fd, char ch);
    void send(u8 fd, char* str);
    Message getMessage();
private:
    USART();
    void init();
    void GPIOInit(u16 pin, u16 pinSource, u16 afUsart, GPIO_TypeDef* port);
    void NVICInit();
    void USARTInit();
    void InitClocks();


    GPIO_TypeDef* gpioPortRx_;
    GPIO_TypeDef* gpioPortTx_;
    u16 gpioPinRx_;
    u16 gpioPinTx_;
    u16 gpioPinSourceRx_;
    u16 gpioPinSourceTx_;

    u16 gpioAF_;

    u16 usartIrqn_;

    USART_TypeDef* USARTx_;

    Buffer<BUFFER_SIZE> buffer_;
};
}

extern "C"
{
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
}