#ifndef GLINK_OS_H
#define GLINK_OS_H

/*===========================================================================

                      G-Link OS Specific types/functions


 Copyright (c) 2008-2013 by QUALCOMM Technologies, Incorporated.  All Rights
 Reserved.
===========================================================================*/


/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/mproc/glink/core/inc/glink_os.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/18/14   bm      Initial version
===========================================================================*/


/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "comdef.h"
#include "string.h"
#include "err.h"
#include "assert.h"
#include "timer.h"  /* Clock services definitions           */
#include "DALFramework.h"

/*===========================================================================
                        MACRO DEFINITIONS
===========================================================================*/

/*===========================================================================
                        TYPE DEFINITIONS
===========================================================================*/
typedef DALSYSSyncObj glink_os_cs_type;

typedef void (*glink_timer_cb_fn)(void* cb_data);

typedef timer_type glink_timer;

/*===========================================================================
                    EXTERNAL FUNCTION DEFINITIONS
===========================================================================*/

/*===========================================================================
FUNCTION      glink_cs_lock

DESCRIPTION   lock/unlock a critical section

PARAMETERS    cs - pointer the the critical section

              lock - lock or unlock the critical section

RETURN VALUE  None.
===========================================================================*/
void glink_cs_lock( void *cs, boolean lock );

/*===========================================================================
FUNCTION      glink_cs_create

DESCRIPTION   Create and initializesa Critical Section

PARAMETERS    None

RETURN VALUE  The critical section.
===========================================================================*/
void *glink_cs_create(void);

/*===========================================================================
FUNCTION      glink_lock_acquire

DESCRIPTION   lock a critical section

PARAMETERS    cs - pointer the the critical section

RETURN VALUE  None.
===========================================================================*/
void glink_lock_acquire( void *cs );

/*===========================================================================
FUNCTION      glink_lock_release

DESCRIPTION   unlock a critical section

PARAMETERS    cs - pointer the the critical section

RETURN VALUE  None.
===========================================================================*/
void glink_lock_release( void *cs );

/*===========================================================================
FUNCTION      glink_cs_init

DESCRIPTION   Initializes a Critical Section

PARAMETERS    cs - pointer to critical section object allocated by caller.

RETURN VALUE  The critical section.
===========================================================================*/
void glink_cs_init(glink_os_cs_type *cs);

/*===========================================================================
FUNCTION      glink_cs_destroy

DESCRIPTION   Destroys a Critical Section

PARAMETERS    None

RETURN VALUE  none.
===========================================================================*/
void glink_cs_destroy( void *cs );

/*===========================================================================
  FUNCTION  glink_malloc
===========================================================================*/
/**
  Dynamically allocate a region of memory from the heap.  The region should be
  freed using \c glink_free when no longer used.

  @param[in]  size   The number of bytes to be allocated.

  @return    The pointer to the region of memory that was allocated.
             NULL if the allocation failed.
*/
/*=========================================================================*/
void *glink_malloc( size_t size );

/*===========================================================================
  FUNCTION  glink_calloc
===========================================================================*/
/**
  Dynamically allocate a region of memory from the heap and initialize with 
  the zeroes.  The region should be freed using \c glink_free 
  when no longer used.

  @param[in]  size   The number of bytes to be allocated.

  @return    The pointer to the region of memory that was allocated.
             NULL if the allocation failed.
*/
/*=========================================================================*/
void *glink_calloc( size_t size );

/*===========================================================================
  FUNCTION  glink_free
===========================================================================*/
/**
  Free a region of memory that was allocated by \c glink_malloc.

  @param[in] pMem    The reference to the region of memory to be freed.

  @return    0 if succesful.
             Negative value if an error occurred.
*/
/*=========================================================================*/
int32 glink_free( void *pMem );

/*===========================================================================
  FUNCTION  glink_string_copy
===========================================================================*/
/**
  Copies the source string into the destination buffer until 
  size is reached, or until a '\0' is encountered.  If valid,
  the destination string will always be NULL deliminated.
  
  @param[in] dst    The destination string, contents will be updated.
  @param[in] src    The source string
  @param[in] size   The maximum copy size (size of dst)

  @return
  The destination string pointer, dst.
*/
/*==========================================================================*/
char *glink_string_copy(char *dst, const char *src, uint32 size);

/*===========================================================================
  FUNCTION  glink_atomic_increment_uint32
===========================================================================*/
/**
  Atomically increment an integer value by 1.

  @param[in/out] ploc    The reference to the location of the integer to be 
                         incremented.

  @return    Incremented value.
*/
/*=========================================================================*/
uint32 glink_atomic_increment_uint32( volatile uint32 *ploc );

/*===========================================================================
  FUNCTION  glink_atomic_decrement_uint32
===========================================================================*/
/**
  Atomically decrement an integer value by 1.

  @param[in/out] ploc    The reference to the location of the integer to be 
                         decremented.

  @return    Decremented value.
*/
/*=========================================================================*/
uint32 glink_atomic_decrement_uint32( volatile uint32 *ploc );

/*===========================================================================
FUNCTION      glink_atomic_exchange_uint32

DESCRIPTION   Swaps the provided value with the value at the given location

PARAMETERS    plocation  - pointer to location holding the value
              new_value  - new value to put at the location

RETURN VALUE  The previous value at the locaiton.
===========================================================================*/
uint32 glink_atomic_exchange_uint32( uint32* plocation, uint32 new_value );

/*===========================================================================
FUNCTION      glink_timer_init

DESCRIPTION   initialized a timer

PARAMETERS    ptimer  - pointer to glink_timer data structure
              cb      - callback to be invoked with timer expiration

RETURN VALUE  TRUE if successfull, FALSE otherwise.
===========================================================================*/
boolean glink_timer_init( glink_timer* ptimer, glink_timer_cb_fn cb, void* cb_data );

/*===========================================================================
FUNCTION      glink_timer_start

DESCRIPTION   Starts a timer with specified duration

PARAMETERS    ptimer    - pointer to glink_timer data structure
              duration  - timer expiry duration in ms

RETURN VALUE  TRUE if successfull, FALSE otherwise.
===========================================================================*/
boolean glink_timer_start( glink_timer* ptimer, uint32 duration );

/*===========================================================================
FUNCTION      glink_timer_stop

DESCRIPTION   Stops timer

PARAMETERS    ptimer    - pointer to glink_timer data structure

RETURN VALUE  none.
===========================================================================*/
void glink_timer_stop( glink_timer* ptimer );

#endif /* GLINK_OS_H */
