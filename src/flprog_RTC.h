#pragma once
#include "Arduino.h"

#ifdef _STM32_DEF_
#define STM32_SYSTEM_RTC
#else
#define SOFTWARE_SYSTEM_RTC
#endif

#include "flprogUtilites.h"
#include "base\flprog_RTC_base.h"

#if defined(STM32_SYSTEM_RTC)
#include "flprogSTM32RTC.h"
#endif

#if defined(SOFTWARE_SYSTEM_RTC)
#include "flprogAvrSoftRTC.h"
#endif

class FLProgI2CRTC : public FLProgRTCBase
{
public:
    virtual void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year, uint8_t day);
    int getTemperature();        // получить температуру int
    float getTemperatureFloat(); // получить температуру float
    void pool();

protected:
    void readTime();
    uint8_t unpackRegister(uint8_t data);
    uint8_t unpackHours(uint8_t data);
    uint8_t encodeRegister(int8_t data);
    int getTemperatureRaw();
    void initDevice();
    virtual void setInitData(){};
    uint8_t addres;
    FLProgI2C *i2cDevice;
    uint32_t speed = FLPROG_I2CSPEED;
    bool isInit = false;
    uint32_t startReadTime = 0;
    uint32_t reqestPeriod = 60000;
};

class FLProgDS1307 : public FLProgI2CRTC
{
public:
    FLProgDS1307(FLProgI2C *device, uint8_t addr = 0x68);

protected:
    virtual void setInitData();
};

class FLProgDS3231 : public FLProgI2CRTC
{
public:
    FLProgDS3231(FLProgI2C *device, uint8_t addr = 0x68);

protected:
    virtual void setInitData();
};