#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"
#include "base/flprog_RTC_base.h"

#ifdef ARDUINO_ARCH_STM32
#include "flprogRtcStm32.h"
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

#ifdef ARDUINO_ARCH_STM32
    void readTime();
    void setTime();
    bool _isInit = false;
    uint32_t _startReadTime = flprog::timeBack(2000);
    uint32_t _reqestPeriod = 2000;
#endif
};
