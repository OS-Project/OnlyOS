//
// Created by Thibault on 09/01/2016.
//

#include "kernel/drivers/drivers.h"

bool dinit_dmtimer(SYSTEM * system_) {
    TIMER_set(0, system_->SYSTEM_DMTIMER);
    TIMER_start(system_->SYSTEM_DMTIMER);
    return true;
}

bool dinit_filesystem(SYSTEM * system_) {
    return true;
}

bool dinit_rtc(SYSTEM * system_) {
    return true;
}

bool dinit_uart(SYSTEM * system_) {
    return true;
}

bool dinit_gpio(SYSTEM * system_) {
    return true;
}

bool dinit_wdt(SYSTEM * system_) {
    if(system_->SYSTEM_WDT) {
        WDT_enable(0);
        WDT_enable(1);
    }
    else {
        WDT_disable(0);
        WDT_disable(1);
    }
    return true;
}