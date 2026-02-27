/* 
 * File:   stepper.h
 * Author: Saulius
 *
 * Created on Ketvirtadienis, 2026, vasaris 26, 16.23
 */

#ifndef STEPPER_H
#define	STEPPER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef enum {
        OFF = 0,
        ON
    } enable_state_t;

    typedef enum {
        CLOSE = 0,
        OPEN
    } stepperDIR_t;

    typedef enum {
        STEP_IDLE = 0,
        STEP_HIGH,
        STEP_LOW
    } step_state_t;

    typedef struct {
        enable_state_t Enable;
        stepperDIR_t    Direction;
        enable_state_t Step;
        uint16_t steps;
        uint16_t stepwidth;
        step_state_t state;
    } Stepper_data;

    extern Stepper_data Motor;

#ifdef	__cplusplus
}
#endif

#endif	/* STEPPER_H */

