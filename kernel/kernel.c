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


int kMain()
{
    init_kernel();
    kprintf("Kernel initialisation done\n");
    return 0;
}

void kInit()
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
void kInit_driver()
{
    dInit_timer();
    dInit_rtc(_COMPILATION_TIME, _COMPILATION_DATE);
    dInit_uart();
}

/**
 * Initialise devices list
 * Initialise devices
 */
void kInit_devices()
{

}

void kprintf(char* message)
{
    // Print on UART
    CONSOLE_WRITE(message);
}

