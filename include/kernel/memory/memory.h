#ifndef ONLYOS_KERNEL_MEMORY_H
#define ONLYOS_KERNEL_MEMORY_H
    #include <kernel/config.h>
    #include <utils/libbool.h>
    #include <utils/libtypes.h>

    /*
     * For 1Mb of memory reserved for memory mapper : 16 384 allocations max
     */
    /* General configuration */
    #define PAGE_SIZE (unsigned int)(8192) /* 8kB */

    /* Define */
    extern char _sheap;
    extern char _eheap;

    extern char _sstack;
    extern char _estack;

    #define HEAP_START _sheap
    #define HEAP_END _eheap

    #define STACK_START _sstack
    #define STACK_END _estack

    typedef struct {
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int size;
        unsigned int nb_page;
        unsigned int total_size;
        //unsigned int number;
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

    /* Functions */
    int minit();


    caddr_t mmalloc(unsigned int size, MEMORY* memory);
    MEMORY * mget_memory(unsigned int heap_start);
    unsigned int mfind_free_block(unsigned int size, MEMORY* memory);

    MEMORY_BLOCK* madd_block(unsigned int size, unsigned int start_adress, MEMORY *memory);
    void mfree_block(MEMORY_BLOCK * block, MEMORY * memory);
    void mcopy_block(MEMORY_BLOCK * destination_block, MEMORY_BLOCK * source_block);

    MEMORY_BLOCK * mget_block(unsigned int nb, MEMORY * memory);
    MEMORY_BLOCK * mget_last_block(MEMORY * memory);
    void * kmemcpy(void * destination, const void * source, size_t num);

    void mmemory_show(MEMORY * memory);
    unsigned int mget_free_space(MEMORY * memory);
#endif