#pragma once

#include "Arduino.h"
#include "flprogUtilites.h"
//#include "base/flprog_RTC_base.h"

#ifdef _STM32_DEF_
#include "stm32/flprogSTM32RTC.h"
#else
#include "software/flprogAvrSoftRTC.h"
#endif

// #include "i2c/flprog_i2c_RTC.h"

// #include "ds1302/flprog_ds1302.h"
