/*
 * File:   1segmentedled.c
 * Author: MANISH S B
 *
 * Created on 1 July, 2026, 2:49 PM
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
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F
};

void main(void)
{
    unsigned char i;

    TRISD = 0x00;
    PORTD = 0x00;

    while(1)
    {
        for(i=0; i<10; i++)
        {
            PORTD = digit[i];
            __delay_ms(1000);
        }
    }
}