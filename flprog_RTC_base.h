#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"

#define FLPROG_RTC_ONE_SYMBOL_TYPE 0
#define FLPROG_RTC_TWO_SYMBOL_TYPE 1
#define FLPROG_RTC_AM_PM_SYMBOL_TYPE 2
#define FLPROG_RTC_DAY_MONTH_SYMBOL_TYPE 3
#define FLPROG_RTC_FOUR_SYMBOL_TYPE 4

#define FLPROG_RTC_NO_FLASH_SYMBOL 0
#define FLPROG_RTC_FLASH_SECOND_SYMBOL 1
#define FLPROG_RTC_FLASH_MINUTE_SYMBOL 2
#define FLPROG_RTC_FLASH_HOUR_SYMBOL 3
#define FLPROG_RTC_FLASH_DATE_SYMBOL 4
#define FLPROG_RTC_FLASH_MONTH_SYMBOL 5
#define FLPROG_RTC_FLASH_YEAR_SYMBOL 6
#define FLPROG_RTC_FLASH_DAY_SYMBOL 7
#define FLPROG_RTC_FLASH_AM_PM_SYMBOL 8

struct DateTime
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
};

class FLProgRTCBase
{
public:
    uint8_t getError() { return codeError; };
    DateTime getTime() { return now; };

    uint8_t getSecond() { return now.second; };
    uint8_t getMinute() { return now.minute; };
    uint8_t getHour() { return now.hour; };
    uint8_t getDay() { return now.day; };
    uint8_t getDate() { return now.date; };
    uint8_t gertMonth() { return now.month; };
    uint16_t getYear() { return now.year; };
    void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year);
    virtual void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year, uint8_t day){};
    uint32_t getUnix(int16_t gmt); // получить unix время (указать свой часовой пояс в часах ИЛИ минутах)
    char *gettime(String);         //	Определяем функцию «дублёр» получения даты и времени из переменных	(строка с параметрами)
    char *gettime(const char *);   //	Объявляем функцию получения даты и времени ввиде строки				(строка с параметрами)
    void blinktime(uint8_t blinkRazrad, float blinkPeriod = 1);

protected:
    uint8_t ds_dim(uint8_t i);
    void setMemoryForString(const char *str);
    uint8_t checkChar(char val, uint8_t index);
    void funcFillChar(uint8_t value, uint8_t type, uint8_t position, uint8_t blinkVal); // Pаполнения строки вывода времени	(данные, тип данных, позиция для вставки, мигание)
    uint16_t getWeekDay(uint16_t y, uint8_t m, uint8_t d);
    void calculationTime();
    void addSecond();
    void addMinute();
    void addHour();
    void addData();
    void addMonth();

    DateTime now;
    uint8_t codeError = FLPROG_SENSOR_NOT_ERROR;
    char *charReturn = (char *)malloc(1);                                                 //	Определяем указатель на символьную область памяти в 1 байт			(указатель будет ссылаться на строку вывода времени)
    const char *charInput = "waAdhHimsyMDY";                                              //	Определяем константу-строку с символами требующими замены			(данные символы заменяются функцией gettime на значение времени)
    const char *charMidday = "ampmAMPM";                                                  //	Определяем константу-строку для вывода полудня						(am / pm / AM / PM)
    const char *charDayMon = "SunMonTueWedThuFriSatJanFebMarAprMayJunJulAugSepOctNovDec"; //	Определяем константу-строку для вывода дня недели или месяца		(Mon ... Sun / Jan ... Dec)
    uint32_t valFrequency = 1000;
    uint8_t valBlink = 0;
    uint32_t startCalculationTime = 0;
};
