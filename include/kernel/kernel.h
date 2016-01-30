//
// Created by Thibault PIANA on 10/11/15.
//
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ONLYOS_KERNEL_H
#define ONLYOS_KERNEL_H

    #include <stdlib.h>
    #include <stdio.h>

    #include "kernel/config.h"
    #include DRIVER_UART_PATH

    typedef struct  {
        // Compilation informations
        char* _COMPILATION_TIME;
        char* _COMPILATION_DATE;

        char SYSTEM_DMTIMER;
        char SYSTEM_WDT;
        // Bus UART for std
        char SYSTEM_STDOUT;
        char SYSTEM_STDERR;
        char SYSTEM_STDIN;
    } SYSTEM;

    int kmain();
    void kinit();
    int kinit_drivers();
    int kinit_devices();

    void kinit_screen();
    int klaunch();
#endif //ONLYOS_KERNEL_H

#ifdef __cplusplus
}
#endif