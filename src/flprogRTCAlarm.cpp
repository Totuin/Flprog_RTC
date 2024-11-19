#include "flprogRTCAlarm.h"

FLProgRtcAlarm::FLProgRtcAlarm(RT_HW_STRUCT_UNIX_ID *time, uint8_t eventDurationMode)
{
    _time = time;
    _eventDurationMode = eventDurationMode;
    setDaily(true);
}

void FLProgRtcAlarm::pool()
{
    if (!_enable)
    {
        _status = false;
        _oldStatus = false;
    }
    if (_status)
    {
        if (_eventDurationMode == FLPROG_ALARM_EVENT_LATCH)
        {
            return;
        }
        if (_eventDurationMode == FLPROG_ALARM_EVENT_ONLY)
        {
            _status = false;
            return;
        }
        if (flprog::isTimer(_eventStart, _eventDuration))
        {
            _status = false;
        }
        return;
    }
    if (_unixCash == _time->timeUNIX)
    {
        return;
    }
    _unixCash = _time->timeUNIX;
    bool temp = checkTime();
    if (temp)
    {
        if (!_oldStatus)
        {
            _status = temp;
            _eventStart = millis();
        }
    }
    _oldStatus = temp;
}

bool FLProgRtcAlarm::checkTime()
{
    if (_second < 60)
    {
        if (_time->seconds != _second)
        {
            return false;
        }
    }
    if (_minute < 60)
    {
        if (_time->minutes != _minute)
        {
            return false;
        }
    }
    if (_hour < 24)
    {
        if (_time->hours != _hour)
        {
            return false;
        }
    }
    if (_date < 32)
    {
        if (_time->day != _date)
        {
            return false;
        }
    }
    if (_month < 13)
    {
        if (_time->month != _month)
        {
            return false;
        }
    }
    if (_year > -1)
    {
        if (_time->year != _year)
        {
            return false;
        }
    }
    if (bitRead(_day, 0))
    {
        return true;
    }
    return bitRead(_day, (_time->weekDay));
}

void FLProgRtcAlarm::setDaily(bool value)
{
    bitWrite(_day, 0, value);
}

void FLProgRtcAlarm::setMonday(bool value)
{
    bitWrite(_day, 1, value);
    setDaily(false);
}

void FLProgRtcAlarm::setTuesday(bool value)
{
    bitWrite(_day, 2, value);
    setDaily(false);
}

void FLProgRtcAlarm::setWednesday(bool value)
{
    bitWrite(_day, 3, value);
    setDaily(false);
}

void FLProgRtcAlarm::setThursday(bool value)
{
    bitWrite(_day, 4, value);
    setDaily(false);
}

void FLProgRtcAlarm::setFriday(bool value)
{
    bitWrite(_day, 5, value);
    setDaily(false);
}

void FLProgRtcAlarm::setSaturday(bool value)
{
    bitWrite(_day, 6, value);
    setDaily(false);
}

void FLProgRtcAlarm::setSunday(bool value)
{
    bitWrite(_day, 7, value);
    setDaily(false);
}

void FLProgRtcAlarm::setYear(int16_t year)
{
    _year = year;
}