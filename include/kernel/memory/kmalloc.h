//
// Created by Thibault PIANA on 23/05/16.
//

#ifndef ONLYOS_KERNEL_KMALLOC_H
#define ONLYOS_KERNEL_KMALLOC_H
    /* Define */
    extern char _sheap;
    extern char _eheap;

    #define HEAP_START _sheap
    #define HEAP_END _eheap

    /* Libs */
    #include <utils/libbool.h>
    #include <utils/libtypes.h>
    #include <kernel/memory/memory.h>

    int kmemory_init();
    caddr_t kmalloc(unsigned int size);

    caddr_t kcalloc(size_t num, size_t size);
    void free(void* ptr);

    MEMORY * kget_memory();
    void memory_tests();
#endif //ONLYOS_KERNEL_KMALLOC_H
