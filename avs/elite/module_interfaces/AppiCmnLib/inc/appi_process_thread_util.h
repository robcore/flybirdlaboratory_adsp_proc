#ifndef _APPI_PROCESS_THREAD_UTIL_H
#define _APPI_PROCESS_THREAD_UTIL_H
/*===========================================================================

  A library to provide a separate processing thread for APPI modules that
  process in fixed sized frames. This library will provide double buffering
  between the main thread used by the post proc service and a processing
  thread in which one frame of data is processed.

  Copyright (C) 2013 by Qualcomm Technologies, Incorporated. All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/avs.adsp/2.6.1/elite/module_interfaces/AppiCmnLib/inc/appi_process_thread_util.h#3 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
2013/09/05 dg      Created file
===========================================================================*/

#ifndef TST_PROCESS_UTIL
#include "Elite_APPI.h"
#else
#include "tst_process_util.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/* Function signature for the processing function to be called in the separate thread.
 * This function must always take in the frame size amount of data and output the
 * same amount of data.
 */
typedef void (*appi_pu_process_fn_t)(appi_t *_pif,
		const appi_buflist_t* input,
		appi_buflist_t* output);

/* Forward declaration of the process utility structure. */
typedef struct _appi_pu_t appi_pu_t;

/**
  Allocates the memory for the process thread utility object and
  initializes it.

  @param[in] stack_size         Stack size in bytes for the processing function.

  @return
  Pointer to the process utility object if the function executed
  successfully. NULL if there was some error.

  @dependencies
  None.
*/
appi_pu_t *appi_pu_create(uint32_t stack_size);

/**
  Destroys the process thread utility object. After this function
  is called, the pointer to the object no longer points to valid
  memory.

  @param[in] obj_ptr             Pointer to the instance structure.

  @return
  None.

  @dependencies
  None.
*/
void appi_pu_destroy(appi_pu_t *obj_ptr);

/**
  Function called to process the data. This function can take any number of input
  bytes and it will produce the same number of output bytes.

  It is recommended that this function be called periodically with small frame
  sizes (compared to the processing frame size). This will give the background
  thread enough time to keep the buffers full. This will ensure that this function
  takes minimal processing time.

  @param[in] obj_ptr  Pointer to the instance structure.
  @param[in] input    The input buffer pointers.
  @param[out] output   The output buffer pointers.

  @return
  None.

  @dependencies
  None.
*/
ADSPResult appi_pu_process(appi_pu_t *obj_ptr,
		const appi_buflist_t* input,
		appi_buflist_t* output);

/**
  Used to set the function to be called to process data. This function will
  be called in a separate processing thread. It will always be called with
  the specified frame size worth of data per buffer and it has to output
  the same amount of data per buffer. The number of input and output
  buffer may be different.

  @param[in] obj_ptr    Pointer to the instance structure.
  @param[in] module_ptr Pointer to the APPI structure which will be passed
                        as the first argument to the processing function.
  @param[in] fn         Pointer to the processing function.

  @return
  None.

  @dependencies
  The background processing thread should not be running when this function is
  called.
*/
void appi_pu_set_process_function(appi_pu_t *obj_ptr, appi_t *module_ptr, appi_pu_process_fn_t fn);

/**
  This function needs to be called whenever the media type changes. It will
  cause all the buffered data to be dropped.

  @param[in] obj_ptr             Pointer to the instance structure.
  @param[in] frame_size_in_bytes The amount of data passed in per buffer for
                                 each call of the processing function.
  @param[in] num_input_buffers   Number of input buffers to the processing function.
  @param[in] input_channel_map   Array of size num_input_buffers, with each element
                                 containing a unique value that identifies the channel
                                 type of the buffer. Channel types can be any integers,
                                 but they must be unique.
  @param[in] num_output_buffers  Number of output buffers for the processing function.
  @param[in] output_channel_map  Array of size num_output_buffers, with each element
                                 containing a unique value that identifies the channel
                                 type of the buffer. Channel types can be any integers,
                                 but they must be unique.

  @return
  Error code to indicate success or failure.

  @dependencies
  None.
*/
ADSPResult appi_pu_set_media_type(appi_pu_t *obj_ptr,
		uint32_t frame_size_in_bytes,
		uint32_t num_input_buffers,
		const uint8_t input_channel_map[],
		uint32_t num_output_buffers,
		const uint8_t output_channel_map[]);

/**
  Clears all the internal buffers.

  @param[in] obj_ptr             Pointer to the instance structure.

  @return
  None.

  @dependencies
  None.
*/
void appi_pu_reset(appi_pu_t *obj_ptr);

/**
  Blocks the called until the background processing is done. This function
  should be called if some non-reentrant operations are to be performed,
  such as a set param.

  @param[in] obj_ptr             Pointer to the instance structure.

  @return
  None.

  @dependencies
  None.
*/
void appi_pu_wait_for_processing_done(appi_pu_t *obj_ptr);


#if defined(__cplusplus)
} // extern "C"
#endif // __cplusplus

#endif /* _APPI_PROCESS_THREAD_UTIL_H */

