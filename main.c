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
    StepperDir(OPEN);
    Motor.steps = 6400; //full circle 1/32 (200*32 = 6400)
    
    while(1){
        StepperStep();
        MT6701_Read();
        LM35_Read();
    }
}

