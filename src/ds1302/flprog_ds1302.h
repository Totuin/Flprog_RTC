#pragma once
#include "Arduino.h"
#include "flprog_RTC.h"
#ifndef _BV
#define _BV(b) (1UL << (b))
#endif

class FLProgDS1302 : public FLProgRTCBase
{
public:
    FLProgDS1302(uint8_t res, uint8_t clk, uint8_t dat);
    void pool();
    virtual void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year, uint8_t day);

protected:
    void readTime();
    void initDevice();

    void beginTransmission(uint8_t command);
    void endTransmission();
    void write(uint8_t value, bool isDataRequestCommand = false);
    uint8_t read();

    uint8_t BcdToUint8(uint8_t val) { return val - 6 * (val >> 4); };
    uint8_t Uint8ToBcd(uint8_t val) { return val + 6 * (val / 10); };
    uint8_t BcdToBin24Hour(uint8_t bcdHour);

    uint8_t pinRES;
    uint8_t pinCLK;
    uint8_t pinDAT;
    bool isInit;
    uint32_t startReadTime = 0;
    uint32_t reqestPeriod = 60000;
    uint8_t varI;
};