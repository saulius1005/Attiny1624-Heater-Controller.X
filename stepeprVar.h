/* 
 * File:   stepeprVar.h
 * Author: Saulius
 *
 * Created on Ketvirtadienis, 2026, vasaris 26, 16.33
 */

#ifndef STEPEPRVAR_H
#define	STEPEPRVAR_H

#include "stepper.h"


#ifdef	__cplusplus
extern "C" {
#endif

Stepper_data Motor = {
.Enable = OFF,
.Direction = CLOSE,
.Step = OFF,
.steps = 0,
.stepwidth = 31, //31us (30.5us is lowest)
.state = STEP_IDLE
//.stepHigh = 0,
//.stepLow = 0
};


#ifdef	__cplusplus
}
#endif

#endif	/* STEPEPRVAR_H */

