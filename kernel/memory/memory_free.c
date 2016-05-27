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
    /*
    unsigned int k = 0;
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
            while (mapper->blocks[k]->start_adress != block->start_adress && k < mapper->nb_blocks)
                k++;

            if (k != mapper->nb_blocks) {

                for (unsigned int i = 0; i < mapper->nb_blocks - k; k++)
                    mcopy_block(mapper->blocks[i + k], mapper->blocks[i + k + 1]);


                for (unsigned int i = 0; i < mapper->end_adress; i++) {
                    char *byte = (char *)mapper->blocks[mapper->nb_blocks - 1];
                    *byte = 0x0;
                }

                mapper->nb_blocks--;
            }
            else
                kexit(2); Error
            break;
    }*/
}