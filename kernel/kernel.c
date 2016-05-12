/*
 * Created by Thibault PIANA on 10/11/15.
*/

#include "kernel/kernel.h"
#include "kernel/config.h"
#include "kernel/drivers/drivers.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
extern int errno;

SYSTEM * system_;

#define kmalloc malloc /* Temporary */
#define kprintf printf

int kmain()
{
    kprintf("### Kernel initialisation\n");
    kinit();
    kprintf("### Kernel initialisation done\n");

    klaunch();
    
    kprintf("\nEnd of code, please restart\n");
    while(1);
    return 0;
}

void kinit()
{
    /* System initialization */
    system_ = kmalloc(sizeof(SYSTEM));

    system_->_COMPILATION_TIME = __TIME__;
    system_->_COMPILATION_DATE = __DATE__;

    system_->SYSTEM_DMTIMER = CONFIG_SYSTEM_DMTIMER;
    system_->SYSTEM_WDT = CONFIG_SYSTEM_WDT_STATUS;

    system_->SYSTEM_STDOUT = CONFIG_SYSTEM_STDOUT;
    system_->SYSTEM_STDERR = CONFIG_SYSTEM_STDERR;
    system_->SYSTEM_STDIN = CONFIG_SYSTEM_STDIN;

    /* Initialisation de l'utilisateur */
    /*user_ = kmalloc(sizeof(USER));

    user_->current_path = "/";
    user_->name = "root";
    */
    /* Initilisation des drivers */
    kprintf("[Init] ### Start drivers initialisation\n");
    kinit_drivers();
    kprintf("[Init] ### Drivers initialisation done\n");
    kprintf("[Init] ### Start devices initialisation\n");
    kinit_devices();
    kprintf("[Init] ### Devices initialisation done\n");

    kinit_screen();
}

/**
 * Initialise drivers list
 *  1. Launch timer
 *  2. Initialise RTC with compilation date
 *
 * Initialise drivers
 */
int kinit_drivers()
{
    int status = 1;
    kprintf("[Init] Initialization of timer\n");
    status &= dinit_dmtimer(system_);
    if(status)
        kprintf("[Init] DM timer ok\n");

    status &= dinit_rtc(system_);
    if(status)
        kprintf("[Init] RTC ok\n");

    status &= dinit_uart(system_);
    if(status)
        kprintf("[Init] UART ok\n");

    status &= dinit_gpio(system_);
    if(status)
        kprintf("[Init] GPIO ok\n");
    /*
    status &= dinit_wdt(system_);
    if(status)
        kprintf("[Init] Watchdog timer ok\n");
    */
    return status;
}

/**
 * Initialise devices list
 * Initialise devices
 */
int kinit_devices() {
    return 1;
}

void kinit_screen()
{
    kprintf("_______ __    _ ___    __   __ _______ _______\n");
    kprintf("|       |  |  | |   |  |  | |  |       |       |\n");
    kprintf("|   _   |   |_| |   |  |  |_|  |   _   |  _____|\n");
    kprintf("|  | |  |       |   |  |       |  | |  | |_____\n");
    kprintf("|  |_|  |  _    |   |__|_     _|  |_|  |_____  |\n");
    kprintf("|       | | |   |       ||   | |       |_____| |\n");
    kprintf("|_______|_|  |__|_______||___| |_______|_______|");
    kprintf("\n\n");
    kprintf("Developped by Thibault PIANA & Alan GARDIN\n\n");
}

void kexit(int err_num)
{
	if (err_num) kprintf("Kernel exited with error\n");
	else kprintf("Kernel exited without error\n");
	while(1);
}
