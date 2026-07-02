/*
 * File:   motor_speedcontroll.c
 * Author: MANISH S B
 *
 * Created on 2 July, 2026, 3:54 PM
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

unsigned int speedLevel = 0;

//---------------- PWM ----------------//

void PWM_Init()
{
    TRISC2 = 0;

    PR2 = 249;

    CCP1CON = 0x0C;

    T2CON = 0x04;
}

void PWM_SetDuty(unsigned int duty)
{
    if(duty > 1023)
        duty = 1023;

    CCPR1L = duty >> 2;

    CCP1CON &= 0xCF;
    CCP1CON |= ((duty & 0x03)<<4);
}

//------------------------------------//

void main()
{
    TRISB0 = 1;      // Push Button Input

    TRISD0 = 0;
    TRISD1 = 0;

    RD0 = 1;
    RD1 = 0;

    PWM_Init();

    PWM_SetDuty(0);

    while(1)
    {
        if(RB0 == 0)          // Button Pressed
        {
            __delay_ms(30);   // Debounce

            while(RB0 == 0);  // Wait until release

            speedLevel++;

            if(speedLevel > 4)
                speedLevel = 0;

            switch(speedLevel)
            {
                case 0:
                    PWM_SetDuty(0);        // OFF
                    break;

                case 1:
                    PWM_SetDuty(256);      // 25%
                    break;

                case 2:
                    PWM_SetDuty(512);      // 50%
                    break;

                case 3:
                    PWM_SetDuty(768);      // 75%
                    break;

                case 4:
                    PWM_SetDuty(1023);     // 100%
                    break;
            }

            __delay_ms(200);
        }
    }
}
