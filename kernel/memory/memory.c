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
    #ifdef DEBUG
        kprintf("[Memory] ### Start memory initialisation\n");
    #endif

    unsigned int memory_size = (unsigned int)(&HEAP_END - &HEAP_START);

    #ifdef DEBUG
        kprintf("[Memory] HEAP size : %d\n", memory_size);
    #endif

    //unsigned int nb_max_allocation = (memory_size / PAGE_SIZE) + 1; // NOT OPTIMIZED : 12801
    unsigned int nb_max_allocation = memory_size / (sizeof(MEMORY_BLOCK) + PAGE_SIZE) - sizeof(MEMORY) - sizeof(MEMORY_MAPPER); // 12727

    #ifdef DEBUG
        kprintf("[Memory] Max number of blocks : %d\n", nb_max_allocation);
    #endif

    unsigned int total_blocks_size = nb_max_allocation * sizeof(MEMORY_BLOCK); /* Size of allocation table */

    #ifdef DEBUG
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
    memory_mapper->nb_blocks = 0;
    memory_mapper->nb_blocks_max = nb_max_allocation;

    memory_mapper->blocks = (MEMORY_BLOCK **)(memory_mapper->start_adress + sizeof(MEMORY_MAPPER));

    memory_mapper->usable_heap_start = memory_mapper->end_adress;
    memory_mapper->usable_heap_end = memory->end_adress;

    memory->mapper = memory_mapper;

    #ifdef DEBUG
        kprintf("[Memory] Memory : 0x%p - 0x%p\n", memory->start_adress, memory->end_adress);
        kprintf("[Memory] Memory mapper : 0x%p - 0x%p\n", memory_mapper->start_adress, memory_mapper->end_adress);
        kprintf("[Memory] Usable HEAP zone : 0x%p - 0x%p\n", memory_mapper->usable_heap_start, memory_mapper->usable_heap_end);
        kprintf("[Memory] Max allocations : %d pages of %d bytes\n", nb_max_allocation, PAGE_SIZE);
    #endif
    return EXIT_SUCCESS;
}

/* _sbrk syscall */

caddr_t ksbrk(unsigned int incr, MEMORY* memory)
{
    // TODO : verifier qu'on ne depasse pas le nombre max de block
    #ifdef DEBUG

        kprintf("[Function : ksbrk] Starting\n");
    #endif
    unsigned int block = (mfind_free_block(incr, memory));

    #ifdef DEBUG
        kprintf("[Function : ksbrk] free block finded at 0x%p\n", block);
    #endif

    MEMORY_MAPPER *mapper = memory->mapper;
    MEMORY_BLOCK * mblock;

    if(block != false) {
        /*
        if(mapper->nb_blocks > 0)
            mblock = (MEMORY_BLOCK *)mapper->blocks[mapper->nb_block - 1]->end_adress;
        else
            mblock = (MEMORY_BLOCK *)(mapper->start_adress + sizeof(MEMORY_MAPPER));
        */

        mblock = mapper->blocks[mapper->nb_blocks];

        mblock->start_adress = block;
        mblock->end_adress = (incr - mblock->start_adress) / PAGE_SIZE * (PAGE_SIZE + 1);
        mblock->size = mblock->end_adress - mblock->start_adress;

        mapper->nb_blocks += 1;

        return (caddr_t) block;
    }
    else /* ERROR : No space */
        return (caddr_t)0; /* A modifier : faire une interruption d'erreur */
}

unsigned int mfind_free_block(unsigned int size, MEMORY* memory)
{
    #ifdef DEBUG
        kprintf("[Function : mfind_free_block]\n");
    #endif
    MEMORY_MAPPER *mapper = memory->mapper;
    #ifdef DEBUG
        kprintf("[Function : mfind_free_block] mapper getted\n");
    #endif
    unsigned int adress = 0;
    unsigned int b1, b2;

    #ifdef DEBUG
        kprintf("[Function : mfind_free_block] Ready to switch\n");
    #endif
    switch(mapper->nb_blocks)
    {
        case 0:
            #ifdef DEBUG
                kprintf("[Function : mfind_free_block] case 0\n");
            #endif
            if(mapper->usable_heap_end - mapper->usable_heap_start > size)
                adress = mapper->usable_heap_start;
            else
                adress = 0;

            break;
        case 1:
            #ifdef DEBUG
                kprintf("[Function : mfind_free_block] case 1\n");
            #endif
            if((mapper->usable_heap_end - mapper->blocks[0]->end_adress) >= size)
                adress = mapper->blocks[0]->end_adress;
            else
                adress = (unsigned int)false;
            break;
        default:
            #ifdef DEBUG
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
    #ifdef DEBUG
        kprintf("[Function : mget_memory]\n");
    #endif
    #ifdef DEBUG
        kprintf("[Function :] Memory getted at 0x%p\n", heap_start);
    #endif
    return (MEMORY *)(heap_start);
}

/*
unsigned int mcopy_block(MEMORY_BLOCK block, unsigned int addr)
{

}
*/