#include "hw_utils.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include <stdint.h>
extern uint32_t SystemCoreClock;

u8 initalizeSysTick(u32 time_ms) {
	if(time_ms == 0) return false;
	if(SysTick_Config(SystemCoreClock/1000*time_ms) != 0) {
		return false;
	}
	return true;
}
