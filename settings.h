/* 
 * File:   settings.h
 * Author: Saulius
 *
 * Created on Ketvirtadienis, 2026, vasaris 26, 16.18
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <avr/cpufunc.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "CLK.h"    
#include <util/delay.h>    
#include "ADC.h"    
#include "USART.h"
#include "stepper.h"
#include "LM35.h"
#include "mt6701.h"
#include "HM-10.h"
#include "WORK.h"


    void GPIO_init();
    
    void CLOCK_INHF_clock_init();    
    
    void Stepper_enable(enable_state_t en);
    void StepperDir(stepperDIR_t dir);
    void StepperStep();
    
    void RTC_ON(uint16_t seconds); // used for 5 seconds data report sending
    void RTC_OFF();
    
    void TCA0_init(); 
    void TCA0_ON(uint32_t period_us); //used for stepper pulses
    void TCA0_OFF();
    
    void ADC0_init();
    uint16_t ADC0_Read(uint8_t channel);
    
    void MT6701_Read(); //reading valve angle
    
    void LM35_Read(); //reading LM35 temperature
    
    void USART0_init();
    char USART0_readChar();
    void USART_printf(const char *format, ...);
    
    void Bluetooth_init(enable_state_t en);
    void BLTReceiver(); //bluetooth data receiving function
    void TimePassUpdate(); //regular raport sending function
    
    uint8_t crc8_cdma2000(uint8_t *data, uint8_t len); //calculate crc
    
    void WorkingMode();//define working mode acording pressed button
    
    void ReadAll(); //read data from eeprom
    void SaveAll(); //write data to eeprom
    


#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

