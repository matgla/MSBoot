#include "utils.h"
#include <system_stm32f4xx.h>
#include <stm32f4xx_gpio.h>

#define USART_WAIT(USARTx) do { while (!((USARTx)->SR & USART_FLAG_TXE)); } while (0)

void USART_GPIO_init(void);
void USART_NVIC_init(void);
void USART_init(void);
void usart_put(USART_TypeDef* USARTx, char *str);	

