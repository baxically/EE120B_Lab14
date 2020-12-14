/*	Author: Ally Thach, athac007
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 14  Exercise 3
 *	Exercise Description: Expand on exercise 2 by replacing "manual" mode switching with "automatic" mode switching.  *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  DEMO LINK:
 */
unsigned char tmpA = 0x00;
unsigned char tickCount = 100;
unsigned char receiveCount = 5;
unsigned char transmitCount = 200;
unsigned char currCount = 5;
unsigned char leadLED = 0x00;
unsigned int cntr = 0;

enum States{start, leader, follower} currState;
void Tick()
{
    switch(currState)
    {

        case start:
            currCount = receiveCount;
            currState = Follow;
            break;

        case leader:
            cntr = 0;
            leadLED = 1;
            if(!USART_HasReceived(0))
            {
                currState = leader;
                currCount = transmitCount;
                if(USART_IsSendReady(1))
                {
                    PORTA = tmpA;
                    USART_Send(tmpA, 1);
                    while(!USART_HasTransmitted(1))
                    {
                        continue;
                    }

                    if(tmpA == 0x01){
                        tmpA = 0x00;
                    }
                    else
                    {
                        tmpA = 0x01;
                    }
                }
            }
            else
            {
                tmpA = USART_Receive(0);
                PORTA = tmpA;
                USART_Flush(0);
                currState = follower;
                cntr = 0;
                if(USART_IsSendReady(1))
                {
                    tmpA = 0;
                    PORTA = tmpA;
                    USART_Send(0, 1);
                    while(!USART_HasTransmitted(1))
                    {
                        continue;
                    }
                }
                USART_Flush(0);
            }
            break;

        case follower:
            leadLED = 0;
            currCount = receiveCount;
            if(USART_HasReceived(0))
            {
                tmpA = USART_Receive(0);
                PORTA = tmpA;
                USART_Flush(0);
                cntr = 0;
            }
            
            if(cntr >= 3000)
            {
                cntr = 0;
                currState = leader;
            }
            break;

        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0xFF;
    PORTA = 0x00;
    DDRC = 0xFF;
    PORTC = 0x00;

    initUSART(0);
    initUSART(1);
    TimerSet(1);
    TimerOn();
    USART_Flush(0);
    currState = start;
    /* Insert your solution below */
    while (1)
    {
        while(!TimerFlag)
        {
            
        }
        TimerFlag = 0;
        tickCount++;
        cntr++;
        if(tickCount == currCount)
        {
            Tick();
            tickCount = 0;
        }
        PORTC = leadLED;
    }
    return 1;
}
