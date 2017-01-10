#include "stm32f4xx_rcc.h"

#include "mock.hpp"

void RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState)
{
    Mock::get().call(&RCC_AHB1PeriphClockCmd, __FUNCTION__);
}

void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{

}