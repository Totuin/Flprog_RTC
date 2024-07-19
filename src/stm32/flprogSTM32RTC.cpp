#include "flprogSTM32RTC.h"
#ifdef _STM32_DEF_

void FLProgSystemRTC::pool()
{
    if ((startReadTime == 0) || (flprog::isTimer(startReadTime, reqestPeriod)))
    {
        readTime();
    }
}

void FLProgSystemRTC::readTime()
{
    if (!isInit)
    {
        initDevice();
    }
    uint8_t year, month, data, day, hour, minute, second;
    uint32_t subSec;
    hourAM_PM_t period;
    RTC_GetDate(&year, &month, &data, &day);
    RTC_GetTime(&hour, &minute, &second, &subSec, &period);
    now.second = second;
    now.minute = minute;
    now.hour = hour;
    now.day = day;
    now.date = data;
    now.month = month;
    now.year = year;
    startCalculationTime = millis();
}

void FLProgSystemRTC::initDevice()
{
    RTC_init(HOUR_FORMAT_24, LSE_CLOCK, false);
    isInit = true;
}

void FLProgSystemRTC::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
    RTC_SetTime(hours, minutes, seconds, 0, HOUR_AM);
    RTC_SetDate(year, month, date, day);
    readTime();
}
#endif
