#include "i2c.h"

// Instellingen juist zetten voor de communicatie
void I2C_init()
{
    SSPCON = 0x28;
    SSPCON2 = 0x00;
    SSPADD = 49;
    SSPSTAT = 0x00;
    TRISC = 0x18;
}

// Wachten tot de microcontroller en de IC klaar zijn
void I2C_wait()
{
    while (!SSPIF);
    SSPIF = 0;
}

// Het startsignaal versturen
void I2C_start()
{
    SEN = 1;
    I2C_wait();
}

// Het herstartsignaal versturen
void I2C_restart()
{
    RSEN = 1;
    I2C_wait();
}

// Het stop signaal versturen
void I2C_stop()
{
    PEN = 1;
    I2C_wait();
}

// Een byte versturen
void I2C_write(uint8_t data)
{
    SSPBUF = data;
    I2C_wait();
}

// Het adres van de IC versturen
void I2C_address(uint8_t address, uint8_t mode)
{
    SSPBUF = (address << 1) + mode;
    I2C_wait();
}

// Een byte inlezen
unsigned char I2C_read(uint8_t ack)
{
    RCEN = 1;
    I2C_wait();
    ACKDT = ack;
    ACKEN = 1;
    return SSPBUF;
}
