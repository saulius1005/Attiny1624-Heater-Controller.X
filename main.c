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
    USART0_init();
    ADC0_init();
    TCA0_init();
    Bluetooth_init(ON);
    //WORK.ProgMode = 1;
    if(!(PORTB.IN & PIN1_bm)){ //if button pressed at the same time as power up then we enabling programming mode
        WORK.ProgMode = 1;
    } 
    else{ //and if not program continue regular work
        //Stepper_enable(ON);
        //StepperDir(OPEN);
        //Motor.steps = 1600; //6400- full circle 1/32 (200*32 = 6400)        
    }
    while(1){
        WorkingMode();
    }
}

