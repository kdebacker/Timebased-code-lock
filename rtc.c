#include "rtc.h"

// De tijd instellen, zowel de uren als de minuten als de seconden
void RTC_set_time(struct tm *time)
{
    I2C_start();
    I2C_address(0x68, 0);
    I2C_write(0x00);
    I2C_write(((time->tm_sec / 10) << 4) + (time->tm_sec % 10));
    I2C_write(((time->tm_min / 10) << 4) + (time->tm_min % 10));
    I2C_write(((time->tm_hour / 10) << 4) + (time->tm_hour % 10));
    I2C_stop();
}

// De seconden uitlezen uit de DS1307
void RTC_get_sec(struct tm *time)
{
    I2C_start();
    I2C_address(0x68, 0);
    I2C_write(0x00);
    I2C_restart();
    I2C_address(0x68, 1);
    uint8_t s = I2C_read(1);
    I2C_stop();
    time->tm_sec = (s & 0x0F) + ((s >> 4) * 10);
}

// De minuten uitlezen uit de DS1307
void RTC_get_min(struct tm *time)
{
    I2C_start();
    I2C_address(0x68, 0);
    I2C_write(0x01);
    I2C_restart();
    I2C_address(0x68, 1);
    uint8_t m = I2C_read(1);
    I2C_stop();
    time->tm_min = (m & 0x0F) + ((m >> 4) * 10);
}

// De uren uitlezen uit de DS1307
void RTC_get_hour(struct tm *time)
{
    I2C_start();
    I2C_address(0x68, 0);
    I2C_write(0x02);
    I2C_restart();
    I2C_address(0x68, 1);
    uint8_t h = I2C_read(1);
    I2C_stop();
    time->tm_hour = (h & 0x0F) + ((h >> 4) * 10);
}

// De datum instellen, zowel de dagen als de maanden als de jaren
void RTC_set_date(struct tm *date)
{
    I2C_start();
    I2C_address(0x68, 0);
    I2C_write(0x04);
    I2C_write(((date->tm_mday / 10) << 4) + (date->tm_mday % 10));
    I2C_write(((date->tm_mon / 10) << 4) + (date->tm_mon % 10));
    I2C_write(((date->tm_year / 10) << 4) + (date->tm_year % 10));
    I2C_stop();
}

// De dagen uitlezen uit de DS13107
void RTC_get_day(struct tm *date)
{
    I2C_start();
    I2C_address(0x68, 0);
    I2C_write(0x04);
    I2C_restart();
    I2C_address(0x68, 1);
    uint8_t d = I2C_read(1);
    I2C_stop();
    date->tm_mday = (d & 0x0F) + ((d >> 4) * 10);
}

// De maanden uitlezen uit de DS1307
void RTC_get_mon(struct tm *date)
{
    I2C_start();
    I2C_address(0x68, 0);
    I2C_write(0x05);
    I2C_restart();
    I2C_address(0x68, 1);
    uint8_t m = I2C_read(1);
    I2C_stop();
    date->tm_mon = (m & 0x0F) + ((m >> 4) * 10);
}

// De jaren uitlezen uit de DS1307
void RTC_get_year(struct tm *date)
{
    I2C_start();
    I2C_address(0x68, 0);
    I2C_write(0x06);
    I2C_restart();
    I2C_address(0x68, 1);
    uint8_t y = I2C_read(1);
    I2C_stop();
    date->tm_year = (y & 0x0F) + ((y >> 4) * 10);
}
