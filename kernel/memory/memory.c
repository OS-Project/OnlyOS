#include <kernel/memory/memory.h>
#include <kernel/config.h>
/* Console */
#include DRIVER_UART_PATH
/* Libs */

#include <utils/libbool.h>
#include <utils/libtypes.h>

int minit(bool console)
{
    /**
    HEAP_END = STACK_START - 1;
    HEAP_TOP = HEAP_END;

    unsigned int memory_size = (unsigned int)(HEAP_END - HEAP_START);

    if(console)
        kprintf("[Memory] HEAP size : %d", memory_size);

    unsigned int nb_max_allocation = (memory_size / PAGE_SIZE) + 1; // NOT OPTIMIZED

    if(console)
        kprintf("[Memory] Max number of blocks : %d", nb_max_allocation);

    unsigned int size_max = nb_max_allocation * sizeof(MEMORY_BLOCK); // Size of allocation table

    MEMORY *memory = HEAP_START;
    MEMORY_MAPPER *memory_mapper = HEAP_START + sizeof(MEMORY);
    */
/*    *//* MEMORY Configuration *//*
    memory->start_adress = (unsigned int)(HEAP_START);
    memory->end_adress = (unsigned int)(HEAP_END);
    memory->size = memory_size;

    *//* MAPPER Configuration *//*
    memory_mapper->start_adress = HEAP_START + sizeof(MEMORY); //
    memory_mapper->end_adress = HEAP_START + sizeof(MEMORY) + sizeof(MEMORY_MAPPER); //
    memory_mapper->size = memory_mapper->end_adress - memory_mapper->start_adress;
    memory_mapper->nb_blocks = 0;
    memory_mapper->nb_blocks_max = nb_max_allocation;

    memory_mapper->blocks = memory_mapper->end_adress; //
    memory->mapper = memory_mapper;

    *//* Set HEAP attributes *//*
    HEAP_START = HEAP_START + sizeof(MEMORY) + sizeof(MEMORY_MAPPER) + size_max; *//* Set base adress to the begining of the real HEAP zone *//*

    
    kprintf("[Memory] HEAP start : 0x%p\n", HEAP_START);
    kprintf("[Memory] HEAP top : 0x%p\n", HEAP_TOP);*/
    return EXIT_SUCCESS;
}

/* _sbrk syscall */
/*
caddr_t ksbrk(int incr, MEMORY* memory)
{

}
*/

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


        
    #endif
}