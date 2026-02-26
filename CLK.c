#include "settings.h"

void CLOCK_INHF_clock_init() {
    /* Enable the internal oscillator with a frequency of 20 MHz. */
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSC20M_gc);// For SO14, it is impossible to enable CLKOUT due to the lack of a dedicated pin. 
    
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_2X_gc & ~CLKCTRL_PEN_bm); //peripherals run at CPUspeed (PEN disabled)

    /* Wait for the oscillator change to complete. */
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm) {};
}
