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

    extern char _bheap;
    extern char _sheap;
    extern char _theap;
    extern char _eheap;

    extern char _sstack;
    extern char _estack;

    #define HEAP_START &_sheap
    #define HEAP_END &_eheap;

    #define STACK_START &_sstack
    #define STACK_END &_estack

    typedef struct {
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int size;
        unsigned char type;
    } MEMORY_BLOCK;

    typedef struct {
        unsigned int size;
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int nb_blocks;
        unsigned int nb_blocks_max;

        MEMORY_BLOCK** blocks;
    } MEMORY_MAPPER;

    typedef struct {
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int size;

        unsigned int usable_heap_start;
        unsigned int usable_heap_end;

        MEMORY_MAPPER mapper;
    } MEMORY;

    /* Functions */
    int minit(bool console);
    void memory_tests();
    unsigned int mcreate_block(MEMORY *memory, unsigned int start_adress, unsigned int size);
    unsigned int mremove_block(MEMORY *memory, MEMORY_BLOCK* entry);

    MEMORY_BLOCK mfind_freeBlock(MEMORY *memory, unsigned int size);
#endif