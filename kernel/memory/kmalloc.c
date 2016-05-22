//
// Created by Thibault PIANA on 23/05/16.
//

#include <kernel/memory/kmalloc.h>
#include <kernel/memory/memory.h>

/* Libs */
#include <utils/libbool.h>
#include <utils/libtypes.h>

caddr_t kmalloc(unsigned int size)
{
    caddr_t addr =  (caddr_t)(ksbrk(size, kget_memory()));
}

MEMORY * kget_memory()
{
    return mget_memory(HEAP_START);
}