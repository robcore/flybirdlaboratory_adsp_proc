#ifndef ICB_SOC_DATA_H
#define ICB_SOC_DATA_H
/**

@file   icb_soc_data.h

@brief  This module provides the type definitions for ICB SoC specifc data.

===========================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/icb/src/common/icb_soc_data.h#1 $

when         who     what, where, why
----------   ---     --------------------------------------------------------
2014/05/20   sds     Change the hardware base address to a uint8_t*.
2014/02/16   sds     Add port halt/unhalt APIs.
2013/11/25   sds     Add support for configurable aggregation schemes
2013/04/08   sds     Add support for static and dynamic BKE configuration
2012/01/06   sds     Created 

===========================================================================
               Copyright (c) 2012-2014 Qualcomm Technologies Incorporated.
                           All Rights Reserved.
                        QUALCOMM Proprietary/GTDR
===========================================================================
*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "HALbimc.h"
#include "HALnoc.h"
#include "icbid.h"
#include "npa.h"
#include "HALtcsr.h"

/* -----------------------------------------------------------------------
** Definitions
** ----------------------------------------------------------------------- */
#define NOT_INTERLEAVED  0
#define ODD_INTERLEAVED  1
#define EVEN_INTERLEAVED 2

#define SET_SEGMENT(seg,addr,size,inter) \
  [(seg)].uAddr = 0, \
  [(seg)].uMask = 0,

/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */
/* Slave segment definition structure */
typedef struct
{
  uint32_t uAddr;
  uint32_t uMask;
} icb_segment_def_type;

typedef enum
{
  ICB_BUS_BIMC = 0,
  ICB_BUS_NOC,
  ICB_BUS_VIRT,
} icb_bus_type;

typedef enum
{
  /** Default scheme:
   * max(max(IB), sum(AB)/ports)/bus_width */
  ICB_AGG_SCHEME_LEGACY = 0,

  /** Scheme 0:
   * max(sum(AB)*P0, max(IB))/ports/bus_width */
  ICB_AGG_SCHEME_0
} icb_agg_type;

/* Bus definition structure */
typedef struct
{
  char *               pszBaseName;
  bool                 bRemote;
  uint8_t *            pBaseAddr;
  uint32_t             uRegionSize;
  icb_bus_type         busType;
  uint32_t             uAddrWidth;
  uint32_t             uDataWidth;
  void *               pInfo;          /* Expected to be BIMC or NOC info type. */
  uint32_t             uNumCfgClks;    /**< Number of bus config clock clients */
  const char * const * aCfgClkNames;   /**< Array of bus config clock names */
  npa_client_handle  * aCfgClkClients; /**< Array of bus config clock clients */
  uint32_t             uNumEnCfgClks;  /**< Number of enable/disable config clocks  */
  const char * const * aEnCfgClkNames; /**< Array enable/disable config clock names */
  uint32_t           * aEnCfgClkIds;   /**< Array enable/disable config clock ids */
  icb_agg_type         aggType;        /**< Aggregation scheme */
  uint32_t             uP0;            /**< Aggregation scheme parameter 0 */
  uint32_t             uP1;            /**< Aggregation scheme parameter 1 */
} icb_bus_def_type;

/* BIMC bandwidth settings. */
typedef enum
{
  ICB_BW_REQ_TYPE_DEFAULT   = 0,        /**< Dynamic, non-thresholded request. */
  ICB_BW_REQ_TYPE_STATIC    = (1 << 0), /**< Static request. */
  ICB_BW_REQ_TYPE_THRESHOLD = (1 << 1), /**< Thresholded request. */
} icb_bw_req_type;

typedef struct
{
  uint64_t uBandwidth;        /**< Bandwidth requirement in bytes per second */
  uint32_t uThresholdHighPct; /**< Percentage of requested bandwidth to use as high threshold. */
  uint32_t uThresholdMedPct;  /**< Percentage of requested bandwidth to use as medium threshold. */
  uint32_t uThresholdLowPct;  /**< Percentage of requested bandwidth to use as low threshold. */
} icb_bimc_bw_def_type;

/* Master definition structures */
typedef struct
{
  /* Clock gating */
  HAL_bimc_ClockGatingType bimcClockGate;

  /* The type of the request. */
  icb_bw_req_type reqType;

  /* Arbitration mode(s). */
  HAL_bimc_QosModeType bimcMode[2];

  /* Priority definition (if necessary) */
  HAL_bimc_QosPriorityType bimcPriority;

  /* Bandwidth requirement (if necessary) */
  icb_bimc_bw_def_type bimcBandwidth;
  uint64_t             bwThreshold;
} icb_bimc_master_defaults_type;

typedef struct
{
  /* Arbitration mode. */
  HAL_noc_QosModeType  nocMode;

  /* Priority definition (if necessary) */
  HAL_noc_QosPriorityType  nocPriority;

  /* Bandwidth requirement (if necessary) */
  HAL_noc_QosBandwidthType  nocBandwidth;
} icb_noc_master_defaults_type;

typedef struct
{
  ICBId_MasterType  masterId;
  icb_bus_def_type *pBus;
  uint32_t          uNumPorts;
  uint32_t *        pPortIds;
  uint32_t *        pQosPortIds;
  bool              bRemote;
  uint32_t          uWindowSize;
  void *            pDefaults;
  uint32_t *        pHaltPorts;
} icb_master_def_type;

/* Slave definition structures */
typedef struct
{
  /* BIMC only. */
  HAL_bimc_ClockGatingType bimcClockGate;
  bool                     bArbEn;
} icb_bimc_slave_defaults_type;

typedef struct
{
  ICBId_SlaveType   slaveId;
  icb_bus_def_type *pBus;
  uint32_t          uNumPorts;
  uint32_t *        pPortIds;
  bool              bRemote;
  uint32_t          uNumSegments;
  void *            pDefaults;
} icb_slave_def_type;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ICB_SOC_DATA_H */
