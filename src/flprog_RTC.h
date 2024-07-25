#pragma once

#include "Arduino.h"
#include "flprogUtilites.h"
#include "base/flprog_RTC_base.h"

#ifdef _STM32_DEF_
#define FLPROG_STM32_SYSTEM_RTC
#else
#define SOFTWARE_SYSTEM_RTC
#endif

#ifdef FLPROG_STM32_SYSTEM_RTC
#include "flprogSTM32RTC.h"
#endif

#ifdef SOFTWARE_SYSTEM_RTC
#include "software/flprogAvrSoftRTC.h"
#endif

// #include "i2c/flprog_i2c_RTC.h"

// #include "ds1302/flprog_ds1302.h"
