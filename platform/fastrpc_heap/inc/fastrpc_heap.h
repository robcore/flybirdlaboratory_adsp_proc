#ifndef FASTRPC_HEAP_H
#define FASTRPC_HEAP_H

#include <stdlib.h>

#define ADSP_MMAP_ANY_ADDR    0
#define ADSP_MMAP_FIXED_ADDR  1
#define ADSP_MMAP_HEAP_ADDR   4
#define ADSP_MMAP_ADD_PAGES   0x1000

int mem_pool_grow(size_t size);

void* rpc_realloc(void* ptr, size_t size);
void* rpc_malloc(size_t size);
void* rpc_calloc(size_t num_elem, size_t elem_size);
void* rpc_memalign(size_t block_size, size_t size);
void  rpc_free(void *ptr);

#endif // FASTRPC_HEAP_H
