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
#include "timer.h"
#include "usart_ATmega1284.h"
#endif

unsigned char output = 0x00;

void receive()
{
    if(USART_HasReceived(0))
    {
        output = USART_Receive(0);
        PORTA = output;
        USART_Flush(0);
    }
}

//Follower Code
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0xFF; PORTA = 0x00;
    //DDRD = 0x00; PORTD = 0xFF;
    /* Insert your solution below */
    TimerOn();
    TimerSet(1000);
    initUSART(0);
    PORTA = output;
    while (1) {
        while (!TimerFlag) {
            
        }
        TimerFlag = 0;
        receiveTick();
    }
    return 1;
}
