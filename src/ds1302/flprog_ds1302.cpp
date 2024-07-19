#include "flprog_ds1302.h"
/*
FLProgDS1302::FLProgDS1302(uint8_t res, uint8_t clk, uint8_t dat)
{
    pinRES = res;
    pinCLK = clk;
    pinDAT = dat;
}

void FLProgDS1302::pool()
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

void FLProgDS1302::readTime()
{
    if (!isInit)
    {
        initDevice();
    }

    beginTransmission(0xBE | 0x01);

    now.second = BcdToUint8(read() & 0x7F);
    now.minute = BcdToUint8(read());
    now.hour = BcdToBin24Hour(read());
    now.date = BcdToUint8(read());
    now.month = BcdToUint8(read());
    now.day = BcdToUint8(read()) - 1; // throwing away day of week as we calculate it
    now.year = BcdToUint8(read());
    read(); // throwing away write protect flag

    endTransmission();
    startCalculationTime = millis();
    startReadTime = millis();
}

void FLProgDS1302::initDevice()
{
    pinMode(pinCLK, INPUT);
    pinMode(pinDAT, INPUT);
    pinMode(pinRES, INPUT);
    isInit = true;
}

void FLProgDS1302::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
    beginTransmission(0xBE);
    write(Uint8ToBcd(seconds));
    write(Uint8ToBcd(minutes));
    write(Uint8ToBcd(hours)); // 24 hour mode only
    write(Uint8ToBcd(date));
    write(Uint8ToBcd(month));
    write(Uint8ToBcd(day + 1));
    write(Uint8ToBcd(year));
    write(0); // no write protect, as all of this is ignored if it is protected
    endTransmission();
    readTime();
}

void FLProgDS1302::beginTransmission(uint8_t command)
{
    digitalWrite(pinRES, LOW); // default, not enabled
    pinMode(pinRES, OUTPUT);
    digitalWrite(pinCLK, LOW); // default, clock low
    pinMode(pinCLK, OUTPUT);
    pinMode(pinDAT, OUTPUT);
    digitalWrite(pinRES, HIGH); // start the session
    delayMicroseconds(4);       // tCC = 4us
    write(command, (command & 0x01) == 0x01);
}

void FLProgDS1302::endTransmission()
{
    digitalWrite(pinDAT, LOW);
    delayMicroseconds(4); // tCWH = 4us
}

void FLProgDS1302::write(uint8_t value, bool isDataRequestCommand = false)
{
    for (uint8_t bit = 0; bit < 8; bit++)
    {
        digitalWrite(pinDAT, value & 0x01);
        delayMicroseconds(1); // tDC = 200ns
        // clock up, data is read by DS1302
        digitalWrite(pinCLK, HIGH);
        delayMicroseconds(1); // tCH = 1000ns, tCDH = 800ns
        // for the last bit before a read
        // Set IO line for input before the clock down
        if (bit == 7 && isDataRequestCommand)
        {
            pinMode(pinDAT, INPUT);
        }
        digitalWrite(pinCLK, LOW);
        delayMicroseconds(1); // tCL=1000ns, tCDD=800ns
        value >>= 1;
    }
}

uint8_t FLProgDS1302::read()
{
    uint8_t value = 0;

    for (uint8_t bit = 0; bit < 8; bit++)
    {
        // first bit is present on io pin, so only clock the other
        // bits
        value |= (digitalRead(pinDAT) << bit);

        // Clock up, prepare for next
        digitalWrite(pinCLK, HIGH);
        delayMicroseconds(1);

        // Clock down, value is ready after some time.
        digitalWrite(pinCLK, LOW);
        delayMicroseconds(1); // tCL=1000ns, tCDD=800ns
    }

    return value;
}

uint8_t FLProgDS1302::BcdToBin24Hour(uint8_t bcdHour)
{
    uint8_t hour;
    if (bcdHour & 0x40)
    {
        // 12 hour mode, convert to 24
        bool isPm = ((bcdHour & 0x20) != 0);

        hour = BcdToUint8(bcdHour & 0x1f);
        if (isPm)
        {
            hour += 12;
        }
    }
    else
    {
        hour = BcdToUint8(bcdHour);
    }
    return hour;
}

*/