#include "stringify.hpp"

namespace std {
std::string to_string(GPIO_TypeDef*)
{
    return "gpio_typedef*";
}

std::string to_string(GPIO_InitTypeDef*)
{
    return "gpio_inittypedef*";
}

std::string to_string(NVIC_InitTypeDef*)
{
    return "nvic_inittypedef*";
}
}
