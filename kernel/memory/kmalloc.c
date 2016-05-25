//
// Created by Thibault PIANA on 23/05/16.
//
#include <kernel/memory/kmalloc.h>
#include <kernel/memory/memory.h>

#include <kernel/config.h>
#include <kernel/kernel.h>
/* Console */
#include DRIVER_UART_PATH

/* Libs */
#include <utils/libbool.h>
#include <utils/libtypes.h>

caddr_t kmalloc(unsigned int size)
{
    #ifdef DEBUG
        kprintf("[Function : kmalloc]\n");
    #endif
    return (caddr_t)(ksbrk(size, kget_memory()));
}

MEMORY * kget_memory()
{
    #ifdef DEBUG
        kprintf("[Function : kget_memory]\n");
    #endif
    return mget_memory((unsigned  int)&HEAP_START);
}

void memory_tests()
{
    #ifdef DEBUG
        static int ui = 5; // DATA test
        static int ui_unitialized; // BSS test

        extern char _stext, _etext, _srodata, _erodata, _sdata, _edata, _sbss, _ebss, _sheap, _eheap, _sstack, _estack;
        kprintf("The TEXT block : 0x%p - 0x%p\n", &_stext, &_etext);
        kprintf("The RO_DATA block : 0x%p - 0x%p\n", &_srodata, & _erodata);
        kprintf("The DATA block : 0x%p - 0x%p\n", &_sdata, &_edata);
        kprintf("The BSS block : 0x%p - 0x%p\n", &_sbss, &_ebss);
        kprintf("The HEAP block : 0x%p - 0x%p\n", &_sheap, &_eheap);
        kprintf("The STACK block : 0x%p - 0x%p\n", &_sstack, &_estack);

        kprintf("\n\n[TESTS] ### Begin STACK tests\n\n");

        kprintf("DATA test : ui variable : 0x%p\n", &ui);
        kprintf("BSS test : ui_unitialized variable : 0x%p\n\n", &ui_unitialized);
        int i,j,k,l;
        char m,n,o,p;

        kprintf("i : 0x%p, ", &i);
        kprintf("m : 0x%p, ", &m);
        kprintf("j : 0x%p, ", &j);
        kprintf("n : 0x%p, ", &n);
        kprintf("k : 0x%p, ", &k);
        kprintf("l : 0x%p, ", &l);
        kprintf("o : 0x%p, ", &o);
        kprintf("p : 0x%p\n\n", &p);

        kprintf("[TESTS] MALLOC tests\n\n");

        int * array = kmalloc(sizeof(int) * 3);
        array[0] = 2; array[1] = 5225; array[2] = 454455;

        kprintf("array[0] : %d. Adresse : 0x%p\n", array[0], &array[0]);
        kprintf("array[1] : %d. Adresse : 0x%p\n", array[1], &array[1]);
        kprintf("array[2] : %d. Adresse : 0x%p\n", array[2], &array[2]);

        mmemory_show(kget_memory());
        kprintf("\n\n");

        char * array2 = kmalloc(sizeof(int) * 5);
        array[0] = 's'; array[1] = 'a'; array[2] = 'l';

        kprintf("array2[0] : %c. Adresse : 0x%p\n", array2[0], &array2[0]);
        kprintf("array2[1] : %c. Adresse : 0x%p\n", array2[1], &array2[1]);
        kprintf("array2[2] : %c. Adresse : 0x%p\n", array2[2], &array2[2]);

        mmemory_show(kget_memory());
    #endif
}