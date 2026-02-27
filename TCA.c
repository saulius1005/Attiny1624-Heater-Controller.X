#include "settings.h"

void TCA0_init(){
 TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc; // paprastas skaitliukas
 TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV16_gc;
}

void TCA0_OFF(){
	TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;	//stabdomas skaitliukas
}

void TCA0_ON(uint32_t period_us){
    // Iðjungiam timerá
    TCA0.SINGLE.CTRLA = 0;

    // Timer frequency:
    // 20MHz / 16 = 1.25 MHz
    // 1 tick = 0.8 us

    uint32_t ticks = (period_us * (F_CPU / 16UL)) / 1000000UL;

    TCA0.SINGLE.PER = (uint16_t)ticks;

    TCA0.SINGLE.CNT = 0;

    // Ájungiam timerá
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}
