#include "settings.h"
#include "mt6701Var.h"

uint16_t MT6701_Read(){
 return ADC0_Read(ANGLE_SENSOR_CHANNEL);
}