//
// Created by thibault on 10/11/15.
//

#ifndef ONLYOS_RTC_H
#define ONLYOS_RTC_H

#include <stdint.h>
#include "arch/hal/timer/rtc.h"


void RTC_start();
void RTC_stop();
void RTC_clear();

#endif //ONLYOS_RTC_H
