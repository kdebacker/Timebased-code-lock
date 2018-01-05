#ifndef _LCD_H_
#define _LCD_H_

#include <xc.h>
#include <stdint.h>

#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 20000000
#endif

#define LCD_RS  RB2
#define LCD_E   RB3
#define LCD_D4  RB4
#define LCD_D5  RB5
#define LCD_D6  RB6
#define LCD_D7  RB7

extern void LCD_port(uint8_t);
extern void LCD_strobe(void);
extern void LCD_send_cmd(uint8_t);
extern void LCD_clear(void);
extern void LCD_goto(uint8_t, uint8_t);
extern void LCD_init(void);
extern void LCD_putch(char);
extern void LCD_print_string(uint8_t, uint8_t, const char *);

#endif
