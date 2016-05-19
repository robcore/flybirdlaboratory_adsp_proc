#ifndef _I2CSYSTYPES_H_
#define _I2CSYSTYPES_H_
/*=============================================================================

  FILE:   I2cSysTypes.h

  OVERVIEW: This file contains the implementation types for OS Services
            Interface: II2cSys 
 
            Copyright (c) 2014 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary
  ===========================================================================*/
/*=========================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/buses/i2c/src/drv/I2cSysTypes.h#1 $
  $DateTime: 2014/10/16 12:45:40 $$Author: pwbldsvc $

  When     Who    What, where, why
  -------- ---    -----------------------------------------------------------
  03/11/14 LK     Created

  ===========================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "I2cTypes.h"
#include "I2cError.h"
#include "qurt.h"

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/

typedef enum I2CSYS_Error
{
   I2CSYS_ERROR_BASE = I2C_RES_ERROR_CLS_DEV_OS,

   I2CSYS_ERROR_TIMEOUT_EVT_CREATE_FAILED,
   I2CSYS_ERROR_CLIENT_EVT_CREATE_FAILED,

   I2CSYS_ERROR_MEM_FREE_FAILED,
   I2CSYS_ERROR_MEM_MALLOC_FAILED,
   I2CSYS_ERROR_PHYS_MEM_MALLOC_FAILED,
   I2CSYS_ERROR_PHYS_MEM_INFO_FAILED,
   I2CSYS_ERROR_MEM_SET_FAILED,
   I2CSYS_ERROR_TIMEOUT_EVT_CLEAR_FAILED,
   I2CSYS_ERROR_CLIENT_EVT_CLEAR_FAILED,
   I2CSYS_ERROR_EVT_CTRL_FAILED,
   I2CSYS_ERROR_EVT_WAIT_FAILED,
   I2CSYS_ERROR_SYNC_CREATE_FAILED,
   I2CSYS_ERROR_SYNC_DESTROY_FAILED,
   I2CSYS_ERROR_INVALID_HANDLE_TYPE,
   I2CSYS_ERROR_NULL_PTR,

} I2CSYS_Error;


typedef struct I2cSys_EventType
{
   qurt_mutex_t        i2c_mutex;

} I2cSys_EventType;
#define I2CSYS_EVENT_INIT                               \
{                                                       \
   /* .i2c_mutex = */          QURT_MUTEX_INIT          \
}                                                       \

typedef struct I2cSys_SyncType
{
   qurt_mutex_t        i2c_mutex;
} I2cSys_SyncType;
#define I2CSYS_SYNC_INIT                         \
{                                                \
   /* .i2c_mutex = */          QURT_MUTEX_INIT   \
}                                                \


/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/

#endif //_I2CSYSTYPES_H_



