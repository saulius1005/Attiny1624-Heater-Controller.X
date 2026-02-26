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
        ON  = 1
    } stepper_state_e;

    typedef enum {
        CCW = 0,
        CW  = 1
    } stepper_dir_e;

    /* Realus saugojimo tipas */
    typedef uint8_t stepper_state_t;
    typedef uint8_t stepperDIR_t;

    typedef struct {
        stepper_state_t Enable;
        stepperDIR_t    Direction;
        stepper_state_t Step;
    } Stepper_data;

    extern Stepper_data Motor;

#ifdef	__cplusplus
}
#endif

#endif	/* STEPPER_H */

