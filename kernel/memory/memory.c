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

/* Memory operation */
/* malloc syscall */
caddr_t mmalloc(unsigned int size, MEMORY* memory)
{
    #ifdef DEBUG_MEMORY
        kprintf("[Function : mmalloc] Starting\n");
    #endif
    unsigned int block_adress = (mfind_free_block(size, memory));

    #ifdef DEBUG_MEMORY
        kprintf("[Function : mmalloc] free block finded at 0x%p\n", block_adress);
    #endif

    MEMORY_BLOCK * mblock;

    if(block_adress != false) {
        mblock = madd_block(size, block_adress, memory);
        return (caddr_t)(mblock->start_adress);
    }
    else /* ERROR : No space */
        return (caddr_t)0; /* A modifier : faire une interruption d'erreur */
}

unsigned int mfind_free_block(unsigned int size, MEMORY* memory)
{
    #ifdef DEBUG_MEMORY
        kprintf("    [Function : mfind_free_block] Starting\n");
    #endif

    MEMORY_MAPPER *mapper = memory->mapper;

    #ifdef DEBUG_MEMORY
        kprintf("    [Function : mfind_free_block] mapper getted\n");
    #endif

    unsigned int adress = 0;
    unsigned int b1, b2;

    #ifdef DEBUG_MEMORY
        kprintf("    [Function : mfind_free_block] Ready to switch\n");
    #endif
    switch(mapper->nb_blocks)
    {
        case 0:
            #ifdef DEBUG_MEMORY
                kprintf("    [Function : mfind_free_block] case 0\n");
            #endif
            if(mapper->usable_heap_end - mapper->usable_heap_start > size)
                adress = mapper->usable_heap_start;
            else
                adress = 0;
            break;
        case 1:
            #ifdef DEBUG_MEMORY
                kprintf("    [Function : mfind_free_block] case 1\n");
            #endif
            if((mapper->usable_heap_end - mget_block(0, memory)->end_adress) >= size)
                adress = mget_block(0, memory)->end_adress;
            else
                adress = (unsigned int)false;
            break;
        default:
            #ifdef DEBUG_MEMORY
                kprintf("    [Function : mfind_free_block] case >2\n");
            #endif
            b1 = mget_block(0, memory)->end_adress; b2 = mget_block(1, memory)->end_adress;
            bool find = false;

            for(unsigned int k = 1; k < mapper->nb_blocks - 1; k++) {
                b2 = mget_block(k, memory)->end_adress;
                if (b2 - b1 > size) {
                    adress = b1;
                    find = true;
                }
                else
                    b1 = b2;
            }
            /* If we haven't find, we look the last block */
            if(find == false)
                if(mapper->usable_heap_end - mget_last_block(memory)->end_adress > size)
                    adress = mget_last_block(memory)->end_adress;
                else
                    adress = 0;
            else
                adress = adress;
            break;
    }
    return adress;
}

MEMORY_BLOCK * mget_block(unsigned int nb, MEMORY * memory)
{
    unsigned int adress;
    if(memory->mapper->nb_blocks > nb) {
        adress = memory->mapper->start_blocks_adress + (nb * (unsigned int)sizeof(MEMORY_BLOCK));
        return (MEMORY_BLOCK *)(adress);
    }
    else
        return (MEMORY_BLOCK *)0x0; /* Error */
}

MEMORY_BLOCK * mget_last_block(MEMORY * memory)
{
    if(memory->mapper->nb_blocks > 0)
        return mget_block(memory->mapper->nb_blocks - 1, memory);
    else
        return (MEMORY_BLOCK *)0x0; /* Error */
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

/* Blocks operations */
MEMORY_BLOCK* madd_block(unsigned int size, unsigned int start_adress, MEMORY *memory)
{
    #ifdef DEBUG_MEMORY
        kprintf("    [Function : madd_block] Starting\n");
    #endif
    MEMORY_MAPPER * mapper = memory->mapper;
    MEMORY_BLOCK * block;

    unsigned int nb_pages;
    unsigned int end_adress;

    if(mapper->nb_blocks + 1 < mapper->nb_blocks_max) {
        block = (MEMORY_BLOCK *)(mapper->start_blocks_adress + (mapper->nb_blocks * (unsigned int)sizeof(MEMORY_BLOCK)));

        nb_pages = (size / PAGE_SIZE) + 1;
        end_adress = (unsigned int)(start_adress) + (nb_pages * PAGE_SIZE);

        #ifdef DEBUG_MEMORY
            kprintf("    [Function : madd_block] Block added at : 0x%p - 0x%p and using %d pages | Block adress : 0x%p\n", start_adress, end_adress, nb_pages, block);
        #endif

        /* Block creation */
        block->start_adress = start_adress;
        block->end_adress = end_adress;
        block->size = size;
        block->nb_page = nb_pages;
        block->total_size = nb_pages * PAGE_SIZE;

        /* Increment number of blocks */
        mapper->nb_blocks++;

    }
    else {
        #ifdef DEBUG_MEMORY
            kprintf("    [Function : madd_block] Error\n");
        #endif

        block = (MEMORY_BLOCK *)0x0; /* Error */
    }

    return block;
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

