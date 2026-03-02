/* 
 * File:   WorkVar.h
 * Author: Saulius
 *
 * Created on Penktadienis, 2026, vasaris 27, 16.55
 */

#ifndef WORKVAR_H
#define	WORKVAR_H

#include "WORK.h"
#include "stepper.h"


#ifdef	__cplusplus
extern "C" {
#endif

Work_data WORK = {
    .ProgMode = 0, //regular mode
    .Room_air_temp_set_point = 25, //20.0C
    .Temp_deviation = 1, //5.0C
    .Close_angle_set_point = 90,
    .Open_angle_set_point = 180,
    .Angle_deviation = 2, //2 degree
    .Valve_state = CLOSED //closed valve state
};


#ifdef	__cplusplus
}
#endif

#endif	/* WORKVAR_H */

