#include "flprog_RTC_base.h"

void FLProgRTCBase::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year)
{
    uint16_t tempYear = year;
    if (tempYear < 2000)
    {
        tempYear = tempYear + 2000;
    }
    now.setTime(seconds, minutes, hours, date, month, tempYear);
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
