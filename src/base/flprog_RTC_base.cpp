#include "flprog_RTC_base.h"

void FLProgRTCBase::setNewTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year)
{
    uint16_t tempYear = year;
    if (tempYear > 100)
    {
        tempYear = tempYear - 2000;
    }
    if ((getSecond() == seconds) && (getMinute() == minutes) && (getHour() == hours) && (getDate() == date) && (getMonth() == month) && (getYear() == tempYear))
    {
        return;
    }
    now()->seconds = seconds;
    now()->minutes = minutes;
    now()->hours = hours;
    now()->day = date;
    now()->month = month;
    now()->year = tempYear;
    privateSetUNIX();
}

void FLProgRTCBase::setSecond(uint8_t second)
{
    if (getSecond() == second)
    {
        return;
    }
    now()->seconds = second;
    privateSetUNIX();
}
void FLProgRTCBase::setMinute(uint8_t minute)
{
    if (getMinute() == minute)
    {
        return;
    }
    now()->minutes = minute;
    privateSetUNIX();
}

void FLProgRTCBase::setHour(uint8_t hour)
{
    if (getHour() == hour)
    {
        return;
    }
    now()->hours = hour;
    privateSetUNIX();
}

void FLProgRTCBase::setDate(uint8_t date)
{
    if (getDate() == date)
    {
        return;
    }
    now()->day = date;
    privateSetUNIX();
}

void FLProgRTCBase::settMonth(uint8_t month)
{
    if (getMonth() == month)
    {
        return;
    }
    now()->month = month;
    privateSetUNIX();
}

void FLProgRTCBase::setYear(uint16_t year)
{
    uint16_t tempYear = year;
    if (tempYear > 100)
    {
        tempYear = tempYear - 2000;
    }
    if (now()->year == tempYear)
    {
        return;
    }
    now()->year = tempYear;
    privateSetUNIX();
}

void FLProgRTCBase::setGmt(int16_t gmt)
{
    if (getGmt() == gmt)
    {
        return;
    }
    now()->zone = gmt;
    privateSetTotal();
}

void FLProgRTCBase::setUnix(uint32_t unixTime)
{
    if (getUnix() == unixTime)
    {
        return;
    }
    now()->timeUNIX = unixTime;
    privateSetTotal();
}
