#include "flprogAvrSoftRTC.h"

#if defined(SOFTWARE_SYSTEM_RTC)
void FLProgSystemRTC::pool()
{
    if (!isInit)
    {
        initDevice();
    }
    calculationTime();
}

void FLProgSystemRTC::initDevice()
{
    now.second = 0;
    now.minute = 0;
    now.hour = 0;
    now.day = 0;
    now.date = 1;
    now.month = 1;
    now.year = 0;
    startCalculationTime = millis();
    isInit = true;
}

void FLProgSystemRTC::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
    now.second = seconds;
    now.minute = minutes;
    now.hour = hours;
    now.day = day;
    now.date = date;
    now.month = month;
    now.year = year;
    startCalculationTime = millis();
}
#endif
