#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"
#include "base/flprog_RTC_base.h"

#ifdef ARDUINO_ARCH_STM32
#if defined(HAL_RTC_MODULE_ENABLED) && !defined(HAL_RTC_MODULE_ONLY)
#include "flprogRtcStm32.h"
#define FLPROG_STM32_ONBOARD_RTC_ENABLED
#endif
#endif

class FLProgSystemRTC : public FLProgRTCBase
{
public:
    FLProgSystemRTC(int16_t gmt = 0);
    virtual void pool();

    virtual RT_HW_STRUCT_UNIX_ID *now() { return &RT_HW_Base.unixID; };

protected:
    virtual void privateSetTotal();
    virtual void privateSetUNIX();

#ifdef FLPROG_STM32_ONBOARD_RTC_ENABLED
    void readTime();
    void setTime();
    bool _isInit = false;
    uint32_t _startReadTime = flprog::timeBack(2000);
    uint32_t _reqestPeriod = 2000;
#endif
};
