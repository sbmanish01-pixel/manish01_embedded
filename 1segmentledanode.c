/*
 * File:   1segmentledanode.c
 * Author: MANISH S B
 *
 * Created on 1 July, 2026, 3:10 PM
 */


#include <xc.h>

#define _XTAL_FREQ 20000000

// CONFIG
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

unsigned char digit[10] =
{
    0xC0,   
    0xF9,  
    0xA4,   
    0xB0,   
    0x99,   
    0x92,   
    0x82,   
    0xF8,   
    0x80,   
    0x90 
};

void main(void)
{
    unsigned char i;

    TRISD = 0x00;
    PORTD = 0xFF;      

    while(1)
    {
        for(i = 0; i < 10; i++)
        {
            PORTD = digit[i];
            __delay_ms(1000);
        }
    }
}
