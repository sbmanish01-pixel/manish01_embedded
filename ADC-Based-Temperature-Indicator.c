/*
 * File:   ADC-Based-Temperature-Indicator.c
 * Author: MANISH S B
 *
 * Created on 27 June, 2026, 3:56 PM
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


void ADC_Init()
{
    ADCON0 = 0x41;      
    ADCON1 = 0x80;      
}


unsigned int ADC_Read()
{
    __delay_us(20);     // Acquisition time

    GO_nDONE = 1;       // Start conversion

    while(GO_nDONE);    // Wait until conversion complete

    return ((ADRESH << 8) | ADRESL);
}

//---------------- Main ----------------//
void main()
{
    unsigned int adc_value;

    ADC_Init();

    TRISA = 0xFF;       // RA0 Input
    TRISB = 0x00;       // PORTB Output

    PORTB = 0x00;

    while(1)
    {
        adc_value = ADC_Read();

        if(adc_value < 341)
        {
            PORTB = 0b00000001;      // Green LED ON
        }
        else if(adc_value < 682)
        {
            PORTB = 0b00000010;      // Yellow LED ON
        }
        else
        {
            PORTB = 0b00000100;      // Red LED ON
        }

        __delay_ms(100);
    }
}