//
// Created by Thibault PIANA on 12/12/15.
//

#include "drivers/uart/uart.h"


int main()
{
    char* test = "Ceci est un test";
    UART_writeStr(test, strlen(test));
    UART_newline();
    while(1);
    return 0;
}

