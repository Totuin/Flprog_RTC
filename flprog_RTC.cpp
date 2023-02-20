#include "flprog_RTC.h"

void FLProgI2CRTC::pool()
{
    if ((startReadTime == 0) || (flprog::isTimer(startReadTime, reqestPeriod)))
    {
        readTime();
    }
    else
    {
        calculationTime();
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
    if (!i2cDevice->findAddr(addres))
    {
        codeError = FLPROG_SENSOR_DEVICE_NOT_FOUND_ERROR;
        return;
    }
    setInitData();
    if (codeError)
    {
        return;
    }
    isInit = true;
    readTime();
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
    startCalculationTime = millis();
    startReadTime = startCalculationTime;
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

//---------------DS1307-----------------
FLProgDS1307::FLProgDS1307(FLProgI2C *device, uint8_t addr)
{
    i2cDevice = device;
    addres = addr;
}

void FLProgDS1307::setInitData()
{
    uint8_t varI = i2cDevice->fullReadReg(addres, 0x00);
    codeError = i2cDevice->getErrorCode();
    if (codeError)
    {
        isInit = false;
        return;
    }
    if (varI & 0b10000000)
    {
        codeError = i2cDevice->fullWriteReg(addres, 0x00, (varI & ~0b10000000));
        if (codeError)
        {
            isInit = false;
            return;
        }
    } //(если установлен 7 бит в 0 регистре, то сбрасываем его - запускаем генератор)
    varI = i2cDevice->fullReadReg(addres, 0x02);
    codeError = i2cDevice->getErrorCode();
    if (codeError)
    {
        isInit = false;
        return;
    }
    if (varI & 0b01000000)
    {
        codeError = i2cDevice->fullWriteReg(addres, 0x02, (varI & ~0b01000000));
        if (codeError)
        {
            isInit = false;
            return;
        }
    } //(если установлен 6 бит в 2 регистре, то сбрасываем его - переводим модуль в 24 часовой режим)
    varI = i2cDevice->fullReadReg(addres, 0x07);
    codeError = i2cDevice->getErrorCode();
    if (codeError)
    {
        isInit = false;
        return;
    }
    if ((varI & 0b00000011) || !(varI & 0b00010000))
    {
        codeError = i2cDevice->fullWriteReg(addres, 0x07, ((varI & ~0b00000011) | 0b00010000));
        if (codeError)
        {
            isInit = false;
            return;
        }
    } //(если установлены 1 и 0 биты или сброшен 4 бит в 7 регистре, то сбрасываем 1 с 0 битами, а 4 устанавливаем - выводим меандр с частотой 1 Гц на выводе SQW/OUT модуля)
}

//---------------DS3231-----------------
FLProgDS3231::FLProgDS3231(FLProgI2C *device, uint8_t addr)
{
    i2cDevice = device;
    addres = addr;
}

void FLProgDS3231::setInitData()
{
    uint8_t varI = i2cDevice->fullReadReg(addres, 0x02);
    codeError = i2cDevice->getErrorCode();
    if (codeError)
    {
        isInit = false;
        return;
    }
    if (varI & 0b01000000)
    {

        codeError = i2cDevice->fullWriteReg(addres, 0x02, (varI & ~0b01000000));
        if (codeError)
        {
            isInit = false;
            return;
        }
    } //(если установлен 6 бит в 2 регистре, то сбрасываем его - переводим модуль в 24 часовой режим)
    varI = i2cDevice->fullReadReg(addres, 0x0E);
    codeError = i2cDevice->getErrorCode();
    if (codeError)
    {
        isInit = false;
        return;
    }
    if (varI & 0b11011111)
    {
        codeError = i2cDevice->fullWriteReg(addres, 0x0E, (varI & ~0b11011111));
        if (codeError)
        {
            isInit = false;
            return;
        }
    } //(если установлены 7,6,4,3,2,1 и 0 биты в 14 регистре, то сбрасываем их - разрешаем генератору работать от батарейки, запрещаем выводу SQW работать от батарейки, выводим меандр с частотой 1Гц на вывод SQW, переводим вывод INT/SQW в режим SQW, запрещаем прерывания будильников)
    varI = i2cDevice->fullReadReg(addres, 0x0F);
    codeError = i2cDevice->getErrorCode();
    if (codeError)
    {
        isInit = false;
        return;
    }
    if ((varI & 0b10000011) || !(varI & 0b00001000))
    {
        codeError = i2cDevice->fullWriteReg(addres, 0x0F, ((varI & ~0b10000011) | 0b00001000));
        if (codeError)
        {
            isInit = false;
            return;
        }
    } //(если установлены 7,1 и 0 биты или сброшен 3 бит в 15 регистре, то сбрасываем 7,1 и 0 биты, а 3 устанавливаем - сбрасываем флаг остановки генератора, разрешаем меандр с частотой 32768Гц на выводе 32kHz, сбрасываем флаги будильников)
}