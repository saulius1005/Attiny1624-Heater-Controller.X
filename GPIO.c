#include "settings.h"

void GPIO_init(){
    PORTB.DIRCLR = PIN1_bm  //Button input
                 | PIN3_bm; //UART RX input
    PORTA.DIRCLR = PIN5_bm  //Hot Water sensor input
                 | PIN6_bm  //Room temperature sensor input
                 | PIN7_bm; //Angle sensor input

    PORTA.PIN5CTRL = PORT_ISC_INPUT_DISABLE_gc;
    PORTA.PIN6CTRL = PORT_ISC_INPUT_DISABLE_gc;
    PORTA.PIN7CTRL = PORT_ISC_INPUT_DISABLE_gc;
    //PORTA.PIN5CTRL &= ~PORT_ISC_gm; //PIN setup for ADC
    //PORTA.PIN5CTRL |= PORT_ISC_INPUT_DISABLE_gc;
    //PORTA.PIN5CTRL &= ~PORT_PULLUPEN_bm;


    //PORTA.PIN6CTRL &= ~PORT_ISC_gm;
    //PORTA.PIN6CTRL |= PORT_ISC_INPUT_DISABLE_gc;
    //PORTA.PIN6CTRL &= ~PORT_PULLUPEN_bm;


    //PORTA.PIN7CTRL &= ~PORT_ISC_gm;
    //PORTA.PIN7CTRL |= PORT_ISC_INPUT_DISABLE_gc;
    //PORTA.PIN7CTRL &= ~PORT_PULLUPEN_bm;

    PORTA.DIRSET = PIN1_bm  //Stepper DIR output
                 | PIN2_bm  //Stepper STEP output
                 | PIN3_bm  //Stepper Enable output
                 | PIN4_bm; //Circulation pump output
    PORTB.DIRSET = PIN0_bm  //Bluetooth module enable output
                 | PIN2_bm; //UART TX output
}
