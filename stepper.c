#include "settings.h"
#include "stepeprVar.h"

void Stepper_enable(stepper_state_t en){
    if(en == ON)
        PORTA.OUTCLR = PIN3_bm; //inverted enable- low meaning enabled
    else
        PORTA.OUTSET = PIN3_bm;
}

void StepperDir(stepper_state_t dir){
    if(dir == CW)
        PORTA.OUTSET = PIN1_bm;		//1-CW
    else
        PORTA.OUTCLR = PIN1_bm;		//0-CCW
}

void StepperStep()
{
    if(Motor.steps == 0)
        return;

    switch(Motor.state)
    {
        case STEP_IDLE:
            PORTA.OUTSET = PIN2_bm;
            RTC_ON(Motor.stepwidth);
            Motor.state = STEP_HIGH;
            break;

        case STEP_HIGH:
            if(RTC.INTFLAGS & RTC_OVF_bm)
            {
                RTC.INTFLAGS = RTC_OVF_bm;
                PORTA.OUTCLR = PIN2_bm;
                RTC_ON(Motor.stepwidth);
                Motor.state = STEP_LOW;
            }
            break;

        case STEP_LOW:
            if(RTC.INTFLAGS & RTC_OVF_bm)
            {
                RTC.INTFLAGS = RTC_OVF_bm;
                Motor.steps--;
                Motor.state = STEP_IDLE;
            }
            break;
    }
}

/*void StepperStep(){ //no cpu holding stepping function (without _delay_ms or _delay_us)
    if(Motor.steps != 0){
        if(Motor.stepHigh == 0){
            PORTA.OUTSET = PIN2_bm; //Set high
            RTC_ON(Motor.stepwidth);
            Motor.stepHigh = 1;
        }
        if(Motor.stepHigh == 1){
            if(RTC.INTFLAGS & RTC_OVF_bm){//after 10 seconds it will turn off
                RTC.INTFLAGS = RTC_OVF_bm;   // clear flag
                PORTA.OUTCLR = PIN2_bm;
                RTC_ON(Motor.stepwidth);
                Motor.stepLow = 1;
            }               
        }
        if(Motor.stepLow == 1){
             if(RTC.INTFLAGS & RTC_OVF_bm){//after 10 seconds it will turn off
                RTC.INTFLAGS = RTC_OVF_bm;   // clear flag
                Motor.stepLow = 0;
                Motor.stepHigh = 0;
                Motor.steps--;
            }              
        }
        
    }
}*/