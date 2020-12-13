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
#include <avr/interupt.h
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "usart_ATmega1284.h"
#endif


unsigned char output;
enum U_States {U_Init, U_On, U_Off} U_State;

void LED_Output(){
    switch(U_State){
        case U_Init:
            output = USART_Receive(0);
            U_State = U_On;
            break;
        case U_On:
            /*if (USART_HasTransmitted(0)){
                USART_Flush(0);
            }
            output = 0x01;
            UDR = output;
            if (USART_IsSendReady(0)){
                USART_Send(output, 0);
            }*/
            if (USART_HasReceived(0)){
                output = USART_Receive(0);
                USART_Flush(0);
                U_State = U_Off;
            } else {
                U_State = U_On;
            }
            break;
        case U_Off:
            /*if (USART_HasTransmitted(0)){
                                USART_Flush(0);
            }
            output = 0x01;
            UDR = output;
            if (USART_IsSendReady(0)){
                USART_Send(output, 0);
            }*/
            if (USART_HasReceived(0)){
                output = USART_Receive(0);
                USART_Flush(0);
                U_State = U_On;
            } else {
                U_State = U_Off;
            }
            break;
    }
}

//Follower Code
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0xFF; PORTA = 0x00;
    DDRD = 0x00; PORTD = 0xFF;
    /* Insert your solution below */
    TimerOn();
    TimerSet(100);
    initUSART(0);
    while (1) {
    LED_Output();
    PORTA = output;
        while (!TimerFlag) {
            
        }
        TimerFlag = 0;
    }
    return 1;
}
