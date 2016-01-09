/*
  * Created by Thibault on 09/01/2016.
*/

#include "drivers/timer/watchdog.h"
#include "hal/timer/watchdog.h"
#include "soc_AM335x"

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
    unsigned physical_adress;
    switch (wdt_number) {
        case 0:
            physical_adress = SOC_WDT_0_REGS;
            break;
        case 1:
            physical_adress = SOC_WDT_1_REGS;
            break;
        default:
            break;
    }

    return physical_adress;
}