#include "settings.h"

void RTC_ON(uint32_t period_us)
{
    while (RTC.STATUS > 0);
   
    RTC.CLKSEL = RTC_CLKSEL_INT32K_gc;

    // ticks = us * 32768 / 1 000 000
    RTC.PER = (uint16_t)((period_us * 32768UL) / 1000000UL); //lowest step is 30.5us and highest ~2sec

    RTC.CNT = 0;

    RTC.CTRLA = RTC_RTCEN_bm | RTC_PRESCALER_DIV1_gc;
}

/*
 * Disable the RTC.
 */
void RTC_OFF()
{
    // Disable RTC
    RTC.CTRLA &= ~RTC_RTCEN_bm;

    // Wait until RTC synchronization is complete
    while (RTC.STATUS > 0);
}