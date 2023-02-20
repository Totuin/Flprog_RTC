#include "flprog_RTC.h"
#include <LiquidCrystal_I2C.h>

FLProgI2C wireDevice(0);
FLProgDS1307 _RTC1(&wireDevice);

LiquidCrystal_I2C _lcd1(0x27, 16, 2);
String _RTC1_GetTime1_StrOut;
String _RTC1_GetTime2_StrOut;
int _dispTempLength1 = 0;
boolean _isNeedClearDisp1;
int _disp2oldLength = 0;
int _disp1oldLength = 0;
int _tempVariable_int;
bool _gen1O = 0;
unsigned long _gen1P = 0UL;
bool _count1I = 0;
int _count1_Value = 0;

void setup()
{
  wireDevice.begin();
  _lcd1.init();
  _lcd1.backlight();
}
void loop()
{
  _RTC1.pool();
  if (_isNeedClearDisp1)
  {
    _lcd1.clear();
    _isNeedClearDisp1 = 0;
  }
  // Плата:1

  if (flprog::isTimer (_gen1P , 2000))
  {
    _gen1P = millis();
    _gen1O = ! _gen1O;
  }


  if (_gen1O)
  {
    if (! _count1I)
    {
      _count1I = 1;
      _count1_Value = _count1_Value + 1;
    }
  }
  else
  {
    _count1I = 0;
  }
  if (_count1_Value >= 9)
  {
    _count1_Value = 0;
  }

  _RTC1.blinktime(_count1_Value);
  _RTC1_GetTime1_StrOut = _RTC1.gettime("d-m-Y M");
  if (!(0))
  {
    _dispTempLength1 = ((_RTC1_GetTime1_StrOut)).length();
    if (_disp1oldLength > _dispTempLength1)
    {
      _isNeedClearDisp1 = 1;
    }
    _disp1oldLength = _dispTempLength1;
    _lcd1.setCursor(int((16 - _dispTempLength1) / 2), 0);
    _lcd1.print((_RTC1_GetTime1_StrOut));
  }
  else
  {
    if (_disp1oldLength > 0)
    {
      _isNeedClearDisp1 = 1;
      _disp1oldLength = 0;
    }
  }

  _RTC1.blinktime(_count1_Value);
  _RTC1_GetTime2_StrOut = _RTC1.gettime("H:i:s D ");
  if (!(0))
  {
    _dispTempLength1 = ((_RTC1_GetTime2_StrOut)).length();
    if (_disp2oldLength > _dispTempLength1)
    {
      _isNeedClearDisp1 = 1;
    }
    _disp2oldLength = _dispTempLength1;
    _lcd1.setCursor(int((16 - _dispTempLength1) / 2), 1);
    _lcd1.print((_RTC1_GetTime2_StrOut));
  }
  else
  {
    if (_disp2oldLength > 0)
    {
      _isNeedClearDisp1 = 1;
      _disp2oldLength = 0;
    }
  }
}