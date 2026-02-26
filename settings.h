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

#define F_CPU 20000000UL
    
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stepper.h"

    void GPIO_init();
    void Stepper_enable(stepper_state_t en);
    
    void RTC_ON(uint16_t period_ms);
    void RTC_OFF();
    


#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

