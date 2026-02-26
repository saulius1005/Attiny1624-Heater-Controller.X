#include "settings.h"
#include "stepeprVar.h"

void Stepper_enable(stepper_state_t en){
    if(en)
        PORTA.OUTCLR = PIN3_bm;
    else
        PORTA.OUTSET = PIN3_bm;
}

void StepperDir(stepper_dir_e dir){
    if(dir)
        PORTA.OUTSET = PIN1_bm;		//1-CW
    else
        PORTA.OUTCLR = PIN1_bm;		//0-CCW
}

void StepperStep(stepper_state_t on){

}