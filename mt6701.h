/* 
 * File:   mt6701.h
 * Author: Saulius
 *
 * Created on Ketvirtadienis, 2026, vasaris 26, 23.14
 */

#ifndef MT6701_H
#define	MT6701_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ANGLE_SENSOR_CHANNEL ADC_MUXPOS_AIN7_gc

typedef struct {
        uint16_t ADC_Value;
        uint16_t angle;
    } MT6701_data;

    extern MT6701_data MT6701;
#ifdef	__cplusplus
}
#endif

#endif	/* MT6701_H */

