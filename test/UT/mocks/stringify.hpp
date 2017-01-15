#pragma once

#include <string>

#include "misc.h"
#include "stm32f4xx_gpio.h"

namespace std {
std::string to_string(GPIO_TypeDef*);

std::string to_string(GPIO_InitTypeDef*);

std::string to_string(NVIC_InitTypeDef*);
}
