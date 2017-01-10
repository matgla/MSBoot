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
#include "utils.hpp"
#include "bootloader.hpp"
// //#include <stdio.h>
// //#include "usart.hpp"
// #include "kernel.hpp"
// #include "logger.hpp"
// #include "usart.hpp"
// #include <cstdio>
// #include <cstdlib>
#include "usart.hpp"


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
    //hw::USART<hw::USARTS::USART2_PP1>::getUsart();
    hw::USART<hw::USARTS::USART1_PP1>::getUsart();
    //u1.init();

    Logger logger("boot");
    initializeBoardLeds();
    GPIO_SetBits(GPIOD, GPIO_Pin_14);


    hardwareInitialize();

    BootLoader bl(logger);
    logger << Level::INFO << "Bootloader started\r\n";

    if (bl.specialMode())
    {
        logger << Level::INFO << "Boot in special mode\r\n";
        bl.bootSpecialMode();
    }
    else
    {
        logger << Level::INFO << "Boot FW\r\n";
        bl.bootFW();
    }

    while (1) {

    }

}


void assert_failed(u8* file, u32 line)
{
    write(0, file, strlen((char*)file));
    write(0, ":", 1);
    char buf[10];
    utils::itoa(line, buf, 10);
    write(0, buf, strlen(buf));
    write(0, " assertion failed!", 18);
    while(true)
    {

    }
}
