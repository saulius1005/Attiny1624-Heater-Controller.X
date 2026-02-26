#include "settings.h"

void RTC_ON(uint16_t period_ms)
{
    // Wait until RTC synchronization is complete
    while (RTC.STATUS > 0);

    // Select 1 kHz internal oscillator (32768 Hz / 32 = 1024 Hz)
    RTC.CLKSEL = RTC_CLKSEL_INT1K_gc;

    // Set period register: RTC counts from 0 to PER (interrupt occurs when COUNT == PER)
    RTC.PER = (uint16_t)(period_ms * 1.024) + 0.5;  

    // Initialize counter to 0
    RTC.CNT = 0;

    // Enable RTC and set prescaler to DIV1
    RTC.CTRLA = RTC_RTCEN_bm | RTC_PRESCALER_DIV1_gc;

    // Optional: run RTC in debug mode
    // RTC.DBGCTRL |= RTC_DBGRUN_bm;
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