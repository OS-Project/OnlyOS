/*
* Created by Thibault on 09/01/2016.
*/

#ifndef ONLYOS_WATCHDOG_H
#define ONLYOS_WATCHDOG_H

#include "hal/timer/watchdog.h"
#include "soc_AM335x.h"

void WDT_enable(char wdt_number);
void WDT_disable(char wdt_number);
unsigned int WDT_getPhysicalAdress(char wdt_number);

#endif //ONLYOS_WATCHDOG_H
