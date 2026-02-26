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
    
    /*typedef enum {
        OFF = 0,
        ON  = 1
    } stepper_state_e;

    typedef enum {
        CCW = 0,
        CW  = 1
    } stepper_dir_e;

    typedef uint8_t stepper_state_t;
    typedef uint8_t stepperDIR_t;

    typedef struct {
        stepper_state_t Enable;
        stepperDIR_t    Direction;
        stepper_state_t Step;
        uint16_t steps;
        uint16_t stepwidth;
        uint8_t stepHigh;
        uint8_t stepLow;
    } Stepper_data;*/
    
    typedef enum {
        OFF = 0,
        ON
    } stepper_state_t;

    typedef enum {
        CCW = 0,
        CW
    } stepperDIR_t;

    typedef enum {
        STEP_IDLE = 0,
        STEP_HIGH,
        STEP_LOW
    } step_state_t;

    typedef struct {
        stepper_state_t Enable;
        stepperDIR_t    Direction;
        stepper_state_t Step;
        uint16_t steps;
        uint16_t stepwidth;
        step_state_t state;
    } Stepper_data;

    extern Stepper_data Motor;

#ifdef	__cplusplus
}
#endif

#endif	/* STEPPER_H */

