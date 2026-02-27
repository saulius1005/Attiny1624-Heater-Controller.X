#include "settings.h"
#include "WORKVar.h"

void WorkingMode(){
    if(WORK.ProgMode == 1){ //if programing mode enabled
            BLTReceiver(); //read bluetooth
        }
        else{
            StepperStep();
            MT6701_Read();
            LM35_Read();            
        }
}
