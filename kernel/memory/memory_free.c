#include <kernel/memory/memory.h>

#include <kernel/config.h>
#include <kernel/kernel.h>

/* Console */
#include DRIVER_UART_PATH

/* Libs */
#include <utils/libbool.h>
#include <utils/libtypes.h>

void mfree(void *ptr, MEMORY * memory)
{
    MEMORY_BLOCK * block = mfind_block((unsigned int)ptr, memory);

    if(block != 0x0)
        mfree_block(block, memory);
    else {} /* Error */
}

void mfree_block(MEMORY_BLOCK * block, MEMORY * memory)
{
    #ifdef DEBUG_MEMORY
        kprintf("[Function : mfree] Starting\n");
    #endif
    unsigned int k = 0, i = 0;
    MEMORY_MAPPER * mapper = memory->mapper;

    switch (mapper->nb_blocks) {
        case 0:
            break;
        case 1:
            /* Erase the block */
            merase_block(block, memory);
            mapper->nb_blocks--;
            break;
        default:
            k = mget_block_number(block, memory);

            #ifdef DEBUG_MEMORY
                kprintf("[Function : mfree] Case default\n");
            #endif
            for (i = 0; i < mapper->nb_blocks - k - 1; k++)
                mcopy_block(mget_block(k + i,memory), mget_block(k + i + 1, memory));

            #ifdef DEBUG_MEMORY
                kprintf("[Function : mfree] Blocks copied\n");
            #endif

            merase_block(mget_last_block(memory), memory);

            #ifdef DEBUG_MEMORY
                kprintf("[Function : mfree] Block erased\n");
            #endif

            mapper->nb_blocks--;
            break;
    }
}