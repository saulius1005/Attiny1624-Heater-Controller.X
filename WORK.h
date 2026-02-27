/* 
 * File:   WORK.h
 * Author: Saulius
 *
 * Created on Penktadienis, 2026, vasaris 27, 16.47
 */

#ifndef WORK_H
#define	WORK_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum {
        CLOSED = 0,
        CLOSING,
        OPENED,
        OPENING
    } valve_action_t;    
    
typedef struct {   
    uint8_t ProgMode;
    uint8_t Room_air_temp_set_point;
    uint8_t Temp_deviation;
    uint16_t Open_angle_set_point;
    uint16_t Close_angle_set_point;
    uint8_t Angle_deviation;
    valve_action_t Valve_state;
} Work_data;

extern Work_data WORK;


#ifdef	__cplusplus
}
#endif

#endif	/* WORK_H */

