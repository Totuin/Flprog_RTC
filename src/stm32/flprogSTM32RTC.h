
#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"
#include "flprog_RTC.h"

//#if defined(STM32_CORE_VERSION) && (STM32_CORE_VERSION < 0x02000000)
//#error "This library is not compatible with core version used. Please update the core."
//#endif
 #include "rtc.h"
//#ifndef HAL_RTC_MODULE_ENABLED
//#error "RTC configuration is missing. Check flag HAL_RTC_MODULE_ENABLED in variants/board_name/stm32yzxx_hal_conf.h"
//#endif
// #include <time.h>

class FLProgSystemRTC : public FLProgRTCBase
{
public:
    FLProgSystemRTC();
    virtual void pool();
    virtual void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year, uint8_t day);

protected:
    void readTime();
    void initDevice();
    bool isInit = false;
    uint32_t startReadTime = 0;
    uint32_t reqestPeriod = 2000;
};
