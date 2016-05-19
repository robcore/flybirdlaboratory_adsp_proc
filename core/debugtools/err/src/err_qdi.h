/*=============================================================================

                err_qdi.h  --  Header File

GENERAL DESCRIPTION
      ERR QDI Layer Header File

EXTERNAL FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

Copyright (c) 2014
by QUALCOMM Technologies Incorporated.  All Rights Reserved.

=============================================================================*/

/*=============================================================================

                        EDIT HISTORY FOR MODULE

 This section contains comments describing changes made to the module.
 Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/err_qdi.h#1 $ 
$DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
007/31/14   din     File created to support Error on User PD.
=============================================================================*/
#ifndef ERR_QDI_H
#define ERR_QDI_H

#include "qurt_qdi.h"
#include "qurt_qdi_driver.h"
#include "qurt.h"
#include "comdef.h"

#define ERR_DRIVER_NAME                    "/dev/err_qdi_pd"

#define ERR_QDI_SEND_PID_INFO              (0+QDI_PRIVATE)
#define ERR_QDI_INFORM_PFR                 (1+QDI_PRIVATE)
#define ERR_QDI_ERR_HANDLING_DONE          (2+QDI_PRIVATE)


#define ERR_QDI_MAX_PDS                    5
#define ERR_QDI_PFR_LEN                    80
#define ERR_QDI_INITIAL_STRING             "PFR not populated"

typedef struct err_qdi_opener_struct {
  qurt_qdi_obj_t  qdiobj;
  uint32          process_idx;
}err_qdi_opener_s;


typedef struct err_qdi_struct{
  char *          pfr;
  uint32          pfr_len;
  boolean         initialized;
  boolean         err_initiated;
  uint32          pid;
} err_qdi_s;

typedef enum err_qdi_enum {
  ERR_QDI_SUCCESS = 0,
  ERR_QDI_FAIL,
  ERR_QDI_INVALID_PARAMETERS,
  ERR_QDI_NOT_INITIALIZED
}err_qdi_e;



#endif /* ERR_QDI_H */
