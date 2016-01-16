/*
  * Created by Thibault on 09/01/2016.
*/

#include "drivers/timer/watchdog.h"

void WDT_enable(char wdt_number)
{
    unsigned int adress = WDT_getPhysicalAdress(wdt_number);
    WatchdogTimerEnable(adress);
}

void WDT_disable(char wdt_number)
{
    unsigned int adress = WDT_getPhysicalAdress(wdt_number);
    WatchdogTimerDisable(adress);
}

unsigned int WDT_getPhysicalAdress(char wdt_number)
{
    unsigned int physical_adress;
    switch (wdt_number) {
        case 0:
            physical_adress = SOC_WDT_0_REGS;
            break;
        case 1:
            physical_adress = SOC_WDT_1_REGS;
            break;
        default:
            physical_adress = 0;
            break;
    }

    return physical_adress;
}