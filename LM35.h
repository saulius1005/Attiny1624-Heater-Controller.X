/* 
 * File:   LM35.h
 * Author: Saulius
 *
 * Created on Ketvirtadienis, 2026, vasaris 26, 23.12
 */

#ifndef LM35_H
#define	LM35_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SENSOR_COUNT 2
#define HOT_WATER_TEMPERATURE_CHANNEL ADC_MUXPOS_AIN5_gc
#define ROOM_AIR_TEMPERATURE_CHANNEL ADC_MUXPOS_AIN6_gc

    
    typedef enum {
        RATS = 0, //room air temperature sensor
        HWTS //hot water temperature sensor
    } sensor_t;
    
    typedef struct {
        uint16_t TempC; //cold or hot temperature in C (not floating point ex.: 20.1C is 201)
    } sensor_data;

    extern sensor_data LM35[SENSOR_COUNT];

#ifdef	__cplusplus
}
#endif

#endif	/* LM35_H */

