#ifndef _I2C_H_
#define _I2C_H_

#include <xc.h>
#include <stdint.h>

#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 20000000
#endif

extern void I2C_init(void);
extern void I2C_wait(void);
extern void I2C_start(void);
extern void I2C_restart(void);
extern void I2C_stop(void);
extern void I2C_write(uint8_t);
extern void I2C_address(uint8_t, uint8_t);
extern unsigned char I2C_read(uint8_t);

#endif
