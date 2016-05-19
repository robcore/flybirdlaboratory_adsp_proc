#ifndef USLEEP_QDI_H
#define USLEEP_QDI_H
/*==============================================================================
  FILE:         uSleep_qdi.h

  OVERVIEW:     uSleep QDI Layer Header File

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/uSleep_qdi.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "qurt.h"
#include "qurt_qdi_driver.h"
#include "uSleep.h"
#include "uSleepi.h"

/*==============================================================================
                              DEFINES & TYPES
 =============================================================================*/
/* QDI opener data structure for uSleep */
typedef struct uSleep_qdi_opener_s 
{
  qurt_qdi_obj_t  qdiobj;
}uSleep_qdi_opener;

/* QDI driver name */
#define USLEEP_QDI_DRIVER_NAME "/qdi/uSleep"

/* QDI function options */
#define USLEEP_QDI_EXIT                 (0+QDI_PRIVATE)
#define USLEEP_QDI_SET_CXO              (1+QDI_PRIVATE)

#define USLEEP_QDI_INSERT_CALLBACK      (2+QDI_PRIVATE)
#define USLEEP_QDI_ADD_CALLBACK_LATENCY (3+QDI_PRIVATE)

/*==============================================================================
                            EXTERNAL FUNCTIONS
 =============================================================================*/
/**
 * uSleep_QDIInvoke
 * 
 * @brief Main QDI interface function to invoke user PD function calls 
 *  
 * @return Status from each function call (see functions for values) 
 */
int uSleep_QDIInvoke(int             client_handle,
                     qurt_qdi_obj_t  *pobj,
                     int             method,
                     qurt_qdi_arg_t  a1,
                     qurt_qdi_arg_t  a2,
                     qurt_qdi_arg_t  a3,
                     qurt_qdi_arg_t  a4,
                     qurt_qdi_arg_t  a5,
                     qurt_qdi_arg_t  a6,
                     qurt_qdi_arg_t  a7,
                     qurt_qdi_arg_t  a8,
                     qurt_qdi_arg_t  a9);

/**
 * uSleep_QDIInit
 * 
 * @brief QDI init function for uSleep
 */
void uSleep_QDIInit(void);

/**
 * uSleep_QDIOpen
 * 
 * @brief Main QDI function to open the QDI interface 
 *  
 * @return Handle value or error if negative
 */
int uSleep_QDIOpen(int client_handle, uSleep_qdi_opener *me);

/**
 * uSleep_QDIRelease
 * 
 * @brief Release function for QDI registration.
 * 
 * @note This function should not ever be called since we will never
 *       deregister our QDI interface. However, QDI setup requires a release
 *       function, so it is provided here
 * 
 * @param obj: QDI object to relase 
 */ 
void uSleep_QDIRelease(qurt_qdi_obj_t *obj);

#endif /* USLEEP_QDI_H */

