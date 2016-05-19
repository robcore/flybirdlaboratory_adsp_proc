#ifndef APR_MEMMGR_I_H
#define APR_MEMMGR_I_H
/**
  @file apr_memmgr_i.h
  @brief A simple sub-allocator to manage memory allocations and deallocations
  using a Next Fit strategy. 
  @note THIS IS AN INTERNAL APR FILE. DO NOT USE THESE INTERFACES DIRECTLY

*/
/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear 
      in the PDF. 

      The Utility_Services_API_mainpage.dox file contains all file/group 
      descriptions that are in the output PDF generated using Doxygen and 
      Latex. To edit or update any of the file/group text in the PDF, edit 
      the Utility_Services_API_mainpage.dox file or contact Tech Pubs.

      The above description for this file is part of the "utils_memory" 
      group description in the Utility_Services_API_mainpage.dox file. 
===========================================================================*/
/*===========================================================================
 Note that these routines are FULLY re-entrant.  Furthermore, while
  performing memory allocation/deallocation calls on one heap, the routines
  may be interrupted to perform memory allocation/deallocation calls on
  different heaps without blocking or corruption.  However, should an
  interrupting task attempt to perform memory allocation/deallocation
  on the same heap that had a critical section interrupted, it will block
  allowing the first call to finish.  All this is accomplished by giving
  each heap its own semaphore.

FEATURE_MEMHEAP_MT
Activates multi threading support for the heap

  Usage Notes - Avoiding Fragmentation
 
1. If all bytes in the heap are freed, the heap is guaranteed to be returned
 to the same state as after a call to mem_init_heap, except that the
 values of maxUsed & maxRequest are not reset.  The order in which blocks
 are freed is irrelevant so long as they ALL are freed.
 
2. After n consecutive malloc/calloc calls, in a heap with non-fragmented
 free space (and no intervening realloc calls that return a new pointer),
 calling free in the reverse order on the n blocks guarantees that the heap
 will be returned to the exact same state as before the n alloc calls.
 
3. FEATURE_HEAP_SMALLER_OVERHEAD == 0
 (2) still applies, except the calls to free may be made in any order and
 after all n blocks are freed, the heap is guaranteed to be returned to the
 exact same state as prior to the n alloc calls.
 
4. FEATURE_HEAP_SMALLER_OVERHEAD == 1
 The overhead per heap block is 8 bytes.  However it's not possible to backup
 the next-block-to-start-searching-for-free-space pointer, so the heap MAY
 become more fragmented, but it MAY NOT -- it depends on the alloc/free
 calling patterns.
 
5. FEATURE_HEAP_SMALLER_OVERHEAD == 0
The overhead per heap block is 12 bytes.  Backing up is possible, so some
 fragmention that otherwise MIGHT occur can be prevented.  There is very little
 performance cost for this, the big expense is the additional 4 bytes of overhead
 per heap block.

===========================================================================*/
/*
Copyright (c) 1997-2012 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary. 
*/
/*===========================================================================

                                 Edit History

$PVCSPath: O:/src/asw/COMMON/vcs/memheap.h_v   1.1   07 Mar 2002 18:48:56   rajeevg  $
$Header: //components/rel/avs.adsp/2.6.1/apr/utils/inc/apr_memmgr_i.h#3 $ $DateTime: 2014/12/26 03:33:20 $ $Author: svutukur $

when       who     what, where, why
--------   ---     --------------------------------------------------------
08/29/12   lkc     Wrapped apr_memmgr with memheap2
05/10/12  rks      memheap2 
03/22/11   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
11/11/10   EBR     Doxygenated File.
03/31/009  sri     amssassert.h is further featurised based on APPS/QDSP6
09/01/004   gr     Deleted the context argument to the debug versions of
                   the memheap functions; the context is no longer used.
11/07/03    gr     More debug support.
09/23/03    gr     Added functions to retrieve information about a heap.
09/17/03    gr     Mainlined FEATURE_HEAP_DEBUG. Added support for storing a
                   filename hash and a line number in the block header.
03/11/03    gr     Added support for a heap-specific locking mechanism. This
                   allows some heaps to be restricted to task-context use,
                   and others to be usable from ISRs.
10/01/01    gr     Added support for some basic heap statistics.
11/17/00   crr     Change stdlib.h to stddef.h for size_t def. Add forward
                     decl for struct apr_memheap_struct.
11/09/00   jct     Match to coding convention, remove of semaphore use, replace
                   with REX critical sections, remove stddef.h inclusion
02/17/99   kjm     Added realloc function.  Minor additions to
                     apr_memheap_struct.  Added giant function descriptions.
11/24/98   kjm     Ported to C-only code for use in phone software from
                     original SubAllocator.h file.
08/22/97   kjm     Original SubAllocator.h file created.
===========================================================================*/
/** @addtogroup utils_memory
@{ */

/* ------------------------------------------------------------------------
** Includes
** ------------------------------------------------------------------------ */
#if defined CUST_H
   #include "customer.h"
#endif
#include "apr_comdef.h"
#ifndef FEATURE_WINCE
#if ((defined (IMAGE_MODEM_PROC)) || (! defined FEATURE_MULTIPROCESSOR) || \
     (defined (FEATURE_BMPOS_QNK)))
//#include "amssassert.h"
#endif
#else

#include "assert.h"
#endif
#include <stddef.h>

/* ------------------------------------------------------------------------
** Defines
** ------------------------------------------------------------------------ */

/** Memory heap Ver 2.0. */
#define MEMHEAP_VERSION 0x0200

/** @cond 
*/

//#define FEATURE_ENABLE_HEAP_PROFILING 


#ifndef FEATURE_HEAP_SMALLER_OVERHEAD
   #define FEATURE_HEAP_SMALLER_OVERHEAD 1
#endif
/** @endcond */

/** Character to which the pad field is set in the block header. This macro
  is useful for catching heap corruption.
*/
#define MEMHEAP_PAD_CHAR 0xaa

/* ------------------------------------------------------------------------
** Types
** ------------------------------------------------------------------------ */

/* Doxygen comments for this struct are in typedef struct apr_memheap_struct */
struct apr_memheap_struct;
/** 
  Called when there is not enough 
  room in the I/O heap to satisfy a request for specified bytes. The function 
  frees up any memory that it can before returning. The request is then 
  tried again. There are no restrictions on what this function does, including 
  memory allocation/deallocation calls. 
  
  Before calling the function, calls to the allocator failed 
  procedure on the I/O heap are disabled. After this function returns, the 
  calls are re-enabled. This disabling does NOT affect other heaps, so if 
  multiple heaps share the same allocator failed procedure, the procedure 
  is to be re-entrant.
   
  @param[in] heap_ptr     Heap on which the allocation is attempted.
  @param[in] request_size Size of the failed request.

  @return
  None.

  @dependencies
  None.
*/
typedef void (*apr_memheap_allocator_failed_proc_type)(
   struct apr_memheap_struct *heap_ptr,
   size_t                  request_size
);

/* Each heap can have its own function that is used to lock the heap and
** free the heap.  mem_lock_fnc_type and mem_free_fnc_type are the types
** of these functions.
*/
/**
  Provides an abstraction so each function can have its own function to 
  lock the heap.

  @param[in] ptr Pointer to what is to be locked.

  @return
  None.

  @dependencies
  None.
*/
typedef void (*apr_memheap_lock_fnc_type)( void * ptr);

/**
  Provides an abstraction so each function can have its own function to 
  free the heap.

  @param[in] ptr Pointer to what is to be freed.

  @return
  None.

  @dependencies
  None.
*/
typedef void (*apr_memheap_free_fnc_type)( void * ptr);

#ifdef APR_MEMHEAP_FEATURE_MEM_DEBUG
typedef PACKED union PACKED_POST
{
	uint32_t debug_index;
	void *caller_ptr;
}apr_memheap_block_header_debug_info;
#endif

/** @brief Header for each memory block allocated. The header describes the 
  properties of the block allocated to the client. Note that the size of this 
  structure must be a multiple of the largest alignment size required by the 
  host CPU.
*/
typedef struct apr_memheap_block_header_struct {
  uint16_t        header_guard;

  unsigned char extra;        /**< Extra bytes at the end of a block. */
  char          free_flag:4;  /**< Flag to indicate if this memory block 
                                   is free. */
  char          last_flag:4;/**< Flag to indicate if this is the last block 
                                   in the allocated section. */
  unsigned long forw_offset; /**< Forward offset. The value of the offset 
                                   includes the size of the header and the 
                                   allocated block. */
#ifdef APR_MEMHEAP_FEATURE_MEM_DEBUG
  apr_memheap_block_header_debug_info header_debug_info;
#ifdef FEATURE_QDSP6
  uint32_t        pad2;
#endif
#endif
} apr_memheap_block_header_type;

typedef struct apr_memheap_block_header_free_struct {
  uint16_t        header_guard;

  unsigned char extra;        /**< Extra bytes at the end of a block. */
  char          free_flag:4;  /**< Flag to indicate if this memory block 
                                   is free. */
  char          last_flag:4;/**< Flag to indicate if this is the last block 
                                   in the allocated section. */
  unsigned long forw_offset; /**< Forward offset. The value of the offset 
                                   includes the size of the header and the 
                                   allocated block. */
} apr_memheap_block_header_free_struct;
/** @brief Used to maintain the information about a heap. This 
  information is used for determining the allocated memory.
*/
#define APR_MEMHEAP2_BIN_COUNT 32

//FreeBlockList implimentation
typedef struct freeBlockList_struct {
   struct apr_memheap_block_header_free_struct freeBlock;
   struct freeBlockList_struct    *nextPtr;
}freeBlockList;

typedef struct _BIN{
  freeBlockList *firstNode;
  freeBlockList *lastNode;
  uint32_t binToUSeForMalloc;
  uint32_t totalNodes;
}binStruct;

typedef struct apr_memheap_struct {
  uint32_t                         magic_num;
  apr_memheap_block_header_type         *first_block;   
  /**< First block in the heap. */
  apr_memheap_block_header_type         *next_block;    
  /**< Next free block in the heap. */
  unsigned long                  total_blocks;  
  /**< Total blocks in the heap. */
  unsigned long                  total_bytes;   
  /**< Total bytes available in the heap. */
  unsigned long                  used_bytes;    
  /**< Amount of bytes in use in the heap. */
  unsigned long                  max_used;      
  /**< Maximum amount that has been used in the heap. */
  unsigned long                  max_request;   
  /**< Maximum amount that has been requested in the heap. */
  apr_memheap_allocator_failed_proc_type fail_fnc_ptr;  
  /**< Pointer to the failed function. */
  apr_memheap_lock_fnc_type              lock_fnc_ptr;
  apr_memheap_free_fnc_type              free_fnc_ptr;
  void  *memheap_crit_sect;
  binStruct BIN[APR_MEMHEAP2_BIN_COUNT];
  uint32_t legacy_check;
#ifdef FEATURE_ENABLE_HEAP_PROFILING
  uint32_t debug_heap_index;
#endif
  uint16_t magic_num_index;
  uint16_t block_header_guard; 

} apr_memheap_type;

#ifdef APR_MEMHEAP_FEATURE_MEM_DEBUG
  typedef struct {
    void  *ptr;
    uint32_t size;
    void *caller_ptr;
  } apr_memheap_alloc_info_type;
#endif

enum {
  kUseLegacyImpl = 0,
  kUseOnlyLLImpl = 1,
  kUseBINsImpl = 2,
};

/* ------------------------------------------------------------------------
** Functions
** ------------------------------------------------------------------------ */

#ifdef __cplusplus
   extern "C"
   {
#endif


/**
  Initializes the I/O heap object and sets up heap_mem_ptr for use with 
  the I/O heap object. 
 
  The heap_mem_ptr parameter may be aligned on any boundary. Beginning bytes 
  are skipped until a paragraph boundary is reached. NULL pointers must not 
  be passed in for heap_mem_ptr. The fail_fnc_ptr parameter may be NULL; 
  in which case, no function is called if apr_memheap_malloc() or apr_memheap_calloc() 
  is about to fail. If fail_fnc_ptr is provided, it is called once and the 
  allocation is attempted again. See apr_memheap_allocator_failed_proc_type() 
  for details.
  
  There is no protection for initializing a heap more than once. If a heap
  is reinitialized, all pointers previously allocated from the heap are
  immediately invalidated and their contents possibly destroyed. If this is 
  the desired behavior, a heap may be initialized more than once.
 
  @param[in] heap_ptr         Pointer to the statically allocated heap 
                              structure.
  @param[in,out] heap_mem_ptr Pointer to the contiguous block of memory used 
                              for this heap.
  @param[in] heap_mem_size    Size in bytes of the memory pointed to by 
                              heap_mem_ptr.
  @param[in] fail_fnc_ptr     Function to call when allocation fails; can be 
                              NULL.
 
  @return
  None.

  @dependencies
  None.
*/
/*lint -sem(apr_memheap_init_heap,1p,2p,2P>=3n) */
void apr_memheap_init_heap(
   apr_memheap_type                 *heap_ptr,
   void                          *heap_mem_ptr,
   unsigned long                  heap_mem_size,
   apr_memheap_allocator_failed_proc_type fail_fnc_ptr
);

/**
  Deinitializes the heap_ptr object only if the heap is in the Reset state.
  Users are responsible for freeing all allocated pointers before calling 
  this function.
  
  @param[in] heap_ptr  Pointer to the heap structure to be deinitialized.
  
  @return
  None.
  
  @dependencies
  None.
*/
void apr_memheap_deinit_heap(
   apr_memheap_type                 *heap_ptr
);

/*===========================================================================
FUNCTION print_memheap_profile_table

DESCRIPTION

===========================================================================*/
#ifdef FEATURE_ENABLE_HEAP_PROFILING
void print_memheap_profile_table(void);
#endif

void print_memheap_free_error_log(void);
/*===========================================================================
FUNCTION apr_memheap_get_random_num
DESCRIPTION

===========================================================================*/
void apr_memheap_get_random_num(void*  random_ptr, int random_len);
/*===========================================================================
  Allocates enough space for elt_count elements each of elt_size bytes
  from the heap and initializes the space to NULL bytes. If
  heap_ptr is NULL, or elt_count or elt_size is 0, the NULL pointer is 
  silently returned.
 
  @param[in] heap_ptr    Pointer to the heap from which to allocate.
  @param[in] elt_count   Number of elements to allocate.
  @param[in] elt_size    Size of each element.
  @param[in] file_name   Name of the file from which apr_memheap_calloc() was called 
                         (only used in Debug mode).
  @param[in] line_number Line number corresponding to the apr_memheap_calloc() call
                         (only used in Debug mode).

  @return
  Returns a pointer to the newly allocated block, or NULL if the block
  could not be allocated.
 
  @dependencies
  heap_ptr must not be NULL. \n
  elt_count must not be 0. \n
  elt_size must not be 0.
*/
/*lint -sem(apr_memheap_calloc,1p,2n>=0&&3n>=0&&(@p==0||@P==2n*3n)) */

void* apr_memheap_calloc(
  apr_memheap_type *heap_ptr,
  size_t         elt_count,
  size_t         elt_size
);

#ifdef APR_MEMHEAP_FEATURE_MEM_DEBUG
/*lint -save -e683 */
   #define  apr_memheap_calloc_debug(heap_ptr, elt_count, elt_size, file_name, line_number)\
      apr_memheap_calloc(heap_ptr,\
                       elt_count,\
                       elt_size)
/*lint -restore */
#endif

/**
  Allocates a block of size bytes from the heap. If heap_ptr is NULL
  or size is 0, the NULL pointer is silently returned.

  @param[in] heap_ptr    Pointer to the heap from which to allocate.
  @param[in] size        Number of bytes to allocate.
  @param[in] file_name   Name of the file from which apr_memheap_malloc() was called 
                         (only used in Debug mode).
  @param[in] line_number Line number corresponding to the apr_memheap_malloc() call 
                         (only used in Debug mode).

  @return
  Returns a pointer to the newly allocated block, or NULL if the block
  could not be allocated.
 
  @dependencies
  heap_ptr must not be NULL. \n
  size must not be 0.
*/
/*lint -sem(apr_memheap_malloc,1p,2n>=0&&(@p==0||@P==2n)) */

void* apr_memheap_malloc(
  apr_memheap_type *heap_ptr,
  size_t         size
);

#ifdef APR_MEMHEAP_FEATURE_MEM_DEBUG
/*lint -save -e683 */
   #define  apr_memheap_malloc_debug(heap_ptr, size, file_name, line_number)\
      apr_memheap_malloc(heap_ptr,\
                       size)
/*lint -restore */
#endif

/*===========================================================================
FUNCTION MEM_REALLOC

===========================================================================*/
/**
  Resizes the ptr block of memory to size bytes while preserving the
  block's contents. 
 
  If the block is shortened, the bytes are discarded from the end. If the block
  is lengthened, the new bytes added are not initialized and will have 
  unrecognizable values. 
 
  This function has the following criteria: \n
  - If heap_ptr is NULL, the contents of ptr are unchanged and the function 
    silently returns NULL. 
  - If ptr is NULL, the function behaves exactly like apr_memheap_malloc(). 
  - If ptr is not NULL and size is 0, the function behaves exactly 
    like apr_memheap_free(). 
 
  If the block cannot be resized (i.e., ptr is not NULL and size is not 0), 
  NULL is returned and the original block is left untouched. If the ptr 
  block is successfully resized and the returned value is different from 
  the ptr value passed in, the old block passed in must be considered 
  deallocated and no longer useable; do NOT use apr_memheap_free() on the old block.  
 
  This function will ASSERT if it can detect a bad pointer or a pointer to a 
  free block within the range of memory managed by heap_ptr. However, 
  detection is not always possible. Passing in a ptr block that is outside 
  the memory managed by heap_ptr results in a silent return of NULL with 
  the contents of ptr unchanged. The function calls apr_memheap_malloc() if it cannot
  increase the block in place, so apr_memheap_allocator_failed_proc_type() WILL 
  be called to increase the block if the heap is out of room.

  @param[in] heap_ptr    Pointer to the heap from which to allocate.
  @param[in] ptr         Pointer to a block previously allocated.
  @param[in] size        Number of bytes to allocate.
  @param[in] file_name   Name of the file from which apr_memheap_realloc() was called 
                         (only used in Debug mode).
  @param[in] line_number Line number corresponding to the apr_memheap_realloc() call 
                         (only used in Debug mode).

  @return
  Returns a pointer to the beginning of the resized block of memory (which
  may be different from ptr), or NULL if the block could not be resized.

  @dependencies
  None. However, read the description thoroughly for how to properly call the 
  function.
*/
/*lint -sem(apr_memheap_realloc,1p,3n>=0&&(@p==0||@P==3n)) */

void *apr_memheap_realloc(
  apr_memheap_type *heap_ptr,
  void          *ptr,
  size_t         size
);

#ifdef APR_MEMHEAP_FEATURE_MEM_DEBUG
/*lint -save -e683 */
   #define  apr_memheap_realloc_debug(heap_ptr, ptr,size, file_name, line_number)\
      apr_memheap_realloc(heap_ptr,\
					   ptr,\
                       size)
/*lint -restore */
#endif
/**
  Deallocates the ptr block of memory. If ptr or heap_ptr is NULL, or
  ptr is outside the range of memory managed by heap_ptr, the function
  call does nothing and is guaranteed to be harmless. This function will
  ASSERT if it can detect an attempt to free an already freed block. 
  However, detection is not always possible.

  @param[in] heap_ptr    Pointer to the heap from which to allocate.
  @param[in] ptr         Pointer to the memory to be freed.
  @param[in] file_name   Name of the file from which apr_memheap_free() was called 
                         (only used in Debug mode).
  @param[in] line_number Line number corresponding to the apr_memheap_free() call 
                         (only used in Debug mode).

  @return
  None.

  @dependencies
  None.
*/
/*lint -sem(apr_memheap_free,1p) */
void apr_memheap_free(
  apr_memheap_type *heap_ptr,
  void          *ptr
);

#ifdef APR_MEMHEAP_FEATURE_MEM_DEBUG
/*lint -save -e683 */
   #define  apr_memheap_free_debug(heap_ptr, ptr, file_name, line_number)\
      apr_memheap_free(heap_ptr,\
					   ptr)
/*lint -restore */
#endif


/**
  Returns the number of allocated bytes, excluding overhead.

  @param[in] heap_ptr Pointer to the heap to be queried.

  @return
  Number of bytes.

  @dependencies
  None.
*/
size_t apr_memheap_used (apr_memheap_type *heap_ptr);


/**
  Returns the number of bytes of overhead, per allocation, for the heap.

  @param[in] heap_ptr Pointer to the heap to be queried.

  @return
  Number of bytes.

  @dependencies
  None.
*/
size_t apr_memheap_overhead (apr_memheap_type *heap_ptr);


/**
  Returns the number of bytes consumed by the allocation and overhead.

  @param[in] heap_ptr Pointer to the heap to be queried.

  @return
  Number of bytes.

  @dependencies
  None.
*/
size_t apr_memheap_consumed (apr_memheap_type *heap_ptr);

/* ------------------------------------------------------------------------
** 
** Memory Heap Debug and Test Routines
**
** ------------------------------------------------------------------------ */

/** 
  Default value is NULL. If this variable is not NULL, a function is called
  whenever an allocation has failed, due to an out-of-heap space condition, 
  and is about to return NULL to the caller.
*/
extern apr_memheap_allocator_failed_proc_type apr_memheap_allocator_failed_hook;

/** @cond
*/
/* Anonymous enum used for keeping tracking of memory. */
enum {
  kBlockFree = 1,/* needed some sapce for checksum in block header so reduced it to 1*/
  kBlockUsed = 0,
  kLastBlock = 1,/* needed some sapce for checksum in block header so reduced it to 1*/
  kMinChunkSize = 16
};
/** @endcond */


/**
  Returns the logical block size of a memory block in the heap.

  @param[in] block_hdr_ptr Pointer to the memory block to be queried.

  @return
  Returns the size (in bytes) of the block, excluding the block header 
  overhead and the unused bytes at the end of the block.
 
  @dependencies
  None.
*/
/*lint -sem(mem_get_block_logical_size,1p) */
unsigned long apr_memheap_get_block_logical_size(
   const apr_memheap_block_header_type *block_hdr_ptr,
   apr_memheap_type *heap_ptr
);

/** @brief Used for walking through the blocks of a specified heap.
*/
typedef struct apr_memheap_block_iterator_struct {
  const apr_memheap_type   *mAllocator;  /**< Pointer to the heap over which 
                                           to be walked. */
  apr_memheap_block_header_type *mBlock;      /**< Current block the iterator is 
                                           iterating over. */
} apr_memheap_block_iterator_type;

/** @brief Used to keep track of the memory heap.
*/
typedef struct apr_memheap_totals_struct {
  unsigned long total_physical_bytes; /**< Total physical bytes in use. */
  unsigned long current_block_count;  /**< Current block count in use. */
  unsigned long used_blocks;          /**< Current blocks in use. */
  unsigned long header_bytes;         /**< Amount of header bytes in use. */
  unsigned long used_bytes;           /**< Amount of bytes in use. */
  unsigned long free_bytes;           /**< Amount of free bytes. */
  unsigned long wasted_bytes;         /**< Amount of extra unallocated 
                                           bytes in use that cannot be 
                                           allocated currently. */
  unsigned long largest_free_block;   /**< Size of the largest free block. */
  unsigned long max_logical_used;     /**< Maximum logical memory amount 
                                           used. */
  unsigned long max_logical_request;  /**< Maximum logical amount requested. */
} apr_memheap_totals_type;


/**
  Initializes apr_memheap_block_iterator_struct to be used for walking the blocks
  in a specified heap.
 
  @param[in,out] block_iter_ptr Pointer to apr_memheap_block_iterator_struct to be 
                                initialized.
  @param[in] heap_ptr           Pointer to the heap this iterator must 
                                iterate over.

  @return
  None.

  @dependencies
  None.
*/
void apr_memheap_block_iterator_init(
   apr_memheap_block_iterator_type *block_iter_ptr,
   const apr_memheap_type          *heap_ptr
);


/**
  Resets a heap block iterator to begin the iteration of the heap blocks from
  the beginning.

  @param[in] block_iter_ptr Pointer to the iterator.

  @return
  None.

  @dependencies
  None.
*/
void apr_memheap_block_iterator_reset(
   apr_memheap_block_iterator_type *block_iter_ptr
     /* The iterator structure to be reset
     */
);

/*===========================================================================
FUNCTION MEM_HEAP_BLOCK_ITERATOR_NEXT

===========================================================================*/
/**
  Returns a memory block header for the next block (or next virtual block)
  in the heap being iterated. 

  The heap being iterated must not be changed during the iteration because 
  the iterator may become lost or return invalid values. However, there 
  is no protection against changing the heap during the iteration.
 
  @param[in,out] block_iter_ptr  Iterator from which to return the next 
                                 iterated block.
  @param[out] out_block_ptr      Pointer to a location where a copy of the 
                                 memory block header is placed. This copy 
                                 describes the returned memory block. 
                                 Parameter is only valid if the function 
                                 returns a nonzero value.
  @param[in] fake_free_coalesced Input flag; 0 = return the next block 
                                 header from the heap exactly as it is; 
                                 nonzero = return the next virtual block 
                                 header from the heap. Virtual block headers 
                                 are created by collapsing all adjacent free 
                                 blocks into one.

  @return
  Nonzero -- Next heap block was returned in out_block successfully. \n
  0 -- No more heap blocks to return.

  @dependencies
  None.
*/
int apr_memheap_block_iterator_next(
   apr_memheap_block_iterator_type *block_iter_ptr,
   apr_memheap_block_header_type        *out_block_ptr,
   int                           fake_free_coalesced
);


/**
  Returns the heap totals. This function is thread safe.
 
  @param[in] heap_ptr Pointer to the heap to be queried.
  @param[out] totals  Pointer to apr_memheap_totals_struct to receive the various
                      heap information.

  @return
  None.

  @dependencies
  The heap must have been initialized previously.
*/
void apr_memheap_get_totals(
   apr_memheap_type  *heap_ptr,
   apr_memheap_totals_type *totals
);


/**
  Sets up the specified heap to use an interrupt's lock/free operation 
  as its locking mechanism.
 
  @param[in] heap_ptr Pointer to the heap to be set up.

  @return
  0 -- Heap is not set up. \n
  1 -- Heap is set up.

  @dependencies
  None.
*/
int
apr_memheap_set_int_lock( apr_memheap_type *heap_ptr );


/**
  Sets up the specified heap to use a task's lock/free operation as its 
  locking mechanism.
 
  @param[in] heap_ptr Pointer to the heap to be set up.

  @return
  0 -- Heap is not set up. \n
  1 -- Heap is set up.

  @dependencies
  None.
*/
int
apr_memheap_set_task_lock( apr_memheap_type *heap_ptr );


/**
  Sets up the specified heap to use no locking. This implies
  that the heap must only be used from the context of one task.

  @param[in] heap_ptr Pointer to the heap to be set up.

  @return
  0 -- Heap is not set up. \n
  1 -- Heap is set up.

  @dependencies
  None.
*/
int
apr_memheap_set_no_lock( apr_memheap_type *heap_ptr );

/** @cond
*/
/**
  Sets up the specified heap to use QUBE Mutex/REX crit_sect/
  WM CriticalSection for its locking mechanism.
 
  @param[in] heap_ptr Pointer to the heap to be set up.

  @return
  0 -- Heap is not set up. \n
  1 -- Heap is set up.

  @dependencies
  None.
*/
int
apr_memheap_set_crit_sect( apr_memheap_type *heap_ptr );
/** @endcond */


/**
  Returns information about the sizes of the largest number of free blocks 
  in the heap.
 
  @param[in] heap_ptr   Pointer to the heap to be queried.
  @param[in] num_blocks Number of blocks to be queried.
  @param[out] buf       Pointer to where the information is returned.

  @return
  None.

  @dependencies
  The heap must have been initialized previously. \n
  The buffer passed in must be large enough to hold the information.
*/
void
apr_memheap_get_freeblock_info(
  apr_memheap_type *heap_ptr,
  unsigned int   num_blocks,
  unsigned int  *buf
);
 
#ifdef APR_MEMHEAP_FEATURE_MEM_DEBUG

/*===========================================================================
FUNCTION MEM_HEAP_GET_ALLOC_INFO

===========================================================================*/
/**
  Returns information about the sizes of the first N allocated blocks in the
  heap.
 
  @param[in] heap_ptr   Pointer to the heap to be queried.
  @param[in] num_blocks Number of blocks to be queried.
  @param[out] buf       Pointer to where the information is returned.

  @return
  None.

  @dependencies
  The heap must have been initialized previously. \n
  The buffer passed in must be large enough to hold the information.
*/
void
apr_memheap_get_alloc_info(
  apr_memheap_type            *heap_ptr,
  unsigned int              num_blocks,
  apr_memheap_alloc_info_type *buf
);

#endif /* APR_MEMHEAP_FEATURE_MEM_DEBUG */


/**
  Returns the minimum chunk size used for allocations from a heap. All
  allocations from a specific heap are multiples of this size.
 
  @param[in] heap_ptr Pointer to the heap to be queried.

  @return
  Minimum chunk size.

  @dependencies
  None.
*/
unsigned int
apr_memheap_get_chunk_size( apr_memheap_type *heap_ptr );

#ifdef __cplusplus
   }
#endif

/** @} */ /* end_addtogroup utils_services */
#endif /* APR_MEMMGR_I_H */
