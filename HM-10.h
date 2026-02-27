/* 
 * File:   HM-10.h
 * Author: Saulius
 *
 * Created on Penktadienis, 2026, vasaris 27, 11.20
 */

#ifndef HM_10_H
#define	HM_10_H

#ifdef	__cplusplus
extern "C" {
#endif

#define COMMAND_LENGTH 14  
#define SHORT_COMMAND_LENGTH 6
    
typedef struct {
        enable_state_t Enable;      
    } HM10_data;

    extern HM10_data HM10;


#ifdef	__cplusplus
}
#endif

#endif	/* HM_10_H */

