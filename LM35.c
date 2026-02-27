#include "settings.h"
#include "LM35Var.h"

void LM35_Read(){
    TempSensor[CWTS].TempC = ADC0_Read(COLD_WATER_TEMPERATURE_CHANNEL);
    TempSensor[HWTS].TempC = ADC0_Read(HOT_WATER_TEMPERATURE_CHANNEL);
}