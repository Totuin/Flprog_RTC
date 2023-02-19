#include "flprog_RTC.h"

FLProgI2CRTC::FLProgI2CRTC(FLProgI2C *device, uint8_t addr)
{
    i2cDevice = device;
    addres = addr;
}

void FLProgI2CRTC::pool()
{
    if ((startTime == 0) || (flprog::isTimer(startTime, 250)))
    {
        startTime = millis();
        readTime();
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

void FLProgI2CRTC::readTime()
{
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
    now.year = unpackRegister(data[6]) + 2000;
}

void FLProgI2CRTC::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year, uint8_t day)
{
    month = constrain(month, 1, 12);
    date = constrain(date, 0, ds_dim(month - 1));
    seconds = constrain(seconds, 0, 59);
    minutes = constrain(minutes, 0, 59);
    hours = constrain(hours, 0, 23);
    year -= 2000;
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