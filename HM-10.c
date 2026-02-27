#include "settings.h"
#include "HM10Var.h"

void Bluetooth_init(enable_state_t en){
 if(en == ON)
    PORTB.OUTSET = PIN0_bm;
 else
    PORTB.OUTCLR = PIN0_bm;
}

void BTDataSplitter(char *command) {
	if(strcmp(command,"TST") == 0){
        USART_printf("TST back \r\n");
     }
     else  if(strcmp(command,"OK+CONN") == 0){
         USART_printf("Connected\r\n");
     }
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

