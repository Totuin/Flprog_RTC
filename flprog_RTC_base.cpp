#include "flprog_RTC_base.h"

uint16_t FLProgRTCBase::getWeekDay(uint16_t y, uint8_t m, uint8_t d)
{
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += ds_dim(i - 1);
    if (m > 2 && y % 4 == 0)
        days++;
    return (days + 365 * y + (y + 3) / 4 + 4) % 7 + 1;
}

uint8_t FLProgRTCBase::ds_dim(uint8_t i)
{
    return (i < 7) ? ((i == 1) ? 28 : ((i & 1) ? 30 : 31)) : ((i & 1) ? 31 : 30);
}

void FLProgRTCBase::setTime(DateTime time)
{
    setTime(time.second, time.minute, time.hour, time.date, time.month, time.year, time.day);
}

uint32_t FLProgRTCBase::getUnix(int16_t gmt)
{
    if (abs(gmt) <= 12)
        gmt *= 60;
    int8_t my = (now.month >= 3) ? 1 : 0;
    uint16_t y = now.year + my - 1970;
    uint16_t dm = 0;
    for (int i = 0; i < now.month - 1; i++)
        dm += ds_dim(i);
    return (((now.date - 1 + dm + ((y + 1) / 4) - ((y + 69) / 100) + ((y + 369) / 100 / 4) + 365 * (y - my)) * 24ul + now.hour) * 60ul + now.minute - gmt) * 60ul + now.second;
}

void FLProgRTCBase::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year)
{
    uint8_t day = getWeekDay(year, month, date);
    setTime(seconds, minutes, hours, date, month, year, day);
}

char *FLProgRTCBase::gettime(String str)
{
    char result[str.length() + 1];
    str.toCharArray(result, str.length());
    result[str.length()] = 0;
    return gettime(result);
}

void FLProgRTCBase::setMemoryForString(const char *str)
{
    uint8_t charIndex, stringSize;
    bool f;
    stringSize = strlen(str) + 1;
    for (charIndex = 0; charIndex < strlen(str); charIndex++)
    {
        for (uint8_t k = 0; k < strlen(charInput); k++)
        {
            if (str[charIndex] == charInput[k])
            {
                if (k > 0)
                {
                    stringSize++;
                }
                if (k > 9)
                {
                    stringSize++;
                }
                if (k > 11)
                {
                    stringSize++;
                }
            }
        }
    }
    free(charReturn);
    charReturn = (char *)malloc(stringSize);
}

uint8_t FLProgRTCBase::checkChar(char val, uint8_t index)
{
    if (val == charInput[0] /*	w	*/)
    {
        funcFillChar(now.day, FLPROG_RTC_ONE_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_DAY_SYMBOL);
        return index + 1;
    }
    if (val == charInput[1] /*	a	*/)
    {
        funcFillChar(((now.hour < 12) ? 0 : 1) * 2, FLPROG_RTC_AM_PM_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_AM_PM_SYMBOL);
        return index + 2;
    }
    if (val == charInput[2] /*	A	*/)
    {
        funcFillChar((((now.hour < 12) ? 0 : 1) + 2) * 2, FLPROG_RTC_AM_PM_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_AM_PM_SYMBOL);
        return index += 2;
    }
    if (val == charInput[3] /*	d	*/)
    {
        funcFillChar(now.date, FLPROG_RTC_TWO_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_DATE_SYMBOL);
        return index + 2;
    }
    if (val == charInput[4] /*	h	*/)
    {
        funcFillChar(((now.hour % 12) ? (now.hour % 12) : 12), FLPROG_RTC_TWO_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_HOUR_SYMBOL);
        return index + 2;
    }
    if (val == charInput[5] /*	H	*/)
    {
        funcFillChar(now.hour, FLPROG_RTC_TWO_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_HOUR_SYMBOL);
        return index + 2;
    }
    if (val == charInput[6] /*	i	*/)
    {
        funcFillChar(now.minute, FLPROG_RTC_TWO_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_MINUTE_SYMBOL);
        return index + 2;
    }
    if (val == charInput[7] /*	m	*/)
    {
        funcFillChar(now.month, FLPROG_RTC_TWO_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_MONTH_SYMBOL);
        return index + 2;
    }
    if (val == charInput[8] /*	s	*/)
    {
        funcFillChar(now.second, FLPROG_RTC_TWO_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_SECOND_SYMBOL);
        return index + 2;
    }
    if (val == charInput[9] /*	y	*/)
    {
        funcFillChar((now.year), FLPROG_RTC_TWO_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_YEAR_SYMBOL);
        return index + 2;
    }
    if (val == charInput[10] /*	M	*/)
    {
        funcFillChar((now.month + 6) * 3, FLPROG_RTC_DAY_MONTH_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_MONTH_SYMBOL);
        return index + 3;
    }
    if (val == charInput[11] /*	D	*/)
    {
        funcFillChar(now.day * 3, FLPROG_RTC_DAY_MONTH_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_DAY_SYMBOL);
        return index + 3;
    }
    if (val == charInput[12] /*	Y	*/)
    {
        funcFillChar((now.year), FLPROG_RTC_FOUR_SYMBOL_TYPE, index, FLPROG_RTC_FLASH_YEAR_SYMBOL);
        return index + 4;
    }

    charReturn[index] = val;
    return index + 1;
}

void FLProgRTCBase::blinktime(uint8_t blinkRazrad, float blinkPeriod = 1)
{
    valBlink = blinkRazrad;
    valFrequency = uint32_t(1000 / blinkPeriod);
}

void FLProgRTCBase::funcFillChar(uint8_t value, uint8_t type, uint8_t position, uint8_t blinkVal)
{ //	(данные, тип данных, позиция для вставки, мигание)
    bool blink = valBlink == blinkVal;
    if ((millis() % valFrequency) < (valFrequency / 2))
    {
        blink = false;
    } //	Устанавливаем флаг мигания, если значение valBlink равно значению параметра k
    switch (type)
    {
    /* 1 знак	*/ case FLPROG_RTC_ONE_SYMBOL_TYPE:
        if (value > 6)
        {
            value = 6;
        }
        charReturn[position] = blink ? 32 : value + 48;
        break;
    /* 2 знака	*/ case FLPROG_RTC_TWO_SYMBOL_TYPE:
        if (value > 99)
        {
            value = 99;
        }
        charReturn[position] = blink ? 32 : value / 10 + 48;
        charReturn[position + 1] = blink ? 32 : value % 10 + 48;
        break;
    /* AM / PM	*/ case FLPROG_RTC_AM_PM_SYMBOL_TYPE:
        if (value > 6)
        {
            value = 6;
        }
        charReturn[position] = blink ? 32 : charMidday[value];
        charReturn[position + 1] = blink ? 32 : charMidday[value + 1];
        break;
    /* дн / мес	*/ case FLPROG_RTC_DAY_MONTH_SYMBOL_TYPE:
        if (value > 54)
        {
            value = 54;
        }
        charReturn[position] = blink ? 32 : charDayMon[value];
        charReturn[position + 1] = blink ? 32 : charDayMon[value + 1];
        charReturn[position + 2] = blink ? 32 : charDayMon[value + 2];
        break;
    /* 4 знака	*/ case FLPROG_RTC_FOUR_SYMBOL_TYPE:
        if (value > 99)
        {
            value = 99;
        }
        charReturn[position] = blink ? 32 : 2 + 48;
        charReturn[position + 1] = blink ? 32 : 0 + 48;
        charReturn[position + 2] = blink ? 32 : value / 10 + 48;
        charReturn[position + 3] = blink ? 32 : value % 10 + 48;
        break;
    }
}

char *FLProgRTCBase::gettime(const char *str)
{
    setMemoryForString(str);
    uint8_t newStringIndex = 0;
    newStringIndex = 0;
    for (uint8_t charIndex = 0; charIndex < strlen(str); charIndex++)
    {
        newStringIndex = checkChar(str[charIndex], newStringIndex);
    }
    charReturn[newStringIndex] = '\0';
    return charReturn;
}

