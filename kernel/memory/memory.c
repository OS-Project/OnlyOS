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
    memory_mapper->size = memory_mapper->end_adress - memory_mapper->start_adress;
    memory_mapper->nb_blocks = (unsigned int)0;
    memory_mapper->nb_blocks_max = (unsigned int)nb_max_allocation;

    memory_mapper->blocks = (MEMORY_BLOCK **)(memory_mapper->start_adress + sizeof(MEMORY_MAPPER));

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
/* _sbrk syscall */
caddr_t ksbrk(unsigned int incr, MEMORY* memory)
{
    #ifdef DEBUG_MEMORY
        kprintf("[Function : ksbrk] Starting\n");
    #endif
    unsigned int block_adress = (mfind_free_block(incr, memory));

    #ifdef DEBUG_MEMORY
        kprintf("[Function : ksbrk] free block finded at 0x%p\n", block_adress);
    #endif

    MEMORY_BLOCK * mblock;

    if(block_adress != false) {
        mblock = madd_block(incr, block_adress, memory);
        return (caddr_t) mblock;
    }
    else /* ERROR : No space */
        return (caddr_t)0; /* A modifier : faire une interruption d'erreur */
}

unsigned int mfind_free_block(unsigned int size, MEMORY* memory)
{
    #ifdef DEBUG_MEMORY
        kprintf("[Function : mfind_free_block] Starting\n");
    #endif
    MEMORY_MAPPER *mapper = memory->mapper;
    #ifdef DEBUG_MEMORY
        kprintf("[Function : mfind_free_block] mapper getted\n");
    #endif
    unsigned int adress = 0;
    unsigned int b1, b2;

    #ifdef DEBUG_MEMORY
        kprintf("[Function : mfind_free_block] Ready to switch\n");
    #endif
    switch(mapper->nb_blocks)
    {
        case 0:
            #ifdef DEBUG_MEMORY
                kprintf("[Function : mfind_free_block] case 0\n");
            #endif
            if(mapper->usable_heap_end - mapper->usable_heap_start > size)
                adress = mapper->usable_heap_start;
            else
                adress = 0;
            break;
        case 1:
            #ifdef DEBUG_MEMORY
                kprintf("[Function : mfind_free_block] case 1\n");
            #endif
            if((mapper->usable_heap_end - mapper->blocks[0]->end_adress) >= size)
                adress = mapper->blocks[0]->end_adress;
            else
                adress = (unsigned int)false;
            break;
        default:
            #ifdef DEBUG_MEMORY
                kprintf("[Function : mfind_free_block] case >2\n");
            #endif
            b1 = mapper->blocks[0]->end_adress; b2 = mapper->blocks[1]->end_adress;
            bool find = false;

            for(unsigned int k = 1; k < mapper->nb_blocks - 1; k++) {
                b2 = mapper->blocks[k]->end_adress;
                if (b2 - b1 > size) {
                    adress = b1;
                    find = true;
                }
                else
                    b1 = b2;
            }
            /* If we haven't find, we look the last block */
            if(find == false)
                if(mapper->usable_heap_end - mapper->blocks[mapper->nb_blocks - 1]->end_adress > size)
                    adress = mapper->blocks[mapper->nb_blocks - 1]->end_adress;
                else
                    adress = 0;
            else
                adress = adress;
            break;
    }
    return adress;
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
        kprintf("[Function : madd_block] Starting\n");
    #endif
    MEMORY_MAPPER * mapper = memory->mapper;
    if(mapper->nb_blocks + 1 < mapper->nb_blocks_max) {
        MEMORY_BLOCK *block = mapper->blocks[mapper->nb_blocks];

        unsigned int nb_pages = (size / PAGE_SIZE) + 1;
        unsigned int end_adress = (unsigned int)(start_adress) + (nb_pages * PAGE_SIZE);

        #ifdef DEBUG_MEMORY
                kprintf("[Function : madd_block] Block added at : 0x%p - 0x%p\n", start_adress, end_adress);
        #endif
        block->start_adress = start_adress;
        block->end_adress = end_adress;
        block->size = size;
        block->nb_page = nb_pages;
        block->total_size = nb_pages * PAGE_SIZE;
        mapper->nb_blocks++;

        return block;
    }
    else
        return (MEMORY_BLOCK *)NULL; /* Error */
}

void mfree_block(MEMORY_BLOCK * block, MEMORY * memory)
{
    unsigned int k;
    MEMORY_MAPPER * mapper = memory->mapper;

    switch (mapper->nb_blocks) {
        case 0:
            break;
        case 1:
            mapper->nb_blocks--;

            MEMORY_BLOCK * block = mapper->blocks[0];

            for (unsigned int i = 0; i < mapper->end_adress; i++) {
                char *byte = (char *)mapper->blocks[mapper->nb_blocks - 1];
                *byte = 0x0;
            }
            break;
        default:
            k = 0;
            while (mapper->blocks[k]->start_adress != block->start_adress && k < mapper->nb_blocks)
                k++;

            if (k != mapper->nb_blocks) {
                /* Copy all blocks */
                for (unsigned int i = 0; i < mapper->nb_blocks - k; k++)
                    mcopy_block(mapper->blocks[i + k], mapper->blocks[i + k + 1]);

                /* Remove the last block (optionnal) */
                for (unsigned int i = 0; i < mapper->end_adress; i++) {
                    char *byte = (char *)mapper->blocks[mapper->nb_blocks - 1];
                    *byte = 0x0;
                }

                mapper->nb_blocks--;
            }
            else
                kexit(2); /* Error */
            break;
    }
}

void mcopy_block(MEMORY_BLOCK * destination_block, MEMORY_BLOCK * source_block)
{
    destination_block->start_adress = source_block->start_adress;
    destination_block->end_adress = source_block->end_adress;
    destination_block->size = source_block->size;
    destination_block->total_size = source_block->total_size;
    destination_block->nb_page = source_block->nb_page;
}

/*
unsigned int mget_free_space(MEMORY * memory)
{
}*/

void mmemory_show(MEMORY * memory)
{
    for(unsigned int k = 0; k < memory->mapper->nb_blocks; k++) {
        kprintf("----------------------------------------------------\n");
        kprintf("Block %d :\n", k);
        kprintf("Plage : 0x%p - 0x%p\n", memory->mapper->blocks[k]->start_adress, memory->mapper->blocks[k]->end_adress);
        kprintf("Size : %d\n", memory->mapper->blocks[k]->size);
    }
}

