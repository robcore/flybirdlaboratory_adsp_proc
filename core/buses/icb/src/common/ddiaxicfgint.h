#ifndef __DDIAXICFGINT_H__
#define __DDIAXICFGINT_H__
/**
 * @file ddiaxicfgint.h
 * @note Internal header file. API for Bus Configuration
 * 
 *                REVISION  HISTORY
 *  
 * This section contains comments describing changes made to this file. Notice
 * that changes are listed in reverse chronological order.
 * 
 * $Header: //components/rel/core.adsp/2.6.1/buses/icb/src/common/ddiaxicfgint.h#1 $ 
 * $DateTime: 2014/10/16 12:45:40 $ 
 * $Author: pwbldsvc $ 
 * 
 * when         who     what, where, why
 * ----------   ---     ---------------------------------------------------
 * 07/12/2013   sds     Add support for BKE thresholding and static configuration.
 * 11/15/2012   sds     Fix handling of RPM msg ids, while consolidating all RPM
 *                      communications in this layer.
 *                      Add support for NAS and proper sleep set usage.
 * 12/05/2011   dj      Created file
 *  
 *  
 * Copyright (c) 2011-2013 by Qualcomm Technologies Incorporated.  All Rights Reserved.
 */ 
#include <stdint.h>
#include <stdbool.h>
#include "icbid.h"
#include "axicfgos.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
  Enums for different function return codes 
 */
typedef enum {
 
  AXICFG_INT_SUCCESS, 
 
  AXICFG_INT_UNSUPPORTED,
  AXICFG_INT_UNINITIALIZED,

  AXICFGINTRETURNCODE_PLACEHOLDER= 0x7FFFFFFF  /**< Forced to extend enum to int32_t size */
} AxiCfgIntReturnCode;

/**
 * Axicfg Initialization Done Marker 
 *  
 * Marker to require as a dependency that indicates that all
 * Axicfg initialization is complete.
 * Axicfg waits on NPA nodes to be present and will create this marker when that is complete.
 */
#define AXICFG_INIT_DONE   "/bus/axicfg/inited"

/**
  @brief  The first method called to initialize AxiCfg driver. 
          Will set up all the required resources including locks, memory maps

  @return bool
      @retval true  if successful
      @retval false if failed or not yet complete

  @post Wait on AXICFG_INIT_DONE marker to know when initialization is complete.
 */
bool AxiCfgInt_Init( void );

/**
  @brief  The method called to reprogram the hardware to default/reset values.

  @return bool
      @retval true  if successful
      @retval false if failed
 */
bool AxiCfgInt_Reset( void );

/**
  @brief Configures the QoS Generator bandwidth for a master.
         Valid only when master QOS mode is either Limited, Regulator, or remote.

  @param[in]  ePort       Master port id
  @param[in]  u64TotalBW  Total aggregated bandwidth value for potential thresholding
  @param[in]  u64ActiveBW QOS generator bandwidth in bytes per second( BpS ) for Active/Next Active
  @param[in]  u64SleepBW  QOS generator bandwidth in bytes per second( BpS ) for Sleep
  @param[in]  bNextActive Boolean indicating that the active request is for next active set

  @return int32_t
        @retval AXICFG_INT_SUCCESS        When successfully configured 
        @retval AXICFG_INT_UNSUPPORTED    When the port is unsupported
        @retval AXICFG_INT_UNINITIALIZED  When the initialization of driver failed
 */
int32_t AxiCfgInt_QoSSetMasterBW
( 
  ICBId_MasterType ePort,
  uint64_t         u64TotalBW,
  uint64_t         u64ActiveBW,
  uint64_t         u64SleepBW,
  bool             bNextActive
);


/**
  @brief Configures the bandwidth for a slave (non-clock).
         Valid only when the slave is remote.

  @param[in]  eSlave      Slave port id
  @param[in]  u64ActiveBW Bandwidth in bytes per second( BpS ) for Active/Next Active
  @param[in]  u64SleepBW  Bandwidth in bytes per second( BpS ) for Sleep
  @param[in]  bNextActive Boolean indicating that the active request is for next active set

  @return int32_t
        @retval AXICFG_INT_SUCCESS        When successfully configured 
        @retval AXICFG_INT_UNSUPPORTED    When the port is unsupported
        @retval AXICFG_INT_UNINITIALIZED  When the initialization of driver failed
 */
int32_t AxiCfgInt_QoSSetSlaveBW
( 
  ICBId_SlaveType eSlave,
  uint64_t        u64ActiveBW,
  uint64_t        u64SleepBW,
  bool            bNextActive
);


/**
  @brief  Used to fetch a value from xml property file in target config lib
          Can only be called after AxiCfgOs_Init

  @param  pString   Name of the property string

  @return uint32_t    Value of the property string
  */
#define AxiCfgInt_GetProperty( pString )  AxiCfgOs_GetProperty( pString )


/**
 @brief Commit all QoS changes to the RPM.

 @param[in] bWait  Indicate to the commit function whether or not
                   to wait for the RPM response.
 */
void AxiCfgInt_Commit( bool bWait );

#ifdef __cplusplus
}
#endif

#endif /* __DDIAXICFGINT_H__ */
