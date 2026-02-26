#include "settings.h"

void ADC0_init(){
	ADC0.CTRLA = ADC_LOWLAT_bm;
	ADC0.CTRLB = ADC_PRESC_DIV64_gc; // 20M / 64 = 312.5kHz ADC
	ADC0.CTRLC = (TIMEBASE_VALUE << ADC_TIMEBASE_gp) | ADC_REFSEL_VDD_gc; 
	ADC0.CTRLE = 128; //128+0.5 ADC cycle
	ADC0.CTRLF = ADC_SAMPNUM_NONE_gc; 
	ADC0.COMMAND = ADC_MODE_SINGLE_12BIT_gc; 
	ADC0.CTRLA |= ADC_ENABLE_bm;
	while (ADC0.STATUS & ADC_ADCBUSY_bm); // wait untill all settings will be set up
}

uint16_t ADC0_Read(uint8_t channel){
	ADC0.MUXPOS  = channel; //channel selection after change it will starting immediately
	ADC0.COMMAND |= ADC_START_IMMEDIATE_gc; //start conversion
	while (ADC0.STATUS & ADC_ADCBUSY_bm); // wait untill all settings will be set up and same time wait until conversion will be compleated
	while (!(ADC0.INTFLAGS & ADC_RESRDY_bm));
	ADC0.INTFLAGS = ADC_RESRDY_bm; //clear result ready flag
	return ADC0.RESULT; //return average ADC value of 64 measurements
}
