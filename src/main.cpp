//#include "fs/romfs/fileSystemHeader.hpp"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "types.h"
//#include <stdio.h>
//#include "usart.hpp"
#include "kernel.hpp"
#include "logger.hpp"
#include "usart.hpp"
#include <cstdio>
#include <cstdlib>

void initializeBoardLeds() {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
}

// extern u8 end asm("end");
// static u8 *heap_start = &end;
// static u8 *heap_end = &end;
// const u8 *heap_max = heap_start + 0x2ba000;
// // *heap_end = 0x0;

// const u8 HEADER_SIZE = sizeof(std::size_t);

// u8 *findFreeBlockWithRequestedSize(std::size_t size) {
//     u8 *currentMemory = heap_start;
//     while (currentMemory < heap_max) {
//         // if allocated skip size
//         if (currentMemory & 0x80) {
//             currentMemory += (currentMemory & 0x7f) + 1;
//         } else {
//         }
//     }
// }
// // 
// void myfree(void *memory) {
//     u8 *mem = (u8 *)memory;
//     mem -= HEADER_SIZE;
//     *mem &= 0x7f;
// }

// void *myalloc(std::size_t size) {
//     Logger::log(Level::TRACE, "alloc", "requested allocation size: %d", size);
//     u8 *allocation_start = heap_end + HEADER_SIZE;
//     u8 *header_start = heap_end;
//     int *header_val = (int *)header_start;
//     *header_val = size;
//     *header_start |= 0x80;
//     Logger::log(Level::TRACE, "alloc", "header value: %d", *header_val);
//     heap_end += size;

//     return allocation_start;
// }

int main() {
    SystemInit();
    hardwareInitialize();
    initializeBoardLeds();

    GPIO_WriteBit(GPIOG, GPIO_Pin_14, Bit_SET);
    while (1) {
    }
}

/*
void assert_failed(u8* file, u32 line)
{
        while(true)
        {

        }
}*/
