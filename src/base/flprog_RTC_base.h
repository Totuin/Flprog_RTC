#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"

class FLProgRTCBase : public AbstractFLProgClass
{
public:
  RT_HW_STRUCT_UNIX_ID *getTime() { return now(); };
  uint8_t getSecond() { return now()->seconds; };
  uint8_t getMinute() { return now()->minutes; };
  uint8_t getHour() { return now()->hours; };
  uint8_t getDay() { return now()->weekDay; };
  uint8_t getDate() { return now()->day; };
  uint8_t getMonth() { return now()->month; };
  uint16_t getYear() { return (now()->year); };
  uint32_t getUnix() { return now()->timeUNIX; };
  int16_t getGmt() { return now()->zone; };

  void setNewTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint16_t year);
 
  void setGmt(int16_t gmt);
  void setUnix(uint32_t unixTime);
  void setSecond(uint8_t second);
  void setMinute(uint8_t minute);
  void setHour(uint8_t hour);
  void setDate(uint8_t date);
  void settMonth(uint8_t month);
  void setYear(uint16_t year);

  virtual void pool() {};
  virtual RT_HW_STRUCT_UNIX_ID *now() { return 0; };

protected:
  virtual void privateSetTotal() {};
  virtual void privateSetUNIX() {};
};
