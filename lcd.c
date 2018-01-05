#include "lcd.h"

// De data omzetten naar een 
void LCD_port(uint8_t a)
{
    LCD_D4 = (a & 1) ? 1 : 0;
    LCD_D5 = (a & 2) ? 1 : 0;
    LCD_D6 = (a & 4) ? 1 : 0;
    LCD_D7 = (a & 8) ? 1 : 0;
}

// Een puls geven op de enable ingang van het LCD scherm
void LCD_strobe()
{
    LCD_E = 1;
    __delay_us(50);
    LCD_E = 0;
}

// Een commando sturen naar het LCD scherm
void LCD_send_cmd(uint8_t cmd)
{
    LCD_RS = 0;
    LCD_port((cmd & 0xF0) >> 4);
    LCD_strobe();
    __delay_ms(5);
    LCD_port(cmd & 0x0F);
    LCD_strobe();
    __delay_ms(5);
}

// Het LCD scherm leeg maken
void LCD_clear()
{
    LCD_send_cmd(0x01);
    __delay_us(1700);
}

// De cursor naar een bepaalde locatie op het LCD scherm laten gaan
void LCD_goto(uint8_t a, uint8_t b)
{
    LCD_send_cmd(0x80 + (a * 0x40) + b);
}

// Het LCD scherm bepaalde instellingen doorsturen
void LCD_init()
{
    LCD_port(0x00);
    __delay_ms(50);
    LCD_port(0x02);
    LCD_strobe();
    __delay_ms(5);
    LCD_send_cmd(0x28);
    LCD_send_cmd(0x08);
    LCD_clear();
    LCD_send_cmd(0x06);
    LCD_send_cmd(0x0C);
}

// Een teken op het LCD scherm laten verschijnen
void LCD_putch(char chr)
{
    LCD_RS = 1;
    LCD_port((chr & 0xF0) >> 4);
    LCD_strobe();
    LCD_port(chr & 0x0F);
    LCD_strobe();
}

// Een reeks tekens op een bepaalde plaats op het LCD scherm laten verschijnen
void LCD_print_string(uint8_t a, uint8_t b, const char *str)
{
    LCD_goto(a, b);
    for (str; *str != '\0'; str++) {
        LCD_putch(*str);
    }
}
