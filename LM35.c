#include "settings.h"
#include "LM35Var.h"

void LM35_Read(){
    TempSensor[RATS].TempC = ADC0_Read(ROOM_AIR_TEMPERATURE_CHANNEL);
    TempSensor[HWTS].TempC = ADC0_Read(HOT_WATER_TEMPERATURE_CHANNEL);
}