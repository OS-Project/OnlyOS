/*
 * Created by Thibault PIANA on 10/11/15.
*/
#include <kernel/config.h>
#include <kernel/kernel.h>
#include <kernel/drivers/drivers.h>

#include <drivers/uart/uart.h>

/* libs */
#include <utils/libbool.h>

int kmain()
{
    kinit();
    UART_printf("Test 1\n");
    UART_printf("Test nombre : %d\n", 5);
    UART_printf("Test 2 nombres : %d et %d\n", 1, 2);
    UART_printf("Test caractere : %c, nombre : %d, chaine : %s", 'a', 5222, "Salut moi cest jean yves");

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
