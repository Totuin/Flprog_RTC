
#include "flprogrSystemRTC.h"

FLProgSystemRTC::FLProgSystemRTC(int16_t gmt)
{
  RT_HW_Base.unixID.zone = gmt;
}

void FLProgSystemRTC::pool()
{
  RT_HW_Base.unixUpdateTime();
}

void FLProgSystemRTC::privateSetTotal()
{
  RT_HW_Base.unixSetTotal();
}

void FLProgSystemRTC::privateSetUNIX()
{
  RT_HW_Base.unixSetTimeUNIX();
}
