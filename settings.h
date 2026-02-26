/* 
 * File:   settings.h
 * Author: Saulius
 *
 * Created on Ketvirtadienis, 2026, vasaris 26, 16.18
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <avr/cpufunc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "CLK.h"    
#include "ADC.h"    
#include "stepper.h"



    void GPIO_init();
    void Stepper_enable(stepper_state_t en);
    
    void RTC_ON(uint16_t period_ms);
    void RTC_OFF();
    
    void CLOCK_INHF_clock_init();
    


#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

