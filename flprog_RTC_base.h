#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"

struct DateTime
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint16_t year;
};

class FLProgRTCBase
{
public:
    uint8_t getError() { return codeError; };
    DateTime getTime() { return now; };
    uint16_t getWeekDay(uint16_t y, uint8_t m, uint8_t d);
    void setTime(DateTime time);
    void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year );
    virtual void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year, uint8_t day){};
    uint32_t getUnix(int16_t gmt); // получить unix время (указать свой часовой пояс в часах ИЛИ минутах)
protected:
    uint8_t ds_dim(uint8_t i);
    DateTime now;
    uint8_t codeError = FLPROG_SENSOR_NOT_ERROR;
};