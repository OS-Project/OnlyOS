//
// Created by Thibault PIANA on 10/11/15.
//
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ONLYOS_KERNEL_H
#define ONLYOS_KERNEL_H

    #include "files_references.h"

    #include DRIVER_UART_PATH
    #include DRIVER_TIMER_PATH

    // Kernel macro
    CONSOLE_WRITE(message) UART_writeStr(message);

    typedef struct SYSTEM SYSTEM;
    struct SYSTEM {
        // Compilation informations
        char* _COMPILATION_TIME;
        char* _COMPILATION_DATE;

        char SYSTEM_TIMER;
        char SYSTEM_UART;
    };

#endif //ONLYOS_KERNEL_H

#ifdef __cplusplus
}
#endif