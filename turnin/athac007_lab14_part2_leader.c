/*	Author: Ally Thach, athac007
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 14  Exercise 2
 *	Exercise Description: Expand upon Exercise 1 by adding a switch that determines the mode (Leader or Follower) of the microcontroller.
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

unsigned char tmpA = 0x00;
unsigned char toggle;

void sendTick()
{
    if(USART_IsSendReady(0))
    {
        PORTA = tmpA;
        USART_Send(tmpA, 0);
        while(!USART_HasTransmitted(0))
        {
            continue;
        }

        if(tmpA == 0x01)
        {
            tmpA = 0x00;
        }
        else
        {
            tmpA = 0x01;
        }
        
    }
}

void receiveTick()
{
    if(USART_HasReceived(0))
    {
        tmpA = USART_Receive(0);
        PORTA = tmpA;
        USART_Flush(0);
        
    }
    
}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0xFF;
    PORTA = 0x00;
    DDRC = 0xFF;
    PORTC = 0x00;
    DDRB = 0x00;
    PORTB = 0xFF;
    initUSART(0);
    TimerSet(500);
    TimerOn();
    
    /* Insert your solution below */
    while (1)
    {
        toggle = ~PINB;
        while(!TimerFlag);
        TimerFlag = 0;
        if (toggle == 0x00)
        {
            TimerSet(500);
            PORTC = 0xFF;
            sendTick();
        }
        else
        {
            TimerSet(5);
            PORTC = 0x00;
            receiveTick();
        }
    }
    return 1;
}
