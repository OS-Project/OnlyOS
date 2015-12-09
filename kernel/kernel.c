//
// Created by Thibault PIANA on 10/11/15.
//

#include <string.h>
#include <inttypes.h>

#include "kernel.h"
#include "files_references.h"

// Drivers inclusion
#include DRIVER_TIMER_PATH
#include DRIVER_RTC_PATH

int kmain()
{
    init_kernel();
    kprintf("Kernel initialisation done\n");
    return 0;
}

void kinit()
{
    init_driver();
    kprintf("Driver initialisation done\n");
    init_devices();
    kprintf("Devices initialisation done\n");
}

/**
 * Initialise drivers list
 *  1. Launch timer
 *  2. Initialise RTC with compilation date
 *
 * Initialise drivers
 */
void kinit_driver()
{
    dmain();
    // Initialise the timer
    dinit_timer();

    dinit_filesystem();
    dinit_rtc(_COMPILATION_TIME, _COMPILATION_DATE);
    dinit_uart();
    dinit_gpio();
    dinit_spi();
}

/**
 * Initialise devices list
 * Initialise devices
 */
void kinit_devices()
{

}

void kprintf(char* message)
{
    CONSOLE_WRITE(message);
}

