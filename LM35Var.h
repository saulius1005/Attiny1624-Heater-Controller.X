/* 
 * File:   LM35Var.h
 * Author: Saulius
 *
 * Created on Penktadienis, 2026, vasaris 27, 12.01
 */

#ifndef LM35VAR_H
#define	LM35VAR_H

#include "LM35.h"


#ifdef	__cplusplus
extern "C" {
#endif

sensor_data LM35[SENSOR_COUNT] = {
    [RATS] = {
        .TempC = 0
    },
    [HWTS] = {
        .TempC = 0
    }
};


#ifdef	__cplusplus
}
#endif

#endif	/* LM35VAR_H */

