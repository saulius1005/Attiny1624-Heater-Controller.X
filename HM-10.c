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

void BTDataSplitter(char *command) {
    //uint8_t crc_received = (uint8_t)strtol(command + 3, NULL, 16);
    
    uint8_t crc_calculated = crc8_cdma2000((uint8_t*)command, 3); 
    uint8_t crc_received = hex2uint(&command[3], 2); //start from 3rd symbol of "TST"
    
    USART_printf("data crc: %x \r\n", crc_calculated);
    
    USART_printf("crc received: %x \r\n", crc_received);
    
    USART_printf("crc received: %s \r\n", crc_calculated == crc_received? "ok" : "no");
    
	/*if(strcmp(command,"TST") == 0){
        USART_printf("TST crc: %x \r\n", crc8_cdma2000_id());
     }
     else  if(strcmp(command,"OK+CONN") == 0){
         USART_printf("Connected\r\n");
     }*/
}

void BLTReceiver() {
    uint8_t index = 0;
    char command[COMMAND_LENGTH]; // Empty command array
    uint8_t start = 0;
	while (1) {
        char c = USART0_readChar();
		if (start) {		
			if (c == '>') { // If received data end symbol
				start = 0;
				command[index] = '\0';
				index = 0;
					BTDataSplitter(command); // Execute the received command //comment when testing lines below
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

