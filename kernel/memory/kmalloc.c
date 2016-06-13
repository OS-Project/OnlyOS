//
// Created by Thibault PIANA on 23/05/16.
//
#include <kernel/memory/kmalloc.h>
#include <kernel/memory/memory.h>

#include <kernel/config.h>
#include <kernel/kernel.h>

#include <utils/random.h>

/* Console */
#include DRIVER_UART_PATH

/* Libs */
#include <utils/libbool.h>
#include <utils/libtypes.h>

int kmemory_init()
{
    return minit((unsigned int)&HEAP_START, (unsigned int)&HEAP_END);
}

caddr_t kmalloc(unsigned int size)
{
    #ifdef DEBUG
        kprintf("[Function : kmalloc]\n");
    #endif
    return (caddr_t)(mmalloc(size, kget_memory()));
}

caddr_t kcalloc(size_t num, size_t size)
{
    return mcalloc(num, size, kget_memory());
}

void free(void* ptr)
{
    mfree(ptr, kget_memory());
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

        kprintf("Sizeof -char- : %d, sizeof -int- : %d\n", sizeof(char), sizeof(int));
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

        /* Test of malloc functions */
            kprintf("------------------------------------------------------ \n\n");
            kprintf("[Tests] ######### MALLOC tests\n\n");

            /* Int array */
            int * array = kmalloc(sizeof(int) * 3);
            array[0] = 2; array[1] = 5225; array[2] = 454455;
            mmemory_show(kget_memory());

            kprintf("\n### 1 array : type -int- :\n");

            for(int k = 0; k < 3; k++)
                kprintf("[%d] : %d | Adresse : 0x%p\n", k, array[k], &array[k]);

            /* Char array */
            kprintf("\n");

            char * array2 = kmalloc(sizeof(int) * 5);
            array2[0] = 's'; array2[1] = 'a'; array2[2] = 'l';

            kprintf("\n### 2 array : type -char- :\n");

            for(int k = 0; k < 5; k++)
                kprintf("[%d] : %c | Adresse : 0x%p\n", k, array2[k], &array2[k]);

            mmemory_show(kget_memory());

            /* unsigned int  array */
            kprintf("\n");

            int * array3 = kmalloc(sizeof(int) * 4000);

            for(int k = 0; k < 4000; k++)
                array3[k] = rand_1_50(k * 30);

            kprintf("\n### 3 array : type -unsigned int- :\n");
            /*
            for(int k = 0; k < 4000; k++)
                kprintf("[%d] : %d | ", k, array3[k], &array3[k]);
            */
            mmemory_show(kget_memory());
            kprintf("\n");

        /* Test of free functions */
            kprintf("------------------------------------------------------ \n\n");
            kprintf("[Tests] ######### FREE tests\n\n");

            mfree(array2, kget_memory());

            mmemory_show(kget_memory());
            mfree(array3, kget_memory());
    #endif
}