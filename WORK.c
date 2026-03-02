#include "settings.h"
#include "WORKVar.h"

void Controll(){
    uint8_t roomTemp  = (LM35[RATS].TempC + 5) / 10; //rounding up room temperature
    uint8_t waterTemp = (LM35[HWTS].TempC + 5) / 10; //rounding up water teperature

    bool waterTooCold  = waterTemp < (WORK.Room_air_temp_set_point - WORK.Temp_deviation);
    bool waterHotEnough = waterTemp > (WORK.Room_air_temp_set_point + WORK.Temp_deviation);

    bool roomNeedsHeat = roomTemp < (WORK.Room_air_temp_set_point - WORK.Temp_deviation);
    bool roomTooHot    = roomTemp > (WORK.Room_air_temp_set_point + WORK.Temp_deviation);

    switch(WORK.Valve_state)
    {
        case CLOSED: //if valve closed and water is hot enough set stepper direction to open valve and change state to opening
            if(waterHotEnough /*&& !roomTooHot*/){
                PORTA.OUTCLR = PIN4_bm; //turn off the pump before opening the valve                 
                StepperDir(OPEN);
                Stepper_enable(ON);
                Motor.steps = 6400; //ideal case should enough 1600, but set more if stepper struglle to spin valve
                WORK.Valve_state = OPENING;
            }
            else{
                Stepper_enable(OFF);
            }
        break;

        case OPENED: //if valve opened and water is too cold or room too hot set stepper direction to close valve and change state to closing
            if(waterTooCold){          
                static uint32_t ticker = 50000; //~6seconds
                PORTA.OUTCLR = PIN4_bm;     // Pump OFF
                if(ticker > 0) //simple poled delay
                    ticker--;
                else{
                    StepperDir(CLOSE);
                    Stepper_enable(ON);
                    Motor.steps = 6400;
                    WORK.Valve_state = CLOSING;     
                    ticker = 50000;
                }
         
            }
            else if(roomTooHot){
                Stepper_enable(OFF);
                PORTA.OUTCLR = PIN4_bm;     // Pump OFF only
            }
            else if(roomNeedsHeat){ //if room is cold and valve is fully opened turn on the pump
                Stepper_enable(OFF);
                PORTA.OUTSET = PIN4_bm;     // Pump ON
            }
        break;

        case OPENING: //if valve opening checking mt6701 angle till it reach open state
            if(MT6701.angle != WORK.Open_angle_set_point){
                StepperStep();
            }
            else{
                WORK.Valve_state = OPENED;
                Motor.steps = 0; //reseting steps 
            }
        break;

        case CLOSING: //if valve closing checking mt6701 angle till it reach close state
            if(MT6701.angle != WORK.Close_angle_set_point){
                StepperStep();
            }
            else{
                WORK.Valve_state = CLOSED;
                Motor.steps = 0;
            }
        break;
    }
}

void WorkingMode(){
    if(WORK.ProgMode == 1){ //if programing mode enabled
            BLTReceiver(); //read bluetooth
        }
    else{ //if it is regular mode controll stepper, read mt6701 angle, read hot water and room air tmperatures (LM35) and send regular raport every 5 seconds
            Controll();
            MT6701_Read();
            LM35_Read(); 
            TimePassUpdate();
        }
}
