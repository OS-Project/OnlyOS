//
// Created by thibault on 10/11/15.
//

#include "drivers/timer/rtc.h"
#include "hal/timer/rtc.h"
#include "soc_AM335x.h"

#include "hal/beaglebone.h"

void RTC_init(char rtc_number)
{
    unsigned int adress = RTC_getPhysicalAdress(rtc_number);

    /* Performing the System Clock configuration for RTC. */
    RTCModuleClkConfig();

    /* Disabling Write Protection for RTC registers.*/
    RTCWriteProtectDisable(adress);

    /* Selecting Internal Clock source for RTC. */
    RTC32KClkSourceSelect(adress, RTC_INTERNAL_CLK_SRC_SELECT);

    /* Enabling RTC to receive the Clock inputs. */
    RTC32KClkClockControl(adress, RTC_32KCLK_ENABLE);
    RTCEnable(adress);

}
void RTC_start(char rtc_number)
{
    unsigned int adress = RTC_getPhysicalAdress(rtc_number);
    RTCRun(adress);
}

unsigned int RTC_getTime(char rtc_number)
{
    unsigned int adress = RTC_getPhysicalAdress(rtc_number);
    return RTCTimeGet(adress);
}

unsigned int RTC_getCalendar(char rtc_number)
{
    unsigned int adress = RTC_getPhysicalAdress(rtc_number);
    return RTCCalendarGet(adress);

}

void RTC_stop(char rtc_number)
{
    unsigned int adress = RTC_getPhysicalAdress(rtc_number);
    RTCStop(adress);
}

unsigned int RTC_getPhysicalAdress(char rtc_number) {
    unsigned int physical_adress;
    switch(rtc_number)
    {
        case 0:
            physical_adress = (unsigned int)SOC_RTC_0_REGS;
        default:
            physical_adress = 0;
            break;
    }
    return physical_adress;
}

