
#include "flprogrSystemRTC.h"

FLProgSystemRTC::FLProgSystemRTC(int16_t gmt)
{
  RT_HW_Base.unixID.zone = gmt;
#ifdef FLPROG_STM32_ONBOARD_RTC_ENABLED
  FLPROG_RTC_init(HOUR_FORMAT_24, LSE_CLOCK, false);
  readTime();
#endif
}

void FLProgSystemRTC::pool()
{
#ifdef FLPROG_STM32_ONBOARD_RTC_ENABLED
  if (flprog::isTimer(_startReadTime, _reqestPeriod))
  {
    readTime();
  }
  else
  {
#endif
    RT_HW_Base.unixUpdateTime();
#ifdef FLPROG_STM32_ONBOARD_RTC_ENABLED
  }
#endif
}

void FLProgSystemRTC::privateSetTotal()
{
  RT_HW_Base.unixSetTotal();
#ifdef FLPROG_STM32_ONBOARD_RTC_ENABLED
  setTime();
#endif
}

void FLProgSystemRTC::privateSetUNIX()
{
  RT_HW_Base.unixSetTimeUNIX();
#ifdef FLPROG_STM32_ONBOARD_RTC_ENABLED
  setTime();
#endif
}

#ifdef FLPROG_STM32_ONBOARD_RTC_ENABLED
void FLProgSystemRTC::readTime()
{
  uint32_t subSec;
  flprog_hourAM_PM_t period;
  FLPROG_RTC_GetDate(&RT_HW_Base.unixID.year, &RT_HW_Base.unixID.month, &RT_HW_Base.unixID.day, &RT_HW_Base.unixID.weekDay);
  FLPROG_RTC_GetTime(&RT_HW_Base.unixID.hours, &RT_HW_Base.unixID.minutes, &RT_HW_Base.unixID.seconds, &subSec, &period);
  RT_HW_Base.unixSetTimeUNIX();
  _startReadTime = millis();
}

void FLProgSystemRTC::setTime()
{
  FLPROG_RTC_SetTime(RT_HW_Base.unixID.hours, RT_HW_Base.unixID.minutes, RT_HW_Base.unixID.seconds, 0, HOUR_AM);
  FLPROG_RTC_SetDate(RT_HW_Base.unixID.year, RT_HW_Base.unixID.month, RT_HW_Base.unixID.day, RT_HW_Base.unixID.weekDay);
}
#endif