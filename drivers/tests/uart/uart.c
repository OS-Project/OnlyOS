//
// Created by Thibault PIANA on 12/12/15.
//

#include "drivers/uart/uart.h"
#include <stdio.h>

int main()
{
    int age = 0;
    UART_writeStr("This is an UART test\n");
    printf("This is a printf test\n\n");

    printf("Ok, printf is done, please how old are you ? ");
    scanf("%d", &age);

    printf("\nOh, I see, your age is %d", age);

    while (1);
    return 0;
}

