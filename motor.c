/*
 * File:   motor.c
 * Author: MANISH S B
 *
 * Created on 2 July, 2026, 3:22 PM
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

unsigned int ADC_Read(unsigned char channel);

void PWM_Init()
{
    TRISC2 = 0;

    PR2 = 249;

    CCP1CON = 0x0C;

    T2CON = 0x04;
}

void PWM_Duty(unsigned int duty)
{
    if(duty > 1023)
        duty = 1023;

    CCPR1L = duty >> 2;

    CCP1CON &= 0xCF;
    CCP1CON |= ((duty & 0x03) << 4);
}

void ADC_Init()
{
    ADCON0 = 0x41;      // AN0 selected, ADC ON
    ADCON1 = 0x8E;      // AN0 analog, right justified
}

unsigned int ADC_Read(unsigned char channel)
{
    ADCON0 &= 0b11000101;
    ADCON0 |= channel << 3;

    __delay_us(20);

    GO_DONE = 1;

    while(GO_DONE);

    return ((ADRESH << 8) + ADRESL);
}

void main()
{
    unsigned int adc;

    ADC_Init();
    PWM_Init();

    TRISA = 0x01;      // RA0 input

    TRISD0 = 0;
    TRISD1 = 0;

    RD0 = 1;
    RD1 = 0;

    while(1)
    {
        adc = ADC_Read(0);

        PWM_Duty(adc);

        __delay_ms(20);
    }
}