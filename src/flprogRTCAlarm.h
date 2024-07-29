#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"
#include "flprogUnixTime.h"

#define FLPROG_ALARM_EVENT_ONLY 0
#define FLPROG_ALARM_EVENT_LATCH 1
#define FLPROG_ALARM_EVENT_TIME 2

class FLProgRtcAlarm
{
public:
    FLProgRtcAlarm(FLProgUnixTime *time, uint8_t eventDurationMode = FLPROG_ALARM_EVENT_TIME);

    void pool();
    void setSeccond(uint8_t second) { _second = second; };
    void setMinute(uint8_t minute) { _minute = minute; };
    void setHour(uint8_t hour) { _hour = hour; };
    void setDate(uint8_t date) { _date = date; };
    void setMonth(uint8_t month) { _month = month; };
    void setYear(int16_t year);

    void setDaily(bool value);
    void setMonday(bool value);
    void setTuesday(bool value);
    void setWednesday(bool value);
    void setThursday(bool value);
    void setFriday(bool value);
    void setSaturday(bool value);
    void setSunday(bool value);
    void setEventMode(uint8_t mode) { _eventDurationMode = mode; };
    void setEventDuration(uint32_t eventDuration) { _eventDuration = eventDuration; };
    void setEnable(bool value) { _enable = value; };

    bool getStatus();

    // void reset() { _resetStatus = true; };
    void reset() { _status = false; };

private:
    void checkStatus();
    void checkAlarm();
    bool checkTime();
  

    FLProgUnixTime *_time = 0;
    uint8_t _second = 255;
    uint8_t _minute = 255;
    uint8_t _hour = 255;
    uint8_t _date = 255;
    uint8_t _month = 255;
    int16_t _year = -1;
    uint8_t _day = 0;
    bool _status = false;
    bool _resetStatus = false;
    uint32_t _unixCash = 0;
    uint8_t _eventDurationMode = FLPROG_ALARM_EVENT_TIME;
    uint32_t _eventDuration = 100;
    uint32_t _eventStart;
    bool _enable = true;
};