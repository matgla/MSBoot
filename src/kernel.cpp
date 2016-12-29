#include "kernel.hpp"
#include "usart.hpp"

void hardwareInitialize() {
    USART_GPIO_init();
    USART_NVIC_init();
    USART_init();
    USART_SendData(USART1, ' ');
    USART_SendData(USART1, ' ');
}
