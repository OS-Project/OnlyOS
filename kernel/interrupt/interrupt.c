#include "drivers/uart/uart.h"
#include "kernel/config.h"
#include "kernel/interrupt/interrupt.h"
#include <kernel/kernel.h>

/* Memory management */
#include <kernel/memory/memory.h>

void INT_SVC_handler(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3)
{
    #ifdef DEBUG
        kprintf("SVC interrupt detected\n");
		kprintf("SVC arguments: r0=%x, r1=%x, r2=%x, r3=%x\n", r0, r1, r2, r3);
    #endif

	switch (r0)
	{
		case 0:
			switch(r1)
			{
				case 0x0:
					kprintf("\nFatal Error : System aborted");
					kexit(0x00);
					break;
				default:
					kprintf("Error exception: error number unknown.\n");
					break;
			}

			break;

		case 0x00100:
			UART_putc((unsigned char)r1);
			break;

		case 0x00200:
			minit(r1, r2);
			break;

		case 0x00201:
			mmalloc(r1, mget_memory(r2));
			break;

		case 0x00202:
			mcalloc(r1, r2, mget_memory(r3));
			break;

		case 0x00204:
			mfree((void *)r1, mget_memory(r2));
			break;

		default:
			kprintf("Unknown SVC call\n");
			break;
	}
}

void INT_SVC_call(int r0, int r1, int r2, int r3)
{
	svc_asm_call(r0, r1, r2, r3);
}

void INT_IRQ_handler()
{
	#ifdef DEBUG_INTERRUPT
		kprintf("IRQ interrupt detected\n");
	#endif
	int * INTC_SIR_IRQ = (int *)(0x48200040);
	char activeIRQ = *(INTC_SIR_IRQ) & 0x7F;
	kprintf("IRQ number: %d\n", activeIRQ);


	switch (activeIRQ)
	{
		default:
			kprintf("Unknown IRQ identifier! \n");
	}
}

