#include <xc.h>

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

volatile unsigned int count = 0;
volatile unsigned char speed = 1;

//======================
// Interrupt Routine
//======================
void __interrupt() ISR(void)
{
    if(INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0;
        TMR0 = 61;

        count++;

        if(speed == 1)
        {
            if(count >= 50)
            {
                RB0 = !RB0;
                count = 0;
            }
        }
        else if(speed == 2)
        {
            if(count >= 100)
            {
                RB0 = !RB0;
                count = 0;
            }
        }
        else if(speed == 3)
        {
            if(count >= 200)
            {
                RB0 = !RB0;
                count = 0;
            }
        }
    }
}

//======================
// Main Program
//======================
void main(void)
{
    // Disable Analog
    ADCON1 = 0x06;

    // RB0 Output
    TRISBbits.TRISB0 = 0;

    // RB1 Input
    TRISBbits.TRISB1 = 1;

    RB0 = 0;

    // Timer0 Settings
    OPTION_REGbits.T0CS = 0;   // Internal Clock
    OPTION_REGbits.PSA = 0;    // Prescaler assigned to Timer0

    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;    // 1:256

    TMR0 = 61;

    // Enable Interrupts
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;

    while(1)
    {
        if(RB1 == 0)
        {
            __delay_ms(200);

            speed++;

            if(speed > 3)
            {
                speed = 1;
            }

            count = 0;

            while(RB1 == 0);
        }
    }
}