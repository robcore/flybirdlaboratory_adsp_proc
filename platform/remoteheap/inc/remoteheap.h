#ifndef RENOTEHEAP_H
#define RENOTEHEAP_H

#ifdef __cplusplus
extern "C" {
#endif

    int pl_grow_heap_dynamically(void *heap_ptr, unsigned int growth_size);

    // To be used by platform code only
    int pl_grow_heap(void *heap_ptr,unsigned int size_needed);
    int pl_release_heap(void * vaddr, unsigned int size);

#ifdef __cplusplus
}
#endif

#endif /*RENOTEHEAP_H*/
