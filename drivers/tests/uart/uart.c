//
// Created by Thibault PIANA on 12/12/15.
//

#include "drivers/uart/uart.h"

int main()
{
    UART_writeStr("Je suis le vent du nord !!!!", 28);
    UART_newline();
    UART_writeStr("J'aime les pommesssss !!!", 25);
    UART_newline();

    return 0;
}

