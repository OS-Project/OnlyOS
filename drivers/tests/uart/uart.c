//
// Created by Thibault PIANA on 12/12/15.
//

#include "drivers/uart/uart.h"
#include <stdlib.h>

int main()
{
    int i;
    UART_writeLn("Ceci est un test de la fonction malloc");
    UART_writeLn("On va ajouter plusieurs espaces mémoires a la suite pour voir ce que ça fait");

    while(1);
    return 0;
}

