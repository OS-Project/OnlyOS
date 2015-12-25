//
// Created by Thibault PIANA on 10/11/15.
//

#include "kernel.h"

int kmain()
{
    kinit();
    kprintf("Kernel initialisation done\n");
    return 0;
}

void kinit()
{
    kinit_drivers();
    kprintf("Driver initialisation done\n");
    kinit_devices();
    kprintf("Devices initialisation done\n");


    kinit_screen();
}

/**
 * Initialise drivers list
 *  1. Launch timer
 *  2. Initialise RTC with compilation date
 *
 * Initialise drivers
 */
void kinit_drivers()
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

void kinit_screen()
{
    kprintf("_______ __    _ ___    __   __ _______ _______");
    kprintf("|       |  |  | |   |  |  | |  |       |       |");
    kprintf("|   _   |   |_| |   |  |  |_|  |   _   |  _____|");
    kprintf("|  | |  |       |   |  |       |  | |  | |_____");
    kprintf("|  |_|  |  _    |   |__|_     _|  |_|  |_____  |");
    kprintf("|       | | |   |       ||   | |       |_____| |");
    kprintf("|_______|_|  |__|_______||___| |_______|_______|");
    kprintf("");
    kprintf("Developped by Thibault PIANA & Alan GARDIN");
    kprintf("");
    kprintf("");
}
