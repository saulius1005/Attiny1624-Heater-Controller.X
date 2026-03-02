#include "settings.h"
#include "HM10Var.h"

void Bluetooth_init(enable_state_t en){
 if(en == ON)
    PORTB.OUTSET = PIN0_bm;
 else
    PORTB.OUTCLR = PIN0_bm;
}

inline uint8_t hexchar2val(char c) {// Fastest ANCII HEX conversion to uint8_t (support  A-F a-f) one simbol
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	return 0;
}

inline uint16_t hex2uint(const char *p, uint8_t len) {//ANCII Hex up to 4 symbols converter
	uint16_t val = 0;
	for (uint8_t i = 0; i < len; i++) {
		val = (val << 4) | hexchar2val(p[i]);
	}
	return val;
}

void BTDataSplitter(char *command, uint8_t len) {
    
    uint8_t crc_calculated = crc8_cdma2000((uint8_t*)command, len - 2);// calculate crc 
    uint8_t crc_received = hex2uint(&command[len - 2], 2); //start from last actual command sybol
    
    if(crc_calculated != crc_received){ //if crc bad send error message and do nothing else
        USART_printf("Gauta eilutë: "); //received data
        USART_printf("%s\r\n", command);
        USART_printf("Jos ilgis %d simboliai ", len); //its length
        USART_printf("ir CRC yra %02X\r\n", crc_received); //and crc      
        USART_printf("Apskaièiuotas ANCII CRC yra %02X\r\n", crc_calculated); //calculated ANCII crc is
        USART_printf("Neteisingas CRC gali bûti, \r\n"); //wrong crc can be
        USART_printf("jei jis apskaièiuotas pagal HEX\r\n"); //if it calculated acording to hex
        return;
    }    
    
    if(len == COMMAND_LENGTH){ //exp: DT14505A0B4A63 is 12 symbols in total
        char *p = command + 2; //remove DT
        WORK.Room_air_temp_set_point    = hex2uint(p, 2); p += 2; //FF 0-255 (0 - 30C)
        WORK.Temp_deviation             = hex2uint(p, 1); p += 1; //F 0-15 (0-10C)
        WORK.Close_angle_set_point      = hex2uint(p, 3); p += 3; //FFF 0-4095 (0-360 degree)
        WORK.Open_angle_set_point       = hex2uint(p, 3); p += 3; //FFF 0-4095 (0-360 degree)
        WORK.Angle_deviation            = hex2uint(p, 1); //F 0-15 (0-15 degree)    
        USART_printf("Duomenys gauti!\r\n"); //data received
    }
    else if(strncmp(command, "MESA2A", SHORT_COMMAND_LENGTH) == 0){ //measure angle (2A crc)
        MT6701_Read();
        USART_printf("Matuojamas kampas yra: %d°\r\n", MT6701.angle); //measured angle is
    }
    else if(strncmp(command, "REDT10", SHORT_COMMAND_LENGTH) == 0){ //read temperatures + crc
        LM35_Read();
        USART_printf("Matuoja temperatûra yra: \nKambario: %d C°\nK.Vandens: %d C°\r\n", (LM35[RATS].TempC + 5) / 10, (LM35[HWTS].TempC + 5) / 10); //measured room temp: how water: rounding by 0.5 degree centigrade
    }
    else if(strncmp(command, "PTSTE8", SHORT_COMMAND_LENGTH) == 0){ //Pump test - toggling action
        PORTA.OUTTGL = PIN4_bm;
        if(PORTA.OUT & PIN4_bm)
            USART_printf("C.S. Ájungtas\r\n"); //pump on
        else
            USART_printf("C.S Iðjungtas\r\n"); //pump off
    }
    else if(strncmp(command, "SAVE02", SHORT_COMMAND_LENGTH) == 0){ //save data
        SaveAll();
        USART_printf("Duomenys iðsaugoti!\r\n"); // data saved
    }
    else if(strncmp(command, "EXITC6", SHORT_COMMAND_LENGTH) == 0){ //exit to regular mode
        USART_printf("Programavimas iðjungtas!\r\n"); //programing off
        WORK.ProgMode = 0;
    }
    else{
        USART_printf("Bloga komanda\r\n"); //bad command
    }
   
}

void BLTReceiver() {
    uint8_t index = 0;
    char command[COMMAND_LENGTH]= {'\0'}; // Empty command array
    uint8_t start = 0;
	while (1) {
        char c = USART0_readChar();
		if (start) {		
			if (c == '>') { // If received data end symbol
                BTDataSplitter(command, index); // Execute the received command //comment when testing lines below
                start = 0;
                command[index] = '\0';
                index = 0;                    
				break;
			} else if (index < COMMAND_LENGTH) {
				command[index++] = c; // Store received character in command array
			}
		}
		if (c == '<') { // If received data start symbol
			start = 1;
			index = 0;
		}
	}
}

void TimePassUpdate(){
    if(HM10.updete_data == 0){
        RTC_ON(DATA_UPDATE_PERIOD);
        HM10.updete_data = 1;
    }
    if(HM10.updete_data == 1){
        if(RTC.INTFLAGS & RTC_OVF_bm){
            RTC.INTFLAGS = RTC_OVF_bm;          
            USART_printf("Kambario temp.: %d/%dC° ±%dC°\r\n", (LM35[RATS].TempC + 5) / 10, WORK.Room_air_temp_set_point, WORK.Temp_deviation); //room temp
            USART_printf("Karðto vandens temp.: %dC°\r\n", (LM35[HWTS].TempC + 5) / 10); //hot water temp
            USART_printf("Sklendë: ");  //"valve"
            switch(WORK.Valve_state){
                case CLOSED:
                    USART_printf("Uþdaryta %d/%d° ±%d°\r\n", WORK.Close_angle_set_point, MT6701.angle, WORK.Angle_deviation);
                break;
                case CLOSING:
                    USART_printf("Uþdaroma %d°\r\n", MT6701.angle);
                break;
                case OPENED:
                    USART_printf("Atidaryta %d/%d° ±%d°\r\n", WORK.Open_angle_set_point, MT6701.angle, WORK.Angle_deviation);
                break;
                case OPENING:
                    USART_printf("Atidaroma %d°\r\n", MT6701.angle);
                break;
            }
            if(PORTA.OUT & PIN4_bm)
                USART_printf("C.S. ájungtas\r\n"); //pump on
            else
                USART_printf("C.S. iðjungtas\r\n"); //pump off
            USART_printf("\r\n");
            HM10.updete_data = 0;
            RTC_OFF();
        }
    }
}

