#pragma once
#include "Arduino.h"
#include "flprog_RTC.h"
#if defined(SOFTWARE_SYSTEM_RTC)
class FLProgSystemRTC : public FLProgRTCBase
{
public:
    FLProgSystemRTC(int16_t gmt = 0) { setGmt(gmt); };
    virtual void pool() { calculationTime(); };
};

#endif
