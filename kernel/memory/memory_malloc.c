#include <kernel/memory/memory.h>

#include <kernel/config.h>
#include <kernel/kernel.h>

/* Console */
#include DRIVER_UART_PATH

/* Libs */
#include <utils/libbool.h>
#include <utils/libtypes.h>

/* Memory operation */
/* malloc syscall */
caddr_t mmalloc(unsigned int size, MEMORY* memory)
{
    #ifdef DEBUG_MEMORY
        kprintf("[Function : mmalloc] Starting\n");
    #endif

    MEMORY_BLOCK * block;
    unsigned int data_adress = (mfind_free_area(size, memory));

    #ifdef DEBUG_MEMORY
        kprintf("[Function : mmalloc] free block finded at 0x%p\n", data_adress);
    #endif

    if(data_adress != 0x0) {
        block = madd_block(size, data_adress, memory);
        return (caddr_t)(block->start_adress);
    }
    else /* ERROR : No space */
        return (caddr_t)0; /* Error : A modifier : faire une interruption d'erreur */
}

caddr_t mcalloc(size_t num, size_t elt_size, MEMORY* memory)
{
    #ifdef DEBUG_MEMORY
        kprintf("[Function : mcalloc] Starting\n");
    #endif

    MEMORY_BLOCK * block;
    unsigned int size = (unsigned int)num * (unsigned int)elt_size;
    unsigned int data_adress = (mfind_free_area(size, memory));
    char * word;

    #ifdef DEBUG_MEMORY
        kprintf("[Function : mcalloc] free block finded at 0x%p\n", data_adress);
    #endif

    if(data_adress != 0x0) {
        block = madd_block(size, data_adress, memory);

        /* Set all bytes to 0x0 */
        #ifdef DEBUG_MEMORY
            kprintf("[Function : mcalloc] Rewrite words to 0x0\n");
        #endif

        for(unsigned int k = 0; k < block->total_size; k++) {
            word = (char *)(block->start_adress + k);
            *word = 0;
        }

        return (caddr_t)(block->start_adress);
    }
    else /* ERROR : No space */
        return (caddr_t)0x0; /* Error : A modifier : faire une interruption d'erreur */
}

caddr_t mrealloc(void* ptr, size_t size, MEMORY * memory)
{
    MEMORY_BLOCK * block = mfind_block((unsigned int)ptr, memory);
    unsigned int new_adress;
    char * word_d;
    char * word_s;

    if(block->total_size > size)
        return (caddr_t)ptr;
    else {
        new_adress = (mfind_free_area(size, memory));

        for(unsigned int k = 0; k < block->size; k++) {
            word_d = (char *)(new_adress + k);
            word_s = (char *)(block->start_adress + k);
            *word_d = *word_s;
        }

        mfree(ptr, memory);
        return (caddr_t)(new_adress);
    }
}