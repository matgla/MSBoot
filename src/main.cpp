//#include "fs/romfs/fileSystemHeader.hpp"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "kernel.hpp"
#include "logger.hpp"
#include "usart.hpp"
// #include "types.h"
// //#include <stdio.h>
// //#include "usart.hpp"
// #include "kernel.hpp"
// #include "logger.hpp"
// #include "usart.hpp"
// #include <cstdio>
// #include <cstdlib>

void initializeBoardLeds() {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

int main(void) {
    SystemInit();
    hardwareInitialize();
    initializeBoardLeds();
    GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET);
    //hardwareInitialize();
    Logger::log(Level::DEBUG, "main", "allocated %d bytes on %p");
    // int *a = (int *)myalloc(sizeof(int) * 10);

    // Logger::log(Level::DEBUG, "main", "allocated %d bytes on %p",
    //             sizeof(int) * 10, a);
    // myfree(a);
    // Logger::log(Level::DEBUG, "main", "end on %p", heap_end);
    // a = (int *)myalloc(sizeof(int) * 2);

    // Logger::log(Level::DEBUG, "main", "allocated %d bytes on %p",
    //             sizeof(int) * 2, a);
    // Logger::log(Level::DEBUG, "main", "end on %p", heap_end);

    while (1) {
    }
}


void assert_failed(u8* file, u32 line)
{
    while(true)
    {
    }

}
