#include <kernel/memory/memory.h>

#include <kernel/config.h>
#include <kernel/kernel.h>
/* Console */
#include DRIVER_UART_PATH

/* Libs */
#include <utils/libbool.h>
#include <utils/libtypes.h>

int minit()
{
    #ifdef DEBUG_MEMORY
        kprintf("[Memory] ### Start memory initialisation\n");
    #endif

    unsigned int memory_size = (unsigned int)(&HEAP_END - &HEAP_START);

    #ifdef DEBUG_MEMORY
        kprintf("[Memory] HEAP size : %d\n", memory_size);
    #endif

    //unsigned int nb_max_allocation = (memory_size / PAGE_SIZE) + 1; // NOT OPTIMIZED : 12801
    unsigned int nb_max_allocation = memory_size / (sizeof(MEMORY_BLOCK) + PAGE_SIZE) - sizeof(MEMORY) - sizeof(MEMORY_MAPPER); // 12727

    #ifdef DEBUG_MEMORY
        kprintf("[Memory] Max number of blocks : %d\n", nb_max_allocation);
    #endif

    unsigned int total_blocks_size = nb_max_allocation * sizeof(MEMORY_BLOCK); /* Size of allocation table */

    #ifdef DEBUG_MEMORY
        kprintf("[Memory] Total block size : %d bytes\n\n", total_blocks_size);
    #endif

    MEMORY *memory = (MEMORY *)(&HEAP_START);
    MEMORY_MAPPER *memory_mapper = (MEMORY_MAPPER *)(&HEAP_START + sizeof(MEMORY));

    /* MEMORY Configuration */
    memory->start_adress = (unsigned int)(&HEAP_START);
    memory->end_adress = (unsigned int)(&HEAP_END);
    memory->size = memory_size;

    /* MAPPER Configuration */
    memory_mapper->start_adress = (unsigned int)(&HEAP_START) + sizeof(MEMORY);
    memory_mapper->end_adress = memory_mapper->start_adress + sizeof(MEMORY_MAPPER) + total_blocks_size;
    memory_mapper->size = (unsigned int)(memory_mapper->end_adress) - (unsigned int)(memory_mapper->start_adress);
    memory_mapper->nb_blocks = (unsigned int)0;
    memory_mapper->nb_blocks_max = (unsigned int)nb_max_allocation;

    memory_mapper->start_blocks_adress = (unsigned int)(memory_mapper->start_adress + sizeof(MEMORY_MAPPER));

    memory_mapper->usable_heap_start = memory_mapper->end_adress;
    memory_mapper->usable_heap_end = memory->end_adress;

    memory->mapper = memory_mapper;

    #ifdef DEBUG_MEMORY
        kprintf("[Memory] Memory : 0x%p - 0x%p\n", memory->start_adress, memory->end_adress);
        kprintf("[Memory] Memory mapper : 0x%p - 0x%p\n", memory_mapper->start_adress, memory_mapper->end_adress);
        kprintf("[Memory] Usable HEAP zone : 0x%p - 0x%p\n", memory_mapper->usable_heap_start, memory_mapper->usable_heap_end);
        kprintf("[Memory] Max allocations : %d pages of %d bytes\n", nb_max_allocation, PAGE_SIZE);
    #endif
    return EXIT_SUCCESS;
}

MEMORY * mget_memory(unsigned int heap_start)
{
    #ifdef DEBUG_MEMORY
        kprintf("[Function : mget_memory] Starting\n");
    #endif
    #ifdef DEBUG_MEMORY
        kprintf("[Function : mget_memory] Memory getted at 0x%p\n", heap_start);
    #endif
    return (MEMORY *)(heap_start);
}

/* Memory informations */
void mmemory_show(MEMORY * memory)
{
    kprintf("\n-------------------------------------------------------\n");

    /* Print Memory */
    kprintf("###### Memory : \n");
    kprintf("Size : %d ko\n", memory->size / 1024);
    kprintf("Plage : 0x%p - 0x%p\n\n", memory->start_adress, memory->end_adress);

    /* Print Memory Mapper */
    kprintf("###### Memory mapper\n");
    kprintf("Size : %d ko\n", memory->mapper->size / 1024);
    kprintf("Plage : 0x%p - 0x%p\n", memory->mapper->start_adress, memory->mapper->end_adress);
    kprintf("Nb blocks : %d \n", memory->mapper->nb_blocks);
    kprintf("Nb blocks max : %d \n", memory->mapper->nb_blocks_max);
    kprintf("Usable plage : 0x%p - 0x%p\n\n", memory->mapper->usable_heap_start, memory->mapper->usable_heap_end);

    /* Print memory blocks */
    kprintf("###### Blocks\n");
    for(unsigned int k = 0; k < memory->mapper->nb_blocks; k++) {
        kprintf("[%d] Plage : 0x%p - 0x%p\n", k, mget_block(k, memory)->start_adress, mget_block(k, memory)->end_adress);
        kprintf("[%d] Size : %d | Pages : %d | Total size : %d\n", k, mget_block(k, memory)->size, mget_block(k, memory)->nb_page, mget_block(k, memory)->total_size);
    }
}

