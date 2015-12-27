//
// Created by Thibault PIANA on 12/12/15.
//

#include "drivers/uart/uart.h"
#include <stdio.h>

int main()
{
    UART_writeStr("Ceci est un test de la fonction malloc\n", 39);

    printf("Salut les copains");
    while(1);
    return 0;
}

