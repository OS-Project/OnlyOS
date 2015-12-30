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

    printf("Size of char : %d\n", sizeof(char));
    printf("Size of short : %d\n", sizeof(short));
    printf("Size of int : %d\n", sizeof(int));
    printf("Size of unsigned int : %d\n", sizeof(unsigned int));
    printf("Size of long : %d\n", sizeof(long));
    printf("Size of long long : %d\n\n", sizeof(long long));
    printf("Ok, printf is done, please how old are you ? ");

    scanf("%d", &age);

    printf("\nOh, I see, your age is %d", age);

    while (1);
    return 0;
}

