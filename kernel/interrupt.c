#include "kernel/interrupt.h"

void INT_SVC_handler()
{
    #ifdef DEBUG
        kprintf("\nSVC interrupt detected\n");
    #endif
}

void INT_SVC_call(int r0, int r1, int r2, int r3)
{
	svc_asm_call(r0, r1, r2, r3);
}


