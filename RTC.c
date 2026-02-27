#include "settings.h"

void RTC_ON(uint16_t seconds){
    while (RTC.STATUS > 0);  
    RTC.CLKSEL = RTC_CLKSEL_INT1K_gc;

    RTC.PER = seconds - 1; //lowest step is 2s, highest is 65535seconds ()
    RTC.CNT = 0;
    RTC.CTRLA = RTC_RTCEN_bm | RTC_PRESCALER_DIV1024_gc;
}

/*
 * Disable the RTC.
 */
void RTC_OFF(){
    // Disable RTC
    RTC.CTRLA &= ~RTC_RTCEN_bm;
    // Wait until RTC synchronization is complete
    while (RTC.STATUS > 0);
}