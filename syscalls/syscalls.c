//
// Created by Thibault PIANA on 24/10/15.
//

/**
 * This file contain the rewrite of the POSIX interface
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <stddef.h>

#include "drivers/uart/uart.h"


int _close(int file) {
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _open(const char *name, int flags, int mode) {
    return -1;
}

/* I/O management */
int _read(int file, char *ptr, int len) {
    return UART_read(ptr, len);
}

int _write(int file, char *ptr, int len) {
    return UART_write(ptr, len);
}

/* Memory management */

char *heap_end = NULL;
caddr_t _sbrk(int incr) {
    extern char heap_low; /* Defined by the linker */
    extern char heap_top; /* Defined by the linker */
    char *prev_heap_end;

    if (heap_end == 0 || heap_end < &heap_low)
        heap_end = &heap_low;

    prev_heap_end = heap_end;

    /* Heap and stack collision */
    if (heap_end + incr > &heap_top)
        return (caddr_t) 0;

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}