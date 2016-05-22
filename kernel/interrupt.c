#include "kernel/interrupt.h"

void INT_SVC_handler()
{
    #ifdef DEBUG
        kprintf("\nSVC interrupt detected\n");
    #endif
}
