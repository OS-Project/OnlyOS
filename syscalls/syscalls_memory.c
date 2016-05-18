//
// Created by Thibault PIANA on 24/10/15.
//

/**
 * This file contain the rewrite of the POSIX interface
 */

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