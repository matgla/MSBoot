#include "stm32f4xx_gpio.h"

#include "gpio_mock.hpp"

MOCK_VOID_FUNCTION(GPIO_PinAFConfig, (a, b, c),
    (GPIO_TypeDef * a, uint16_t b, uint8_t c),
    GPIO_TypeDef*, uint16_t, uint8_t);

MOCK_VOID_FUNCTION(GPIO_Init, (a, b), (GPIO_TypeDef * a, GPIO_InitTypeDef* b),
    GPIO_TypeDef*, GPIO_InitTypeDef*);