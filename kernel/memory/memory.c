#include <kernel/memory/memory.h>
#include <kernel/config.h>

/* Libs */
#include <utils/libbool.h>

MEMORY* minit(bool console)
{
    unsigned int memory_size = (unsigned int)(HEAP_TOP - HEAP_START);
    unsigned int nb_max_allocation = (memory_size / PAGE_SIZE) + 1; /* NOT OPTIMIZED */

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

    HEAP_START = HEAP_START + sizeof(MEMORY) + sizeof(MEMORY_MAPPER) + size_max; /* Set base adress to the begining of the real HEAP zone */

    return memory;
}
