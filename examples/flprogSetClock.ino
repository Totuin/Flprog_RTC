#include "flprog_RTC.h"

FLProgI2C wireDevice(0);
FLProgI2CRTC rtc(&wireDevice);
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
  get3231Date();
}
void loop()
{
  rtc.pool();

  if (canResiveData) {
    if (Serial.available()) {
      inChar = (char)Serial.read();
      if (inChar == 1) {
        tempIndex = 0;
        hasData = 0;
      } else {
        if (inChar == 2) {
          inputString = "";
        } else {
          if (inChar == 3) {
            switch (tempIndex) {
              case 0: set3231Date(dataTime.second, dataTime.minute, (inputString.toInt()), dataTime.date, dataTime.month, dataTime.year, dataTime.day); break;
              case 1: set3231Date(dataTime.second, (inputString.toInt()), dataTime.hour, dataTime.date, dataTime.month, dataTime.year, dataTime.day); break;
              case 2: set3231Date((inputString.toInt()), dataTime.minute, dataTime.hour, dataTime.date, dataTime.month, dataTime.year, dataTime.day)    ; break;
              case 3: set3231Date(dataTime.second, dataTime.minute, dataTime.hour, (inputString.toInt()), dataTime.month, dataTime.year, dataTime.day);  break;
              case 4: set3231Date(dataTime.second, dataTime.minute, dataTime.hour, dataTime.date, (inputString.toInt()), dataTime.year, dataTime.day) ; break;
              case 5: set3231Date(dataTime.second, dataTime.minute, dataTime.hour, dataTime.date, dataTime.month, ((inputString.toInt())+2000), dataTime.day); break;
              case 6: set3231Date(dataTime.second, dataTime.minute, dataTime.hour, dataTime.date, dataTime.month, dataTime.year, (inputString.toInt())); break;
            }
            tempIndex++;
          } else {
            if (inChar == 4) {
              hasData = 1;
              canResiveData = 0;
            } else {
              inputString += inChar;
            }
          }
        }
      }
    }
  }



  if (1)
  {
    if (! _gen1I)
    {
      _gen1I = 1;
      _gen1O = 1;
      _gen1P = millis();
    }
  }
  else
  {
    _gen1I = 0 ;
    _gen1O = 0;
  }
  if (_gen1I )
  {
    if ( flprog::isTimer ( _gen1P , 250 ))
    {
      _gen1P = millis();
      _gen1O = ! _gen1O;
    }
  }
  if (_gen1O)
  {
    if (! _csb1)
    {
      get3231Date();
      Serial.write (1);
      Serial.write (2);
      Serial.print (dataTime.hour);
      Serial.write (3);
      Serial.write (2);
      Serial.print (dataTime.minute);
      Serial.write (3);
      Serial.write (2);
      Serial.print (dataTime.second);
      Serial.write (3);
      Serial.write (2);
      Serial.print (dataTime.date);
      Serial.write (3);
      Serial.write (2);
      Serial.print (dataTime.month);
      Serial.write (3);
      Serial.write (2);
      Serial.print (dataTime.day);
      Serial.write (3);
      Serial.write (2);
      Serial.print ((dataTime.year)-2000);
      Serial.write (3);
      Serial.write (4);
      _csb1 = 1;
    }
  } else {
    _csb1 = 0;
  }
  if (hasData) {
    canResiveData = 1;
    hasData = 0;
  }
}

void get3231Date()
{
  dataTime = rtc.getTime();
}


void set3231Date(byte sec, byte  minut, byte hou, byte dat, byte mo, byte ye, byte daW)
{
  rtc.setTime(sec, minut, hou,  dat, mo, ye,daW );
  get3231Date();
}


