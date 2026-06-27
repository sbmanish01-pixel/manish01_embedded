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

void ADC_Init()
{
    ADCON0 = 0x41;     // AN0 enabled
    ADCON1 = 0x80;     // Right justified
}

unsigned int ADC_Read()
{
    GO = 1;

    while(GO);

    return ((ADRESH<<8) | ADRESL);
}

void main()
{
    unsigned int value;

    ADC_Init();

    TRISA = 0xFF;      // RA0 Input
    TRISB = 0x00;      // PORTB Output

    PORTB = 0;

    while(1)
    {
        value = ADC_Read();

        if(value < 256)
        {
            PORTB = 0b00000001;      // LED1
        }
        else if(value < 512)
        {
            PORTB = 0b00000011;      // LED1 + LED2
        }
        else if(value < 768)
        {
            PORTB = 0b00000111;      // LED1 + LED2 + LED3
        }
        else
        {
            PORTB = 0b00001111;      // All LEDs
        }

        __delay_ms(100);
    }
}