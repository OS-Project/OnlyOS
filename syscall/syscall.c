//
// Created by Thibault PIANA on 24/10/15.
//

/**
 * This file contain the rewrite of the POSIX interface
 */

#include "sys/stat.h"
#include "sys/types.h"

#include "drivers/uart/uart.h"

#define UART_DR(baseaddr) (*(unsigned int *)(baseaddr))
#define UART_FR(baseaddr) (*(((unsigned int *)(baseaddr))+6))

int _close(int file) { return -1; }

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) { return 1; }

int _lseek(int file, int ptr, int dir) { return 0; }

int _open(const char *name, int flags, int mode) { return -1; }

int _read(int file, char *ptr, int len) {
    return 0;
}

char *heap_end = 0;
caddr_t _sbrk(int incr) {
    extern char _sheap; /* Defined by the linker */
    extern char _eheap; /* Defined by the linker */
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_sheap;
    }
    prev_heap_end = heap_end;

    if (heap_end + incr > &_eheap) {
        /* Heap and stack collision */
        return (caddr_t)0;
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}

int _write(int file, char *ptr, int len) {
    UART_write(ptr);
    return len;
}