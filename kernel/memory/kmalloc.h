#ifndef ONLYOS_KERNEL_KMALLOC_H
#define ONLYOS_KERNEL_KMALLOC_H

/*
 * For 1Mb of memory reserved for memory mapper : 16 384 allocations max
 */

typedef struct {
    unsigned int size;
    unsigned int start_adress;
    unsigned int end_adress;
    MEMORY_ENTRY** entries;
} MEMORY_MAPPER;

typedef struct {
    unsigned int start_adress;
    unsigned int size;
} MEMORY_ENTRY;

int minit(unsigned int start_adress, unsigned int size);
int mcreateEntry(unsigned int start_adress, unsigned int size);
int mremoveEntry(unsigned int start_adress, unsigned int size);

void* mfindFreeBlock(unsigned int size);
#endif