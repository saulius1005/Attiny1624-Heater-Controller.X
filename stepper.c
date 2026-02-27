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
        TCA0_OFF();
        return;        
    }

    switch(Motor.state)
    {
        case STEP_IDLE:
            PORTA.OUTSET = PIN2_bm; //set step signal high
            TCA0_ON(Motor.stepwidth);
            Motor.state = STEP_HIGH;
            break;

        case STEP_HIGH:
            if(TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm)
            {
                TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
                PORTA.OUTCLR = PIN2_bm; //set step signal low
                TCA0_ON(Motor.stepwidth);
                Motor.state = STEP_LOW;
            }
            break;

        case STEP_LOW:
            if(TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm)
            {
                TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
                Motor.steps--;
                Motor.state = STEP_IDLE;
            }
            break;
    }
}