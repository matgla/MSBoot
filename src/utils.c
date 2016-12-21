#include "utils.h"

void DelayUs(u32 delay_us) {
	if(delay_us == 0) return;
	while(--delay_us);
}

void Delay(u32 delay_ms) {
	while(delay_ms--) {
		DelayUs(1000);
	}
}

void DelayS(u32 delay_s) {
	while(delay_s--) {
		Delay(1000);
	}
}
