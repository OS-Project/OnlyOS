#include <kernel/memory/memory.h>

#include <kernel/config.h>
#include <kernel/kernel.h>

/* Console */
#include DRIVER_UART_PATH

/* Libs */
#include <utils/libbool.h>
#include <utils/libtypes.h>

unsigned int mfind_free_area(unsigned int size, MEMORY* memory)
{
    #ifdef DEBUG_MEMORY
        kprintf("    [Function : mfind_free_block] Starting\n");
    #endif

    MEMORY_MAPPER *mapper = memory->mapper;

    unsigned int adress = 0;
    unsigned int b1, b2;

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

MEMORY_BLOCK * mfind_block(unsigned int ptr, MEMORY* memory)
{
    unsigned int k = 0;

    while(mget_block(k, memory)->start_adress != ptr && k < memory->mapper->nb_blocks)
        k++;

    if(k < memory->mapper->nb_blocks)
        return mget_block(k, memory);
    else
        return 0x0;
}

MEMORY_BLOCK* mcopy_block(MEMORY_BLOCK * destination_block, MEMORY_BLOCK * source_block)
{
    destination_block->start_adress = source_block->start_adress;
    destination_block->end_adress = source_block->end_adress;
    destination_block->size = source_block->size;
    destination_block->total_size = source_block->total_size;
    destination_block->nb_page = source_block->nb_page;

    return destination_block;
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