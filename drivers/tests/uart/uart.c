//
// Created by Thibault PIANA on 12/12/15.
//

#include "drivers/uart/uart.h"
#include <stdlib.h>
#include <stdio.h>

extern char *heap_end; /* Defined in syscall.c */
int main()
{
    int i;
    printf("This is a malloc test : \n");
    int *test = NULL;

    printf("Sizeof allocations : %d\n", sizeof(int) * 5000);
    printf("Test adress :%X\n", (unsigned int) test);

    for(i = 0; i < 1000; i++) {
        printf("### %d\n",i);
        printf("HEAP_END BEFORE : %X\n", (unsigned int) heap_end);
        test = malloc(sizeof(int) * 5000);
        printf("HEAP_END AFTER : %X\n", (unsigned int) heap_end);
        printf("Test adress : %X\n", (unsigned int) test);
    }

    while (1);
    return 0;
}

