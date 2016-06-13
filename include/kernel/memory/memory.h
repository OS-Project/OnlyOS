#ifndef ONLYOS_KERNEL_MEMORY_H
#define ONLYOS_KERNEL_MEMORY_H
    #include <kernel/config.h>
    #include <utils/libbool.h>
    #include <utils/libtypes.h>

    /* General configuration */
    #define PAGE_SIZE (unsigned int)(8192) /* 8kB */

    typedef struct {
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int size;
        unsigned int nb_page;
        unsigned int total_size;
    } MEMORY_BLOCK;

    typedef struct {
        unsigned int size;
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int nb_blocks;
        unsigned int nb_blocks_max;

        unsigned int usable_heap_start;
        unsigned int usable_heap_end;

        unsigned int start_blocks_adress;
    } MEMORY_MAPPER;

    typedef struct {
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int size;

        MEMORY_MAPPER *mapper;
    } MEMORY;

    /* Memory functions */
    int minit(unsigned int _heap_start, unsigned int _heap_end);
    MEMORY * mget_memory(unsigned int heap_start);

    void mmemory_show(MEMORY * memory);

    /* Malloc functions */
    caddr_t mmalloc(size_t size, MEMORY* memory);
    caddr_t mcalloc(size_t num, size_t elt_size, MEMORY* memory);
    caddr_t mrealloc(void* ptr, size_t size, MEMORY* memory);

    /* Free functions */
    void mfree(void *ptr, MEMORY* memory);
    void mfree_block(MEMORY_BLOCK * block, MEMORY * memory);

    /* Miscellaneous functions */
    unsigned int mfind_free_area(unsigned int size, MEMORY* memory);

    MEMORY_BLOCK* madd_block(unsigned int size, unsigned int start_adress, MEMORY *memory);
    MEMORY_BLOCK* mcopy_block(MEMORY_BLOCK * destination_block, MEMORY_BLOCK * source_block);
    MEMORY_BLOCK * mfind_block(unsigned int ptr, MEMORY* memory);
    MEMORY_BLOCK * mget_block(unsigned int nb, MEMORY * memory);
    MEMORY_BLOCK * mget_last_block(MEMORY * memory);

    unsigned int mget_block_number(MEMORY_BLOCK * block, MEMORY * memory);
    void merase_block(MEMORY_BLOCK * block);
#endif