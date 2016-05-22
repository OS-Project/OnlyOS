#include "kernel/interrupt.h"

void INT_SVC_handler(int r0, int r1, int r2, int r3)
{
    #ifdef DEBUG
        kprintf("SVC interrupt detected\n");
	kprintf("SVC arguments: r0=%x, r1=%x, r2=%x, r3=%x\n", r0, r1, r2, r3);
    #endif
	switch (r0)
	{
		default:
			kprintf("Unknown SVC call\n");
			break;
	}
}

void INT_SVC_call(int r0, int r1, int r2, int r3)
{
	svc_asm_call(r0, r1, r2, r3);
}


