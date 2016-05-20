/*
 * Created by Thibault PIANA on 10/11/15.
*/
#include <kernel/config.h>
#include <kernel/kernel.h>
#include <kernel/drivers/drivers.h>

#include <drivers/uart/uart.h>

/* Libs */
#include <utils/libbool.h>

int kmain()
{
    kinit();

    while(1);
    return EXIT_SUCCESS;
}

int kinit()
{
    dinit(true);
    kprintf("[Init] ### Drivers initialisation done\n");
    kprintf("[INIT] ### Start memory initilisation\n");
    return EXIT_SUCCESS;
}

void kexit(int err_num)
{
    if (err_num) kprintf("Kernel exited with error\n");
    else kprintf("Kernel exited without error\n");
    while(1);
}
