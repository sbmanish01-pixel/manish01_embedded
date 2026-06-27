/*
 * File:   traffic_light.c
 * Author: MANISH S B
 *
 * Created on 23 June, 2026, 4:01 PM
 */


#include <xc.h>

#define _XTAL_FREQ 4000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

void main(void)
{
    TRISB = 0x00;     
    PORTB = 0x00;

    while(1)
    {
        
        RB0 = 1;
        RB1 = 0;
        RB2 = 0;
        __delay_ms(3000);

        
        RB0 = 0;
        RB1 = 1;
        RB2 = 0;
        __delay_ms(1000);

        
        RB0 = 0;
        RB1 = 0;
        RB2 = 1;
        __delay_ms(4500);
    }
}