#include <xc.h>
#include <stdio.h>
#include <time.h>

__CONFIG(MCLRE_OFF & WDTE_OFF & FOSC_HS & LVP_OFF & DEBUG_OFF);

#define _XTAL_FREQ 20000000

#include "i2c.h"
#include "lcd.h"
#include "rtc.h"
#include "sha1.h"
#include "hmac.h"

const char key[15] = {12, 3, 7, NULL, 9, 1, 5, NULL, 11, 2, 6, NULL, 8, 0, 4};

uint8_t i = 0;
char str[10];
long code = 0;

struct tm now;

// De tijd op het LCD scherm laten verschijnen
void draw_time()
{
    RTC_get_sec(&now);
    RTC_get_min(&now);
    RTC_get_hour(&now);
    sprintf(str, "%02i:%02i:%02i", now.tm_hour, now.tm_min, now.tm_sec);
    LCD_print_string(0, 4, str);
}

// De datum op het LCD scherm laten verschijnen
void draw_date()
{
    RTC_get_day(&now);
    RTC_get_mon(&now);
    RTC_get_year(&now);
    sprintf(str, "%02i/%02i/%04i", now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);
    LCD_print_string(0, 3, str);
}
// De tijd instellen met behulp van het LCD scherm en het toetsenbord
void set_time()
{
    i = 4;
    __delay_ms(100);
    for (;;) {
        draw_time();
        LCD_goto(1, i);
        if (i < 12)
            LCD_putch('^');
        if (PORTD & 0xF0) {
            __delay_ms(50);
            if (PORTD & 0xF0) {
                if (key[PORTD >> 4] == 11) {
                    LCD_clear();
                    __delay_ms(100);
                    return;
                } else {
                    switch (i) {
                        case 4: {
                            now.tm_hour = key[PORTD >> 4] * 10;
                        } break;

                        case 5: {
                            now.tm_hour += key[PORTD >> 4];
                            i++;
                        } break;

                        case 7: {
                            now.tm_min = key[PORTD >> 4] * 10;
                        } break;

                        case 8: {
                            now.tm_min += key[PORTD >> 4];
                            i++;
                        } break;

                        case 10: {
                            now.tm_sec = key[PORTD >> 4] * 10;
                        } break;

                        case 11: {
                            now.tm_sec += key[PORTD >> 4];
                            i++;
                        } break;
                    }
                }
                RTC_set_time(&now);
                __delay_ms(100);
                LCD_clear();
                i++;
            }
        }
    }
}







// De datum instellen met behulp van het LCD scherm en het toetsenbord
void set_date()
{
    i = 3;
    __delay_ms(100);
    for (;;) {
        draw_date();
        LCD_goto(1, i);
        if (i < 13)
            LCD_putch('^');
        if (PORTD & 0xF0) {
            __delay_ms(50);
            if (PORTD & 0xF0) {
                if (key[PORTD >> 4] == 11) {
                    LCD_clear();
                    __delay_ms(100);
                    return;
                } else {
                   switch (i) {
                        case 3: {
                            now.tm_mday = key[PORTD >> 4] * 10;
                        } break;

                        case 4: {
                            now.tm_mday += key[PORTD >> 4];
                            i++;
                        } break;

                        case 6: {
                            now.tm_mon = key[PORTD >> 4] * 10;
                        } break;

                        case 7: {
                            now.tm_mon = key[PORTD >> 4] - 1;
                            i++;
                        } break;

                        case 9: {
                            now.tm_year = (key[PORTD >> 4] == 2) ? 100 : 0;
                        } break;

                        case 11: {
                            now.tm_year += key[PORTD >> 4] * 10;
                        } break;

                        case 12: {
                            now.tm_year += key[PORTD >> 4];
                            i++;
                        } break;
                    }
                    RTC_set_date(&now);
                    __delay_ms(100);
                    LCD_clear();
                    i++;
                }
            }
        }
    }
}


// Deze functie zal de code die berekenen die op dat moment van toepassing is bij de 
// kluis, de tijd wordt hier als variable aangegeven
long get_code(long time)
{
    const char hmac_key[] = {0x66, 0x1E, 0x09, 0x48, 0x4E, 0x19, 0x35, 0xBE, 0x77, 0xDF};
    uint8_t byteArray[8] = { 0 };

    byteArray[0] = 0x00;
    byteArray[1] = 0x00;
    byteArray[2] = 0x00;
    byteArray[3] = 0x00;
    byteArray[4] = (int)((time >> 24) & 0xFF);
    byteArray[5] = (int)((time >> 16) & 0xFF);
    byteArray[6] = (int)((time >> 8) & 0xFF);
    byteArray[7] = (int)(time & 0xFF);

    HMAC_init(hmac_key, 10);
    HMAC_block(byteArray, 8);
    HMAC_done();

    uint8_t offset = shadigest.data[19] & 0x0F;
    long truncatedHash = 0;
    uint8_t j;
    for (j = 0; j < 4; ++j) {
        truncatedHash <<= 8;
        truncatedHash |= shadigest.data[offset + j];
    }

    truncatedHash &= 0x7FFFFFFF;
    truncatedHash %= 1000000;

    return truncatedHash;
}
