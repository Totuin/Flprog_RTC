#pragma once
#include "Arduino.h"
#include "flprog_RTC.h"
#if defined(SOFTWARE_SYSTEM_RTC)
class FLProgSystemRTC : public FLProgRTCBase
{
public:
    virtual void pool() { calculationTime(); };

protected:
    virtual void privateSetTime() {};
};

#endif