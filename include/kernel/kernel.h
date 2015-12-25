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

    // Kernel macro
    CONSOLE_WRITE(message) UART_writeLn(message);

    // Compilation informations
    char* _COMPILATION_TIME = __TIME__;
    char* _COMPILATION_DATE = __DATE__;

#endif //ONLYOS_KERNEL_H

#ifdef __cplusplus
}
#endif