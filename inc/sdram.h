#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f4xx_conf.h"

#include <math.h>
#include <stdint.h>


#define SDRAM_TIMEOUT ((uint32_t)0xFFFF)
#define SDRAM_REG_VALUE 0x0231

#define SDRAM_START_ADDRESS ((uint32_t)0xD0000000)

#define SDRAM_Write8(address, value)                                           \
    (*(__IO uint8_t *)(SDRAM_START_ADDRESS + (address)) = (value))
#define SDRAM_Write16(address, value)                                          \
    (*(__IO uint16_t *)(SDRAM_START_ADDRESS + (address)) = (value))
#define SDRAM_Read8(address)                                                   \
    (*(__IO uint8_t *)(SDRAM_START_ADDRESS + (address)))
#define SDRAM_Read16(address)                                                  \
    (*(__IO uint16_t *)(SDRAM_START_ADDRESS + (address)))
#define SDRAM_Write32(address, value)                                          \
    (*(__IO uint32_t *)(SDRAM_START_ADDRESS + (address)) = (value))
#define SDRAM_Read32(address)                                                  \
    (*(__IO uint32_t *)(SDRAM_START_ADDRESS + (address)))

void GPIO_FMC_init();
void FMC_init();
void SDRAM_timeout();

void SDRAM_WriteBuffer(uint16_t *pBuffer, uint16_t uwWriteAddress,
                       uint16_t uwBufferSize);

#ifdef __cplusplus
}
#endif