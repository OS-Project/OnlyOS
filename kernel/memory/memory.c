#include <kernel/memory/memory.h>
#include <kernel/config.h>

/* Console */
#include DRIVER_UART_PATH
/* Libs */
#include <utils/libbool.h>
#include <utils/libtypes.h>

void minit(bool console)
{
    HEAP_END = STACK_START - 1;
    HEAP_TOP = HEAP_END;

    unsigned int memory_size = (unsigned int)(HEAP_END - HEAP_START);

    if(console)
        kprintf("[Memory] HEAP size : %d", memory_size);

    unsigned int nb_max_allocation = (memory_size / PAGE_SIZE) + 1; /* NOT OPTIMIZED */

    if(console)
        kprintf("[Memory] Max number of blocks : %d", nb_max_allocation);

    unsigned int size_max = nb_max_allocation * sizeof(MEMORY_BLOCK); /* Size of allocation table */

    MEMORY *memory = HEAP_START;
    MEMORY_MAPPER *memory_mapper = HEAP_START + sizeof(MEMORY);

    /* MEMORY Configuration */
    memory->start_adress = (unsigned int)(HEAP_START);
    memory->end_adress = (unsigned int)(HEAP_END);
    memory->size = memory_size;

    /* MAPPER Configuration */
    memory_mapper->start_adress = HEAP_START + sizeof(MEMORY); //
    memory_mapper->end_adress = HEAP_START + sizeof(MEMORY) + sizeof(MEMORY_MAPPER); //
    memory_mapper->size = memory_mapper->end_adress - memory_mapper->start_adress;
    memory_mapper->nb_blocks = 0;
    memory_mapper->nb_blocks_max = nb_max_allocation;

    memory_mapper->blocks = memory_mapper->end_adress; //
    memory->mapper = memory_mapper;

    /* Set HEAP attributes */
    HEAP_START = HEAP_START + sizeof(MEMORY) + sizeof(MEMORY_MAPPER) + size_max; /* Set base adress to the begining of the real HEAP zone */

    
    kprintf("[Memory] HEAP start : 0x%p\n", HEAP_START);
    kprintf("[Memory] HEAP top : 0x%p\n", HEAP_TOP);
}

/* _sbrk syscall */
caddr_t ksbrk(int incr, MEMORY* memory)
{

}