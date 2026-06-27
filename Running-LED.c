/*
 * File:   Running-LED.c
 * Author: MANISH S B
 *
 * Created on 27 June, 2026, 3:27 PM
 */


#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

volatile unsigned int count = 0;
volatile unsigned char led = 0;
volatile unsigned char speed = 1;     // 1=Slow, 2=Medium, 3=Fast

void __interrupt() ISR(void)
{
    if(INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0;
        TMR0 = 61;

        count++;

        if(speed == 1)          // Slow
        {
            if(count >= 50)
            {
                count = 0;
                led++;
            }
        }
        else if(speed == 2)     // Medium
        {
            if(count >= 25)
            {
                count = 0;
                led++;
            }
        }
        else                    // Fast
        {
            if(count >= 10)
            {
                count = 0;
                led++;
            }
        }

        if(led > 3)
            led = 0;

        PORTB = (1 << led);
    }
}

void main()
{
    ADCON1 = 0x06;

    // RB0-RB3 Output
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;

    // RB4 Input (Push Button)
    TRISBbits.TRISB4 = 1;

    PORTB = 0x01;

    // Timer0 Settings
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;

    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;

    TMR0 = 61;

    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;

    while(1)
    {
        // Push Button Pressed
        if(RB4 == 0)
        {
            __delay_ms(200);      // Debounce

            speed++;

            if(speed > 3)
                speed = 1;

            while(RB4 == 0);      // Wait until button released
        }
    }
}