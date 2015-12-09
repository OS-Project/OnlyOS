//
// Created by Thibault PIANA on 10/11/15.
//

#ifndef ONLYOS_KERNEL_H
#define ONLYOS_KERNEL_H
// Kernel macro
CONSOLE_WRITE(message) driver_uart_send(0, message)

// Compilation informations
char* _COMPILATION_TIME = __TIME__;
char* _COMPILATION_DATE = __DATE__;

// Functions
int kmain();

#endif //ONLYOS_KERNEL_H
