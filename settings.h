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
    
    void RTC_ON(uint32_t period_us);
    void RTC_OFF();
    
    void TCA0_init();
    void TCA0_ON(uint32_t period_us);
    void TCA0_OFF();
    
    void ADC0_init();
    uint16_t ADC0_Read(uint8_t channel);
    
    void MT6701_Read();
    
    void LM35_Read();
    
    void USART0_init();
    char USART0_readChar();
    void USART_printf(const char *format, ...);
    
    void Bluetooth_init(enable_state_t en);
    void BLTReceiver();
    
    uint8_t crc8_cdma2000(uint8_t *data, uint8_t len);
    bool verify_crc8_cdma2000(uint8_t *data, uint8_t len, uint8_t received_crc);
    
    void WorkingMode();
    


#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

