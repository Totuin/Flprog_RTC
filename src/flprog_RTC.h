#pragma once
#include "Arduino.h"

#ifdef _STM32_DEF_
#define STM32_SYSTEM_RTC
#else
#define SOFTWARE_SYSTEM_RTC
#endif

#include "flprogUtilites.h"
#include "base/flprog_RTC_base.h"

#if defined(STM32_SYSTEM_RTC)
#include "flprogSTM32RTC.h"
#endif

#if defined(SOFTWARE_SYSTEM_RTC)
#include "software/flprogAvrSoftRTC.h"
#endif

#include "i2c/flprog_i2c_RTC.h"

#include "ds1302/flprog_ds1302.h"
