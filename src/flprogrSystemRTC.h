#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"
#include "base/flprog_RTC_base.h"

class FLProgSystemRTC : public FLProgRTCBase
{
public:
    FLProgSystemRTC(int16_t gmt = 0);
    virtual void pool();

    virtual RT_HW_STRUCT_UNIX_ID *now() { return &RT_HW_Base.unixID; };

protected:
    virtual void privateSetTotal();
    virtual void privateSetUNIX();
};
