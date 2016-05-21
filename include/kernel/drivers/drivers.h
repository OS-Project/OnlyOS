//
// Created by Thibault on 09/01/2016.
//

#ifndef ONLYOS_KERNEL_DRIVERS_H
#define ONLYOS_KERNEL_DRIVERS_H
    #include <utils/libbool.h>

    unsigned int dinit(bool console);
    unsigned int dinit_dmtimer();

    unsigned int dinit_filesystem();
    unsigned int dinit_rtc();
    unsigned int dinit_uart();
    unsigned int dinit_gpio();
    unsigned int dinit_wdt();
#endif //ONLYOS_DRIVERS_H
