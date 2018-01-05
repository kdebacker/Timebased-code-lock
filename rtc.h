#ifndef RTC_H
#define	RTC_H

#include <time.h>

#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 20000000
#endif

#include "i2c.h"

extern void RTC_set_time(struct tm *);
extern void RTC_get_sec(struct tm *);
extern void RTC_get_min(struct tm *);
extern void RTC_get_hour(struct tm *);
extern void RTC_set_date(struct tm *);
extern void RTC_get_day(struct tm *);
extern void RTC_get_mon(struct tm *);
extern void RTC_get_year(struct tm *);

#endif
