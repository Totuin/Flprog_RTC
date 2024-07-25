#include "flprogSTM32RTC.h"
#ifdef _STM32_DEF_

void FLProgSystemRTC::pool()
{
    if (!_isInit)
    {
        RTC_init(HOUR_FORMAT_24, LSE_CLOCK, false);
        _isInit = true;
        readTime();
        return;
    }
    if (flprog::isTimer(_startReadTime, _reqestPeriod))
    {
        readTime();
    }
    else
    {
        calculationTime();
    }
}

void FLProgSystemRTC::privateSetTime()
{
    RTC_SetTime(now.getHour(), now.getMinute(), now.getSecond(), 0, HOUR_AM);
    RTC_SetDate(uint8_t(mow.getYear() - 2000), now.getMonth(), now.getDate(), now.getDay());
}

void FLProgSystemRTC::readTime()
{

    uint8_t year, month, data, day, hour, minute, second;
    uint32_t subSec;
    hourAM_PM_t period;
    RTC_GetDate(&year, &month, &data, &day);
    RTC_GetTime(&hour, &minute, &second, &subSec, &period);
    now.setTime(second, minute, hour, data, month, (year + 2000));
    _startReadTime = millis();
}
#endif