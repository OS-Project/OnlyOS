//
// Created by Thibault on 09/01/2016.
//

#include "kernel/drivers/drivers.h"

int dinit_dmtimer(SYSTEM * system_) {
    return 1;
}

int dinit_filesystem(SYSTEM * system_) {
    return 1;
}

int dinit_rtc(SYSTEM * system_) {
    //RTC_init(0);
    //RTC_start(0);
    return 1;
}

int dinit_uart(SYSTEM * system_) {
    return 1;
}

int dinit_gpio(SYSTEM * system_) {
    return 1;
}

int dinit_wdt(SYSTEM * system_) {
    /*if(system_->SYSTEM_WDT) {
        WDT_enable(0);
    }
    else {
        WDT_disable(0);
    }*/
    return 1;
}
