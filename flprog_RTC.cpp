#include "flprog_RTC.h"

FLProgI2CRTC::FLProgI2CRTC(FLProgI2C *device, uint8_t addr)
{
    i2cDevice = device;
    addres = addr;
}

void FLProgI2CRTC::pool()
{
    if ((startReadTime == 0) || (flprog::isTimer(startReadTime, reqestPeriod)))
    {
        startReadTime = millis();
        startCalculationTime = millis();
        readTime();
    }
    if (flprog::isTimer(startCalculationTime, 250))
    {
        if (isInit)
        {
            calculationTime();
        }
        else
        {
            readTime();
            startReadTime = millis();
        }
    }
}

uint8_t FLProgI2CRTC::unpackRegister(uint8_t data)
{
    return ((data >> 4) * 10 + (data & 0xF));
}

uint8_t FLProgI2CRTC::unpackHours(uint8_t data)
{
    if (data & 0x20)
    {
        return ((data & 0xF) + 20);
    }
    if (data & 0x10)
    {
        return ((data & 0xF) + 10);
    }
    return (data & 0xF);
}

uint8_t FLProgI2CRTC::encodeRegister(int8_t data)
{
    return (((data / 10) << 4) | (data % 10));
}

void FLProgI2CRTC::initDevice()
{
    if (i2cDevice->findAddr(addres))
    {
        isInit = true;
        readTime();
        return;
    }
    codeError = FLPROG_SENSOR_DEVICE_NOT_FOUND_ERROR;
}

void FLProgI2CRTC::readTime()
{
    if (!isInit)
    {
        initDevice();
        return;
    }

    uint8_t data[7];
    codeError = i2cDevice->fullWrite(addres, 0x0);
    if (codeError)
    {
        isInit = false;
        return;
    }
    codeError = i2cDevice->fullRead(addres, data, 7);
    if (codeError)
    {
        isInit = false;
        return;
    }
    now.second = unpackRegister(data[0]);
    now.minute = unpackRegister(data[1]);
    now.hour = unpackHours(data[2]);
    now.day = data[3];
    now.date = unpackRegister(data[4]);
    now.month = unpackRegister(data[5]);
    now.year = unpackRegister(data[6]);
}

void FLProgI2CRTC::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
    month = constrain(month, 1, 12);
    date = constrain(date, 0, ds_dim(month - 1));
    seconds = constrain(seconds, 0, 59);
    minutes = constrain(minutes, 0, 59);
    hours = constrain(hours, 0, 23);
    uint8_t data[8];
    data[0] = 0x00;
    data[1] = encodeRegister(seconds);
    data[2] = encodeRegister(minutes);
    if (hours > 19)
    {
        data[3] = ((0x2 << 4) | (hours % 20));
    }
    else
    {
        if (hours > 9)
        {
            data[3] = ((0x1 << 4) | (hours % 10));
        }
        else
        {
            data[3] = hours;
        }
    }
    data[4] = day;
    data[5] = encodeRegister(date);
    data[6] = encodeRegister(month);
    data[7] = encodeRegister(year);
    codeError = i2cDevice->fullWrite(addres, data, 8);
    if (codeError)
    {
        isInit = false;
        return;
    }

    readTime();
}

int FLProgI2CRTC::getTemperatureRaw(void)
{
    uint8_t data[2];
    codeError = i2cDevice->fullWrite(addres, 0x11);
    if (codeError)
    {
        isInit = false;
        return 0;
    }
    codeError = i2cDevice->fullRead(addres, data, 2);
    if (codeError)
    {
        isInit = false;
        return 0;
    }
    return ((int8_t)data[0] << 2) + (data[1] >> 6);
}

float FLProgI2CRTC::getTemperatureFloat(void)
{
    return (getTemperatureRaw() * 0.25f);
}

int FLProgI2CRTC::getTemperature(void)
{
    return (getTemperatureRaw() >> 2);
}

void FLProgI2CRTC::calculationTime()
{
    uint32_t currentTime = millis();
    uint32_t newSec = (flprog::difference32(startCalculationTime, (currentTime))) / 1000;
    if (!(newSec > 0))
    {
        return;
    }
    startCalculationTime = flprog::timeBack(currentTime - (newSec * 1000));
    for (uint32_t i = 0; i < newSec; i++)
    {
        addSecond();
    }
}

void FLProgI2CRTC::addSecond()
{
    if (now.second < 59)
    {
        now.second++;
        return;
    }
    now.second = 0;
    addMinute();
}

void FLProgI2CRTC::addMinute()
{
    if (now.minute < 59)
    {
        now.minute++;
        return;
    }
    now.minute = 0;
    addHour();
}

void FLProgI2CRTC::addHour()
{
    if (now.hour < 23)
    {
        now.hour++;
        return;
    }
    now.hour = 0;
    addData();
}

void FLProgI2CRTC::addData()
{
    uint8_t daysInMonth;
    if (now.month == 2)
    {
        daysInMonth = 28 + ((2000 + now.year) % 4 ? 0 : 1);
    }
    else
    {
        daysInMonth = 30 + ((now.month + (now.month > 7 ? 1 : 0)) % 2);
    }
    now.day++;
    if (now.day > 6)
    {
        now.day = 0;
    }
    if (now.date < (daysInMonth - 1))
    {
        now.date++;

        return;
    }
    now.date = 1;
    addMonth();
}

void FLProgI2CRTC::addMonth()
{
    if (now.month < 12)
    {
        now.month++;
        return;
    }
    now.month = 1;
    now.year++;
}
