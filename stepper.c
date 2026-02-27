#include "settings.h"
#include "stepeprVar.h"

void Stepper_enable(enable_state_t en){
    if(en == ON)
        PORTA.OUTCLR = PIN3_bm; //inverted enable- low meaning enabled
    else
        PORTA.OUTSET = PIN3_bm;
}

void StepperDir(stepperDIR_t dir){
    if(dir == CLOSE)
        PORTA.OUTSET = PIN1_bm;		//CLOSE
    else
        PORTA.OUTCLR = PIN1_bm;		//OPEN
}

void StepperStep()
{
    if(Motor.steps == 0){
        Stepper_enable(OFF);
        RTC_OFF();
        return;        
    }

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