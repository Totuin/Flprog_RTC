#include "flprog_RTC_base.h"

uint16_t FLProgRTCBase::getWeekDay(uint16_t y, uint8_t m, uint8_t d)
{
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += ds_dim(i - 1);
    if (m > 2 && y % 4 == 0)
        days++;
    return (days + 365 * y + (y + 3) / 4 + 4) % 7 + 1;
}

uint8_t FLProgRTCBase::ds_dim(uint8_t i)
{
    return (i < 7) ? ((i == 1) ? 28 : ((i & 1) ? 30 : 31)) : ((i & 1) ? 31 : 30);
}

void FLProgRTCBase::setTime(DateTime time)
{
    setTime(time.second, time.minute, time.hour, time.date, time.month, time.year, time.day);
}

uint32_t FLProgRTCBase::getUnix(int16_t gmt)
{
    if (abs(gmt) <= 12)
        gmt *= 60;
    int8_t my = (now.month >= 3) ? 1 : 0;
    uint16_t y = now.year + my - 1970;
    uint16_t dm = 0;
    for (int i = 0; i < now.month - 1; i++)
        dm += ds_dim(i);
    return (((now.date - 1 + dm + ((y + 1) / 4) - ((y + 69) / 100) + ((y + 369) / 100 / 4) + 365 * (y - my)) * 24ul + now.hour) * 60ul + now.minute - gmt) * 60ul + now.second;
}

void FLProgRTCBase::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year)
{
    uint8_t day = getWeekDay(year, month, date);
    setTime(seconds, minutes, hours, date, month, year, day);
}
