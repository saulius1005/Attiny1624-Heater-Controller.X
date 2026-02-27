#include "settings.h"
#include "WORKVar.h"

/*void Controll(){
    uint8_t baseRoomTemp = (LM35[RATS].TempC + 5) / 10;     
    uint8_t baseWaterTemp = (LM35[HWTS].TempC + 5) / 10;
    
    if(baseWaterTemp > (WORK.Room_air_temp_set_point + WORK.Temp_deviation)){//if hot water temperature is above set point + deviation, open the valve
        StepperDir(OPEN); //set stepper spinning direction
        if(WORK.Valve_state == CLOSED){ //if valve was closed before set steps count once
            Motor.steps = 6400; //for 90 degree angle enough 1600. Add more if stepper struggle to spin valve and missing steps  
            WORK.Valve_state = OPENING; // set to open state
        }
    }
    else if(baseWaterTemp < (WORK.Room_air_temp_set_point - WORK.Temp_deviation)){//if hot water temperature is below set point - deviation, close the valve
        StepperDir(CLOSE); //set stepper spinning direction
        if(WORK.Valve_state == OPENED){ //if valve was closed before set steps count once
            Motor.steps = 6400; //for 90 degree angle enough 1600
            WORK.Valve_state = CLOSING; // set to open state
        }
    }
    
    if(WORK.Valve_state == OPENING){ //opening valve...
        if(WORK.Open_angle_set_point != MT6701.angle){
            StepperStep();
        }
        else{ //till it will be opened
            WORK.Valve_state = OPENED;
            Motor.steps = 0; //if open reset steps count
        }
    }
    else if(WORK.Valve_state == CLOSING){ //closing valve...
         if(WORK.Close_angle_set_point != MT6701.angle){
            StepperStep();
        }
         else{ //till it will be closed
            WORK.Valve_state = CLOSED;
            Motor.steps = 0;//if open reset steps count
        }       
    }
    
    //if( (baseRoomTemp <= (WORK.Room_air_temp_set_point + WORK.Temp_deviation)) && (baseRoomTemp >= (WORK.Room_air_temp_set_point - WORK.Temp_deviation)) && (WORK.Valve_state == OPENED) ){ // if room temperature in between set point+ deviation turn on pump
    //    PORTA.OUTSET = PIN4_bm;//turn on the pump or keep it runing
   // }
     //else
    if( (baseRoomTemp > (WORK.Room_air_temp_set_point + WORK.Temp_deviation))  && (WORK.Valve_state == CLOSED) ){//if room temperature is above set point + deviation and valve is closed, turn off the pump
        PORTA.OUTCLR = PIN4_bm;//turn off the pump
    }
    else if( (baseRoomTemp < (WORK.Room_air_temp_set_point - WORK.Temp_deviation))  && (WORK.Valve_state == OPENED)){//if room temperature is below set point - deviation and valve is opened, turn on the pump
        PORTA.OUTSET = PIN4_bm;//turn on the pump
    }
}*/

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
            if(waterHotEnough){
                StepperDir(OPEN);
                Stepper_enable(ON);
                Motor.steps = 6400; //ideal case should enough 1600, but set more if stepper struglle to spin valve
                WORK.Valve_state = OPENING;
                PORTA.OUTCLR = PIN4_bm; //turn off the pump before opening the valve 
            }
            else{
                Stepper_enable(OFF);
            }
        break;

        case OPENED: //if valve opened and water is too cold or room too hot set stepper direction to close valve and change state to closing
            if(waterTooCold || roomTooHot){               
                //if(roomTooHot){ //if too hot turn the pump off
                    PORTA.OUTCLR = PIN4_bm;     // Pump OFF
                //} 
                StepperDir(CLOSE);
                Stepper_enable(ON);
                Motor.steps = 6400;
                WORK.Valve_state = CLOSING;          
            }
            else{
                Stepper_enable(OFF);
                if(roomNeedsHeat){ //if room is cold and valve is fully opened turn on the pump
                    PORTA.OUTSET = PIN4_bm;     // Pump ON
                }
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
        else{
            Controll();
            //StepperStep();
            MT6701_Read();
            LM35_Read(); 
            TimePassUpdate();
        }
}
