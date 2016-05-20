#ifndef ONLYOS_KERNEL_KMALLOC_H
#define ONLYOS_KERNEL_KMALLOC_H
    #include <kernel/config.h>
    #include <utils/libbool.h>

    /*
     * For 1Mb of memory reserved for memory mapper : 16 384 allocations max
     */
    /* General configuration */
    #define PAGE_SIZE = 8192; /* 8kB */

    /* Define */
    #define FREE_BLOCK ((unsigned char)0x10)
    #define TAKEN_BLOCK ((unsigned char)0x20)

    #define HEAP_START _sheap
    #define HEAP_END _eheap;

    typedef struct {
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int size;
        MEMORY_MAPPER mapper;
    } MEMORY;

    typedef struct {
        unsigned int size;
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int nb_blocks;
        unsigned int nb_blocks_max;

        MEMORY_ENTRY** blocks;
    } MEMORY_MAPPER;

    typedef struct {
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int size;
        unsigned char type;
    } MEMORY_BLOCK;

    /* Functions */
    unsigned int minit(MEMORY *memory, bool console_);
    unsigned int mcreate_block(MEMORY *memory, unsigned int start_adress, unsigned int size);
    unsigned int mremove_block(MEMORY *memory, MEMORY_BLOCK* entry);

    MEMORY_BLOCK mfind_freeBlock(MEMORY *memory, unsigned int size);
#endif