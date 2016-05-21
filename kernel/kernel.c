/*
 * Created by Thibault PIANA on 10/11/15.
*/
#include <kernel/config.h>
#include <kernel/kernel.h>
#include <kernel/drivers/drivers.h>

#include <drivers/uart/uart.h>

/* Libs */
#include <utils/libbool.h>
#include "kernel/cp15.h"

int kmain()
{
    kinit();

    kprintf("[INIT] Move interrupt vector table");
    kinitVector_table();
    kprintf("[INIT] Interrupt vector table");

    __asm__("svc #0");

    while(1);
    return EXIT_SUCCESS;
}

void kinitVector_table()
{
    const unsigned int AM335X_VECTOR_BASE = 0x4030FC00;

    unsigned int const vecTbl[14]=
    {
            0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
            0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
            0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
            0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
            0xE59FF014,    /* Opcode for loading PC with the contents of [PC + 0x14] */
            0xE24FF008,    /* Opcode for loading PC with (PC - 8) (eq. to while(1)) */
            0xE59FF010,    /* Opcode for loading PC with the contents of [PC + 0x10] */
            0xE59FF010,    /* Opcode for loading PC with the contents of [PC + 0x10] */
            (unsigned int)kmain,
            (unsigned int)kexit,
            (unsigned int)kexit,
            (unsigned int)kexit,
            (unsigned int)kexit,
            (unsigned int)kexit
    };

    unsigned int *dest = (unsigned int *)AM335X_VECTOR_BASE;
    unsigned int *src =  (unsigned int *)vecTbl;
    unsigned int count;

    CP15VectorBaseAddrSet(AM335X_VECTOR_BASE);

    for(count = 0; count < sizeof(vecTbl)/sizeof(vecTbl[0]); count++)
        dest[count] = src[count];
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
    if (err_num) kprintf("Kernel exited with error\n");
    else kprintf("Kernel exited without error\n");
    while(1);
}
