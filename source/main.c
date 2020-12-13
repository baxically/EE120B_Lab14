/*	Author: Ally Thach, athac007
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 14  Exercise 1
 *	Exercise Description: Two microcontrollers each have an LED connected to PA0. Both LEDs are synchronously toggled on/off in one second intervals using USART.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  DEMO LINK:
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "usart_ATmega1284.h"
#include "Timer.h"
unsigned char temp = 0x00;



void receiveTick(){
    
    if(USART_HasReceived(0)){
        temp = USART_Receive(0);
        PORTA = temp;
        USART_Flush(0);
        
    }
    
}





int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0xFF; PORTA = 0x00;

    initUSART(0);
    TimerSet(5);
    TimerOn();
    PORTA = temp;
    USART_Flush(0);
    /* Insert your solution below */
    while (1) {
    while(!TimerFlag);
    TimerFlag = 0;
    receiveTick();
    }
    return 1;
}
