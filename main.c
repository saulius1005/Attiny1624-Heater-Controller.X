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
    ADC0_init();
    Stepper_enable(ON);
    Motor.steps = 6400; //full circle
    
    while(1){
        StepperStep();
        if(Motor.steps == 0){
            Stepper_enable(OFF);
        }
        MT6701.ADC_Value = MT6701_Read();
    }
}

