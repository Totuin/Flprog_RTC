#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"
#include "flprog_RTC_base.h"

class FLProgI2CRTC : public FLProgRTCBase
{
public:
    FLProgI2CRTC(FLProgI2C *device, uint8_t addr = 0x68);
    virtual void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year, uint8_t day);
    int getTemperature();        // получить температуру int
    float getTemperatureFloat(); // получить температуру float
    void pool();

protected:
    void readTime();
    uint8_t unpackRegister(uint8_t data);
    uint8_t unpackHours(uint8_t data);
    uint8_t encodeRegister(int8_t data);
    int getTemperatureRaw();
    uint8_t addres;
    FLProgI2C *i2cDevice;
    uint32_t speed = FLPROG_I2CSPEED;
    bool isInit = false;
    uint32_t startTime = 0;
};