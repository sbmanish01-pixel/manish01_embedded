/*
 * File:   lcddisplay.c
 * Author: MANISH S B
 *
 * Created on 1 July, 2026, 4:23 PM
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

#define RS RC0
#define EN RC1

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_init(void);
void lcd_string(const char *);

void lcd_enable()
{
    EN = 1;
    __delay_ms(2);
    EN = 0;
}

void lcd_cmd(unsigned char cmd)
{
    RS = 0;

    RD4 = (cmd >> 4) & 1;
    RD5 = (cmd >> 5) & 1;
    RD6 = (cmd >> 6) & 1;
    RD7 = (cmd >> 7) & 1;
    lcd_enable();

    RD4 = cmd & 1;
    RD5 = (cmd >> 1) & 1;
    RD6 = (cmd >> 2) & 1;
    RD7 = (cmd >> 3) & 1;
    lcd_enable();

    __delay_ms(2);
}

void lcd_data(unsigned char data)
{
    RS = 1;

    RD4 = (data >> 4) & 1;
    RD5 = (data >> 5) & 1;
    RD6 = (data >> 6) & 1;
    RD7 = (data >> 7) & 1;
    lcd_enable();

    RD4 = data & 1;
    RD5 = (data >> 1) & 1;
    RD6 = (data >> 2) & 1;
    RD7 = (data >> 3) & 1;
    lcd_enable();

    __delay_ms(2);
}

void lcd_init()
{
    __delay_ms(20);

    lcd_cmd(0x02);   // 4-bit mode
    lcd_cmd(0x28);   // 2 lines, 5x7 font
    lcd_cmd(0x0C);   // Display ON
    lcd_cmd(0x06);   // Cursor increment
    lcd_cmd(0x01);   // Clear display

    __delay_ms(2);
}

void lcd_string(const char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

void scroll_message()
{
    char msg[] = "   WELCOME TO EMBEDDED SYSTEM   ";
    unsigned char i, j;

    while(1)
    {
        for(i = 0; msg[i + 15] != '\0'; i++)
        {
            lcd_cmd(0x80);      // Move cursor to first line

            for(j = 0; j < 16; j++)
            {
                lcd_data(msg[i + j]);
            }

            __delay_ms(300);
        }
    }
}

void main()
{
    TRISC = 0x00;
    TRISD = 0x00;

    PORTC = 0x00;
    PORTD = 0x00;

    lcd_init();

    scroll_message();
}