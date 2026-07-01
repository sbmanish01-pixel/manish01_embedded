/*
 * File:   4segledcat.c
 * Author: MANISH S B
 *
 * Created on 1 July, 2026, 3:50 PM
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


const unsigned char seg[10] =
{
    0x3F,   //0
    0x06,   //1
    0x5B,   //2
    0x4F,   //3
    0x66,   //4
    0x6D,   //5
    0x7D,   //6
    0x07,   //7
    0x7F,   //8
    0x6F    //9
};

void Display(unsigned char d1,unsigned char d2,unsigned char d3,unsigned char d4)
{
    // Digit 1
    PORTB = 0x01;
    PORTD = seg[d1];
    __delay_ms(2);

    // Digit 2
    PORTB = 0x02;
    PORTD = seg[d2];
    __delay_ms(2);

    // Digit 3
    PORTB = 0x04;
    PORTD = seg[d3];
    __delay_ms(2);

    // Digit 4
    PORTB = 0x08;
    PORTD = seg[d4];
    __delay_ms(2);

    PORTB = 0x00;
}

void main()
{
    unsigned int number;
    unsigned int t;

    unsigned char th, hu, te, on;

    TRISB = 0x00;
    TRISD = 0x00;

    PORTB = 0x00;
    PORTD = 0x00;

    while(1)
    {
        for(number=0; number<=9999; number++)
        {
            th = number/1000;
            hu = (number/100)%10;
            te = (number/10)%10;
            on = number%10;

            for(t=0; t<100; t++)
            {
                Display(th,hu,te,on);
            }
        }
    }
}

