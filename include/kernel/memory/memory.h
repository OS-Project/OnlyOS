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
    #define FREE_BLOCK ((unsigned char)0x10)
    #define TAKEN_BLOCK ((unsigned char)0x20)

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
        unsigned char type;
    } MEMORY_BLOCK;

    typedef struct {
        unsigned int size;
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int nb_blocks;
        unsigned int nb_blocks_max;

        unsigned int usable_heap_start;
        unsigned int usable_heap_end;
        MEMORY_BLOCK** blocks;
    } MEMORY_MAPPER;

    typedef struct {
        unsigned int start_adress;
        unsigned int end_adress;
        unsigned int size;

        MEMORY_MAPPER *mapper;
    } MEMORY;

    /* Functions */
    int minit();
    MEMORY_BLOCK* mcreate_block(MEMORY *memory, unsigned int start_adress, unsigned int size);
    unsigned int mremove_block(MEMORY *memory, MEMORY_BLOCK* entry);

    caddr_t ksbrk(unsigned int incr, MEMORY* memory);
    MEMORY * mget_memory(unsigned int heap_start);
    unsigned int mfind_free_block(unsigned int size, MEMORY* memory);
#endif