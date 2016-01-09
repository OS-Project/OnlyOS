//
// Created by Thibault on 09/01/2016.
//

#ifndef ONLYOS_KERNEL_DRIVERS_H
#define ONLYOS_KERNEL_DRIVERS_H

    #include "kernel/kernel.h"
    #include "kernel/config.h"

    #include DRIVER_UART_PATH
    #include DRIVER_DMTIMER_PATH
    #include DRIVER_WDT_PATH

    bool dinit_dmtimer(SYSTEM * system_);

    bool dinit_filesystem(SYSTEM * system_);
    bool dinit_rtc(SYSTEM * system_);
    bool dinit_uart(SYSTEM * system_);
    bool dinit_gpio(SYSTEM * system_);
    bool dinit_wdt(SYSTEM * system_);

#endif //ONLYOS_DRIVERS_H
