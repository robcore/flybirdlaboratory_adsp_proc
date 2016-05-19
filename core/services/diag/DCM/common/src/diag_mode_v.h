#ifndef DIAG_MODE_V_H
#define DIAG_MODE_V_H
/*==========================================================================

              Diag APIs for buffering and streaming modes

General Description
  
Copyright (c) 2014 by QUALCOMM Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

===========================================================================*/

/*===========================================================================

                              Edit History

 $Header: //components/rel/core.adsp/2.6.1/services/diag/DCM/common/src/diag_mode_v.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
04/10/14   sr      Support for peripheral buffering mode 

===========================================================================*/

/* Tx Modes */
#define DIAG_TX_MODE_STREAMING         0    /* Streaming mode (default) */
#define DIAG_TX_MODE_BUFFERED_THRESH   1    /* Threshold buffering mode */
#define DIAG_TX_MODE_BUFFERED_CIR      2    /* Circular buffering mode */
#define DIAG_TX_MODE_INVALID           0xFF /* Invalid mode */
#define DIAG_TX_MODE_LAST              2


/*===========================================================================
FUNCTION DIAG_BUFFERED_MODE_STREAM (internal)

DESCRIPTION
  Checks if we're currently in one of the buffering modes.
  
PARAMETERS
  stream_id - Valid stream IDs are between DIAG_MIN_STREAM_ID and DIAG_MAX_STREAM_ID.
              DIAG_STREAM_ALL for all streams.
  
RETURN VALUE
  TRUE - If we're currently in one of the buffering modes.
  FALSE - Otherwise.
  
===========================================================================*/
boolean diag_buffered_mode_stream( uint8 stream_id );

/*===========================================================================

FUNCTION DIAG_TX_MODE_INIT (internal)

DESCRIPTION
  Initializes global variable for keeping track of streaming mode vs buffering mode.

PARAMETERS
  None
  
RETURN VALUE
  None
  
===========================================================================*/
void diag_tx_mode_init( void );

/*===========================================================================
FUNCTION DIAG_DRAIN_DSM_BUFFER (internal)

DESCRIPTION
  This function drains the buffering DSM pools per stream. 
  
PARAMETERS
  stream_id - stream_id for buffering DSM pool to drain.
              Valid stream IDs are between DIAG_MIN_STREAM_ID and DIAG_MAX_STREAM_ID.
  
RETURN VALUE
  None
  
===========================================================================*/
void diag_drain_dsm_buffer( uint8 stream_id );

/*===========================================================================
FUNCTION diag_buffering_pool_used_cnt (internal)
  
DESCRIPTION
  This function returns the # of DSMs used in the buffering pool for
  each stream.

PARAMETERS
  stream_id - Valid stream IDs are between DIAG_MIN_STREAM_ID and DIAG_MAX_STREAM_ID.
  
RETURN VALUE
  The # of DSMs used in the buffering pool for each stream.
  
===========================================================================*/
uint32 diag_buffering_pool_used_cnt( uint8 stream_id );

/*===========================================================================

FUNCTION DIAG_DRAIN_POOL_CHECK

DESCRIPTION
  Checks whether Diag needs to set signal to drain the DSM pool. Diag should
  signal draining if we're passed the threshold in threshold buffering mode
  or if we're in streaming mode.
  
PARAMETERS
  stream_id - Valid stream IDs are between DIAG_MIN_STREAM_ID and DIAG_MAX_STREAM_ID.
  
RETURN VALUE
  TRUE - Diag can drain the pool now.
  FALSE - Buffering pools are not ready to be drained yet.
  
===========================================================================*/
boolean diag_drain_pool_check( uint8 stream_id );

#endif /*DIAG_MODE_V_H*/
