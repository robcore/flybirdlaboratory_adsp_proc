#ifndef _CAPI_V2_APPI_WRAPPER_H
#define _CAPI_V2_APPI_WRAPPER_H
/*===========================================================================

                  CAPIv2 APPI Wrapper

  A wrapper that can be used to translate APPI to CAPIv2.

  Copyright (C) 2013 by Qualcomm Technologies, Incorporated. All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/avs.adsp/2.6.1/elite/module_interfaces/capi_v2_appi_wrapper/inc/capi_v2_appi_wrapper.h#3 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
2013/11/18 dg      Created file
===========================================================================*/

#include "Elite_CAPI_V2.h"
#include "Elite_APPI.h"


/**
  Returns the size of the wrapper object. The client must allocate this much space in addition
  to the space required for the APPI object.

  @return
  Size of the wrapper object in bytes.

  @dependencies
  None.
*/
uint32_t capi_v2_appi_wrapper_getsize(void);

/**
  Initializes the wrapper object. The client must initialize the APPI object first.

  @param[in] obj_ptr  Instance pointer.
  @param[in] module_ptr  Pointer to the APPI object that is being wrapped. From this point on
                         this object is owned by the wrapper. The end() function for this APPI
                         will be called when the wrapper is destroyed. The memory must still be
                         freed by the client. The client needs to implement a function for
                         any static properties required by CAPIv2.
  @param[in] init_properties The initialization properties to be passed when creating the CAPIv2
                         object.
  @param[in] initial_output_media_format The output media format returned by the APPI from init.

  @return
  Error code indicating success or failure.

  @dependencies
  None.
*/
ADSPResult capi_v2_appi_wrapper_init(capi_v2_t *obj_ptr,
        appi_t* module_ptr,
        capi_v2_proplist_t *init_properties,
        const appi_format_t *initial_output_media_format,
        uint32_t module_id);

#endif /* _CAPI_V2_APPI_WRAPPER_H */

