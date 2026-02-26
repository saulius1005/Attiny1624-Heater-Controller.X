/* 
 * File:   main.c
 * Author: Saulius
 *
 * Created on Ketvirtadienis, 2026, vasaris 26, 16.10
 */

#include "settings.h"

int main() {

    CLOCK_INHF_clock_init();
    GPIO_init();
    Stepper_enable(OFF);
    RTC_ON(10000);
    Stepper_enable(ON);
    
    while(1){
        if(RTC.INTFLAGS & RTC_OVF_bm){//after 10 seconds it will turn off
            Stepper_enable(OFF);
        }
    }
}

