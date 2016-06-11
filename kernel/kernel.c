/*
 * Created by Thibault PIANA on 10/11/15.
*/
#include <kernel/config.h>
#include <kernel/kernel.h>

#include <kernel/drivers/drivers.h>
#include <drivers/uart/uart.h>

/* Memory management */
#include <kernel/memory/memory.h>
#include <kernel/memory/kmalloc.h>

/* Libs */
#include <utils/libbool.h>

/* Interrupts */
#include <kernel/interrupt/interrupt.h>

int kmain()
{
   	kinit();
	INT_SVC_call(0,1,2,3);
    	while(1);
    	return EXIT_SUCCESS;
}


int kinit()
{
    dinit(true);
    kprintf("[INIT] ### Drivers initialisation done\n");
    kprintf("[INIT] ### Start memory initilisation\n");
    return EXIT_SUCCESS;
}


void kexit(int err_num)
{
	switch (err_num)
	{
		case EXIT_SUCCESS:
			kprintf("Kernel exited without error\n");
			break;

		case 11:
			kprintf("Undefined instruction exception happened but it is not implemented\n");
			break;

		case 33:
			kprintf("Prefetch bort exception happened but it is not implemented\n");
			break;

		case 44:
			kprintf("Data abort exception happened but it is not implemented\n");
			break;

		case 77:
			kprintf("FIQ happened but it is not implemented\n");
			break;

		default:
			kprintf("Kernel exited with error : %d\n", err_num);
	}
	while(1);
}
