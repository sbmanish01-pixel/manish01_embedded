#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 20000000

// CONFIGURATION BITS
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

void UART_Init(void)
{
    TRISC6 = 0;
    TRISC7 = 1;

    SPBRG = 129;      // 9600 baud @20MHz
    BRGH = 1;

    SYNC = 0;
    SPEN = 1;

    TXEN = 1;
    CREN = 1;
}

void UART_Write(char data)
{
    while(!TXIF);
    TXREG = data;
}

void UART_String(char *str)
{
    while(*str)
    {
        UART_Write(*str++);
    }
}

void ADC_Init(void)
{
    ADCON0 = 0x41;    // AN0 enabled
    ADCON1 = 0x80;    // Right justified
}

unsigned int ADC_Read()
{
    GO = 1;

    while(GO);

    return ((ADRESH<<8)+ADRESL);
}

void main()
{
    char buffer[20];
    unsigned int value;

    UART_Init();
    ADC_Init();

    while(1)
    {
        value = ADC_Read();

        sprintf(buffer,"%u\r\n",value);

        UART_String(buffer);

        __delay_ms(500);
    }
}