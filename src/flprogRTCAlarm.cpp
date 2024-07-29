#include "flprogRTCAlarm.h"

FLProgRtcAlarm::FLProgRtcAlarm(FLProgUnixTime *time, uint8_t eventDurationMode)
{
    _time = time;
    _eventDurationMode = eventDurationMode;
    setDaily(true);
}

bool FLProgRtcAlarm::getStatus()
{
    return _status;
    /*
    if (!_enable)
    {
        return false;
    }
    if (!_status)
    {
        return false;
    }
    if (_resetStatus)
    {
        return false;
    }
    return true;
    */
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
    if ((year > -1) && (year < 100))
    {
        year = year + 2000;
    }
    _year = year;
}

void FLProgRtcAlarm::pool()
{
    /*
    if (_status && (!_resetStatus))
    {
        checkStatus();
        return;
    }
     */
    if (_unixCash == _time->getUnix())
    {
        return;
    }

    checkAlarm();
}

void FLProgRtcAlarm::checkStatus()
{
    /*
    if (_eventDurationMode == FLPROG_ALARM_EVENT_LATCH)
    {
        return;
    }
    if (_eventDurationMode == FLPROG_ALARM_EVENT_ONLY)
    {
        _resetStatus = true;
        return;
    }
    if (flprog::isTimer(_eventStart, _eventDuration))
    {
        _resetStatus = true;
        return;
    }
    */
}

void FLProgRtcAlarm::checkAlarm()
{
    _unixCash = _time->getUnix();
    bool temp = checkTime();
    if (temp)
    {
        _status = temp;
    }
    /*
    if (temp)
    {
        if (!_status)
        {
            _eventStart = millis();
        }
    }
    else
    {
        _resetStatus = false;
    }
    _status = temp;
    */
}

bool FLProgRtcAlarm::checkTime()
{
    if (_second < 60)
    {
        if (_time->getSecond() != _second)
        {
            return false;
        }
    }
    if (_minute < 60)
    {
        if (_time->getMinute() != _minute)
        {
            return false;
        }
    }
    if (_hour < 24)
    {
        if (_time->getHour() != _hour)
        {
            return false;
        }
    }
    if (_date < 32)
    {
        if (_time->getDate() != _date)
        {
            return false;
        }
    }
    if (_month < 13)
    {
        if (_time->getMonth() != _month)
        {
            return false;
        }
    }
    if (_year > -1)
    {
        if (_time->getYear() != _year)
        {
            return false;
        }
    }
    if (bitRead(_day, 0))
    {
        return true;
    }
    return bitRead(_day, (_time->getDay()));
}
