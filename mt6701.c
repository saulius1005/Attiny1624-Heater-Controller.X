#include "settings.h"
#include "mt6701Var.h"

void MT6701_Read(){
    MT6701.ADC_Value = ADC0_Read(ANGLE_SENSOR_CHANNEL);
    MT6701.angle = ((uint32_t)MT6701.ADC_Value * 360) / 4095;
}