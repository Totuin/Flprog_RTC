#pragma once
#include "Arduino.h"
#include "flprog_RTC.h"
#if defined(SOFTWARE_SYSTEM_RTC)
class FLProgSystemRTC : public FLProgRTCBase
{
public:
    FLProgSystemRTC(){};
    void pool();
    virtual void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year, uint8_t day);

protected:
    void initDevice();
    bool isInit = false;
};

#endif
