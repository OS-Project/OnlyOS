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
    kprintf("B SVC\n");
	INT_SVC_call(0,1,2,3);
    kprintf("%d\n", EXIT_SUCCESS);
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
		case 7:
			kprintf("FIQ happened but it is not implemented\n");
		default:
			kprintf("Kernel exited with error : %d\n", err_num);
	}
	while(1);
}
