//#include "fs/romfs/fileSystemHeader.hpp"
#include <unistd.h>
#include <cstring>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
// #include "stm32f4xx_rcc.h"
#include "kernel.hpp"
#include "logger.hpp"
// #include "usart.hpp"
#include "types.h"
#include "utils.h"
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

int main(void) 
{
    SystemInit();
    hardwareInitialize();

    initializeBoardLeds();
    // GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET);
    Logger logger("boot");
    logger << Level::INFO << "Bootloader started";

    while (1) {
    }
}


void assert_failed(u8* file, u32 line) 
{
    write(0, file, strlen((char*)file));
    write(0, ":", 1);
    char buf[10];
    itoa(line, buf, 10);
    write(0, buf, strlen(buf));
    write(0, " assertion failed!", 18);
    while(true)
    {

    }
}
