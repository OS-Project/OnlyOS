//
// Created by Thibault PIANA on 12/12/15.
//

#include "drivers/uart/uart.h"
#include <stdlib.h>
#include <stdio.h>

extern char heap_end; /* Defined in syscall.c */
int main()
{
    unsigned long i = 122;
    unsigned long * p = &i;
    printf("%lu", (unsigned long)p);
    /*
    char c;
    char *ptr = NULL;
    size_t alloc_size = 1;
    do {
        c =getchar();
        printf("%d: %c\n", c, c);

        ptr = realloc(ptr, alloc_size);
        if(ptr == NULL) {
            puts("Out of memory!\nProgram halting.");
            for(;;);
        } else {
            printf("new alloc of %d bytes at address 0x%X\n", alloc_size, (unsigned int)ptr);
            alloc_size <<= 1;
            printf("Heap end = 0x%X\n", (unsigned int)heap_end);
        }
    }

    */
    while (1);
    return 0;
}

