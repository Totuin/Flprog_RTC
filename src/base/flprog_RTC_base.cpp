#include "flprog_RTC_base.h"

void FLProgRTCBase::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year)
{
    uint16_t tempYear = year;
    if (tempYear < 100)
    {
        tempYear = tempYear + 2000;
    }
    if ((now.getSecond() == seconds) && (now.getMinute() == minutes) && (now.getHour() == hours) && (now.getDate() == date) && (now.getMonth() == month) && (now.getYear() == tempYear))
    {
        return;
    }
    now.setTime(seconds, minutes, hours, date, month, tempYear);
    privateSetTime();
}

void FLProgRTCBase::setSecond(uint8_t second)
{
    if (now.getSecond() == second)
    {
        return;
    }
    now.setSecond(second);
    privateSetTime();
}
void FLProgRTCBase::setMinute(uint8_t minute)
{
    if (now.getMinute() == minute)
    {
        return;
    }
    now.setMinute(minute);
    privateSetTime();
}
void FLProgRTCBase::setHour(uint8_t hour)
{
    if (now.getHour() == hour)
    {
        return;
    }
    now.setHour(hour);
    privateSetTime();
}

void FLProgRTCBase::setDate(uint8_t date)
{
    if (now.getDate() == date)
    {
        return;
    }
    now.setDate(date);
    privateSetTime();
}

void FLProgRTCBase::settMonth(uint8_t month)
{
    if (now.getMonth() == month)
    {
        return;
    }
    now.settMonth(month);
    privateSetTime();
}

void FLProgRTCBase::setYear(uint16_t year)
{
    uint16_t tempYear = year;
    if (tempYear < 100)
    {
        tempYear = tempYear + 2000;
    }
    if (now.getYear() == tempYear)
    {
        return;
    }
    now.setYear(tempYear);
    privateSetTime();
}

void FLProgRTCBase::setGmt(int16_t gmt)
{
    if (now.getGmt() == gmt)
    {
        return;
    }
    now.setGmt(gmt);
    privateSetTime();
}

void FLProgRTCBase::setUnix(uint32_t unixTime)
{
    if (now.getUnix() == unixTime)
    {
        return;
    }
    now.setUnix(unixTime);
    privateSetTime();
}

void FLProgRTCBase::calculationTime()
{
    uint32_t currentTime = millis();
    uint16_t diff = flprog::difference32(startCalculationTime, currentTime);
    uint8_t newSec = diff / 1000;
    if (newSec < 1)
    {
        return;
    }
    startCalculationTime = flprog::timeBack(diff - (newSec * 1000));
    uint32_t tempUnix = now.getUnix();
    for (uint8_t i = 0; i < newSec; i++)
    {
        tempUnix++;
    }
    now.setUnix(tempUnix);
}
