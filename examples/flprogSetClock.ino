#include "flprog_RTC.h"

FLProgI2C wireDevice(0);
FLProgDS3231 rtc(&wireDevice);
DateTime dataTime;
bool _gen1I = 0;
bool _gen1O = 0;
unsigned long _gen1P = 0;
bool _csb1 = 0;
boolean hasData = 0;
boolean canResiveData = 1;
int tempIndex = 0;
char inChar;
String inputString;
void setup()
{
  wireDevice.begin();
  Serial.begin(9600);
  dataTime = rtc.getTime();
}
void loop()
{
  rtc.pool();

  if (canResiveData)
  {
    if (Serial.available())
    {
      inChar = (char)Serial.read();
      if (inChar == 1)
      {
        tempIndex = 0;
        hasData = 0;
      }
      else
      {
        if (inChar == 2)
        {
          inputString = "";
        }
        else
        {
          if (inChar == 3)
          {
            switch (tempIndex)
            {
            case 0:
              dataTime.hour = inputString.toInt();
              break;
            case 1:
              dataTime.minute = inputString.toInt();
              break;
            case 2:
              dataTime.second = inputString.toInt();
              break;
            case 3:
              dataTime.date = inputString.toInt();
              break;
            case 4:
              dataTime.month = inputString.toInt();
              break;
            case 5:
              dataTime.year = inputString.toInt();
              break;
            case 6:
              dataTime.day = inputString.toInt();
              break;
            }
            tempIndex++;
          }
          else
          {
            if (inChar == 4)
            {
              hasData = 1;
              canResiveData = 0;
              rtc.setTime(dataTime.second, dataTime.minute, dataTime.hour, dataTime.date, dataTime.month, dataTime.year, dataTime.day);
            }
            else
            {
              inputString += inChar;
            }
          }
        }
      }
    }
  }

  if (1)
  {
    if (!_gen1I)
    {
      _gen1I = 1;
      _gen1O = 1;
      _gen1P = millis();
    }
  }
  else
  {
    _gen1I = 0;
    _gen1O = 0;
  }
  if (_gen1I)
  {
    if (flprog::isTimer(_gen1P, 500))
    {
      _gen1P = millis();
      _gen1O = !_gen1O;
    }
  }
  if (_gen1O)
  {
    if (!_csb1)
    {
      Serial.write(1);
      Serial.write(2);
      Serial.print(rtc.getHour());
      Serial.write(3);
      Serial.write(2);
      Serial.print(rtc.getMinute());
      Serial.write(3);
      Serial.write(2);
      Serial.print(rtc.getSecond());
      Serial.write(3);
      Serial.write(2);
      Serial.print(rtc.getDate());
      Serial.write(3);
      Serial.write(2);
      Serial.print(rtc.gertMonth());
      Serial.write(3);
      Serial.write(2);
      Serial.print(rtc.getDay());
      Serial.write(3);
      Serial.write(2);
      Serial.print(rtc.getYear());
      Serial.write(3);
      Serial.write(4);
      _csb1 = 1;
    }
  }
  else
  {
    _csb1 = 0;
  }
  if (hasData)
  {
    canResiveData = 1;
    hasData = 0;
  }
}
