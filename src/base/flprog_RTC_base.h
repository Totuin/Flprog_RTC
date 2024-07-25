#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"
#include "flprogUnixTime.h"

class FLProgRTCBase
{
public:
    uint8_t getError() { return _codeError; };
    FLProgUnixTime *getTime() { return &now; };
    uint8_t getSecond() { return now.getSecond(); };
    uint8_t getMinute() { return now.getMinute(); };
    uint8_t getHour() { return now.getHour(); };
    uint8_t getDay() { return now.getDay(); };
    uint8_t getDate() { return now.getDate(); };
    uint8_t getMonth() { return now.getMonth(); };
    uint16_t getYear() { return now.getYear(); };
    uint32_t getUnix() { return now.getUnix(); };
    int16_t getGmt() { return now.getGmt(); };

    void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year);
    virtual void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year, uint8_t day) = 0;

    virtual void pool() {};

protected:
    void calculationTime();
    FLProgUnixTime now;
    uint8_t _codeError = 0;
    uint32_t startCalculationTime = 0;
};
