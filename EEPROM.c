#include "settings.h"

 void ReadAll(){ //read eeprom and if eeprom is empty fill it with default values
	 eeprom_busy_wait(); // Start only eeprom is ready
	 if(eeprom_read_byte((uint8_t*) 0) == 0xff)
        eeprom_update_byte((uint8_t*) 0,(uint8_t) 20); //default temp is 20
	 WORK.Room_air_temp_set_point = eeprom_read_byte((uint8_t*) 0);

	 eeprom_busy_wait();
	 if(eeprom_read_byte((uint8_t*) 1) == 0xff)
        eeprom_update_byte((uint8_t*) 1,(uint8_t) 1); //default temp deviation is 1 degree centegrade
	 WORK.Temp_deviation = eeprom_read_byte((uint8_t*) 1);
     
     eeprom_busy_wait();
	 if(eeprom_read_word((uint16_t*) 2) == 0xffff)
        eeprom_update_word((uint16_t*) 2,(uint16_t) 90);// set as default 90 
	 WORK.Close_angle_set_point = eeprom_read_word((uint16_t*) 2);

     eeprom_busy_wait();
	 if(eeprom_read_word((uint16_t*) 4) == 0xffff)
        eeprom_update_word((uint16_t*) 4,(uint16_t) 180);// set as default 90 
	 WORK.Open_angle_set_point = eeprom_read_word((uint16_t*) 4);
     
     eeprom_busy_wait();
	 if(eeprom_read_byte((uint8_t*) 6) == 0xff)
        eeprom_update_byte((uint8_t*) 6,(uint8_t) 2); //default angle deviation is 2
	 WORK.Angle_deviation  = eeprom_read_byte((uint8_t*) 6);
	 
 }
 
 void SaveAll(){
     eeprom_busy_wait();
     eeprom_update_byte((uint8_t*) 0,(uint8_t) WORK.Room_air_temp_set_point);
     eeprom_busy_wait();
     eeprom_update_byte((uint8_t*) 1,(uint8_t) WORK.Temp_deviation);
     eeprom_busy_wait();
     eeprom_update_word((uint16_t*) 2,(uint16_t) WORK.Close_angle_set_point);
     eeprom_busy_wait();
     eeprom_update_word((uint16_t*) 4,(uint16_t) WORK.Open_angle_set_point);
     eeprom_busy_wait();
     eeprom_update_byte((uint8_t*) 6,(uint8_t) WORK.Room_air_temp_set_point);
 }
