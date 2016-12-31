#include "utils.h"
#include <cstdint>
#include <system_stm32f4xx.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_gpio.h>

#define USART_WAIT(USARTx) do { while (!((USARTx)->SR & USART_FLAG_TXE)); } while (0)


void USART_GPIO_init(void);
void USART_NVIC_init(void);
void USART_init(void);
void usart_put(USART_TypeDef* USARTx, const char *str);	

namespace hw
{
enum class USARTS
{
    USART1_PP1,
    USART1_PP2,
    USART2_PP1,
    USART2_PP2
};

template <USARTS UsartNumber>
class USART
{
public:
    USART();
    void init();
private:
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
};
}