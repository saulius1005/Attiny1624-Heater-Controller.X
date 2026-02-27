#include "settings.h"
#include "HM10Var.h"

void Bluetooth_init(enable_state_t en){
 if(en == ON)
    PORTB.OUTSET = PIN0_bm;
 else
    PORTB.OUTCLR = PIN0_bm;
}
