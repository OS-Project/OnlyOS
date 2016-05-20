//
// Created by Thibault on 09/01/2016.
//

#include <kernel/kernel.h>
#include <kernel/drivers/drivers.h>
#include <kernel/config.h>

/* Libs */
#include <utils/libbool.h>

#include DRIVER_UART_PATH

unsigned int dinit(bool console)
{
    dinit_uart();

    if(console)
        kprintf("[Driver] UART driver configured and initialized\n");

    return EXIT_SUCCESS;
}

unsigned int dinit_dmtimer() {
    return EXIT_SUCCESS;
}

unsigned int dinit_filesystem() {
    return EXIT_SUCCESS;
}

unsigned int dinit_rtc() {
    return EXIT_SUCCESS;
}

/* Init UART driver */
unsigned int dinit_uart() {
    UART_stdioInit();
    UART_putc('\n');
    UART_putc('\n');

    return EXIT_SUCCESS;
}

unsigned int dinit_gpio() {
    return EXIT_SUCCESS;
}

unsigned int dinit_wdt() {
    return EXIT_SUCCESS;
}
