#include "settings.h"
#include "LM35Var.h"

void LM35_Read(){
    LM35[RATS].TempC = ADC0_Read(ROOM_AIR_TEMPERATURE_CHANNEL);
    LM35[HWTS].TempC = ADC0_Read(HOT_WATER_TEMPERATURE_CHANNEL);
}