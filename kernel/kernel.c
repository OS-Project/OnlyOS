//
// Created by Thibault PIANA on 10/11/15.
//

#include "kernel/kernel.h"
#include "kernel/user.h"

USER * user_;
SYSTEM * system_;

int kmain()
{
    kinit();
    kprintf("Kernel initialisation done\n");
    return 0;
}

void kinit()
{
    /* Initialisation du système */
    system_ = kmalloc(sizeof(SYSTEM));

    system_->_COMPILATION_TIME = __TIME__;
    system_->_COMPILATION_DATE = __DATE__;
    system_->SYSTEM_TIMER = 0;
    system_->SYSTEM_UART = 0;

    /* Initialisation de l'utilisateur */
    user_ = kmalloc(sizeof(USER));

    user_->current_path = "/";
    user_->name = "root";

    /* Initilisation des drivers */
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
    /*
    dmain();
    dinit_timer();

    dinit_filesystem();
    dinit_rtc(_COMPILATION_TIME, _COMPILATION_DATE);
    dinit_uart();
    dinit_gpio();
    dinit_spi();
    */
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
    kprintf("\n\n");
    kprintf("Developped by Thibault PIANA & Alan GARDIN");
    kprintf("");
    kprintf("");
}
