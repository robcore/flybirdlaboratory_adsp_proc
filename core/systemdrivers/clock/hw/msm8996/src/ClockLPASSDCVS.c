/*
===========================================================================
*/
/**
  @file ClockLPASSDCVS.c 
  
  DCVS NPA node definitions for MSM8996 LPASS clock driver.
*/
/*
  ====================================================================

  Copyright (c) 2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/hw/msm8996/src/ClockLPASSDCVS.c#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $
 
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/13/14   dcf     Created.
 
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "DDIClock.h"
#include "ClockDriver.h"
#include "ClockLPASS.h"
#include "busywait.h"
#include "ClockSWEVT.h"
#include "ClockLPASSHWIO.h"

#include <DALSys.h>
#include <npa.h>
#include <npa_resource.h>
#include <npa_remote.h>
#include <npa_remote_resource.h>


/*=========================================================================
      Macros
==========================================================================*/



/*=========================================================================
      Data
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/


/*
 * Clock_NPALocalResourcesType
 *
 * Structure containing the NPA node and resource data for local nodes.
 *
 *  CPUResource        - CPU resource data - /clk/cpu
 *  CPUNode            - CPU node data     - /node/clk/cpu
 */
typedef struct
{
  npa_resource_definition   CPUResource;
  npa_node_definition       CPUNode;
} Clock_NPAResourcesType;


/*=========================================================================
      Prototypes
==========================================================================*/

npa_resource_state Clock_NPACPUDriverFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState
);

void Clock_CoreCPUAvailableCB 
(
  void        *pContext,
  unsigned int nEventType,
  void        *pNodeName,
  unsigned int nNodeNameSize
);

npa_query_status Clock_NPAResourceQuery
( 
  npa_resource    *resource, 
  unsigned int     id,
  npa_query_type  *result
);


/*=========================================================================
      Data
==========================================================================*/

/*
 * NPA remote resources used on LPASS
 */

static npa_remote_resource_definition Clock_aNPARemoteResources[] =
{
  {
    CLOCK_NPA_RESOURCE_QDSS,
    "clk0\x01\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn, 
    "STATE",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_PNOC,
    "clk1\x00\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn, 
    "KHz",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_SNOC,
    "clk1\x01\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn, 
    "KHz",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_CNOC,
    "clk1\x02\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn, 
    "KHz",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_BIMC,
    "clk2\x00\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn, 
    "KHz",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_AGGR0,
    "aggr\x00\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn,
    "Enable",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_AGGR1,
    "aggr\x01\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn,
    "Enable",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_AGGR2,
    "aggr\x02\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn,
    "Enable",
    NPA_MAX_STATE
  }
};


/*
 * Separate chipset-dependent remote nodes for initialization after 
 * reading the device configuration data for supported chipsets. 
 */

static npa_remote_resource_definition Clock_aOCMEMNPARemoteResources[] =
{
  {
    CLOCK_NPA_RESOURCE_OCMEM,
    "clk2\x02\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn, 
    "KHz",
    NPA_MAX_STATE
  },
};

/*
 * Define the local clock resources.
 */

Clock_NPAResourcesType Clock_NPALocalResources =
{
  /*
   * CPUResource
   */
  {
    "/clk/cpu", 
    "KHz",
    0,  /* Max, fill in later */
    &npa_max_plugin, 
    NPA_RESOURCE_DEFAULT,
    (npa_user_data)NULL,
    Clock_NPAResourceQuery
  },

  /*
   * CPUNode
   */
  { 
    "/node/clk/cpu",          /* name */
    Clock_NPACPUDriverFunc,   /* driver_fcn */
    NPA_NODE_DEFAULT,         /* attributes */
    NULL,                     /* data */
    NPA_EMPTY_ARRAY,
    1, &Clock_NPALocalResources.CPUResource
  }
};


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_InitDCVS
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

DALResult Clock_InitDCVS
(
  ClockDrvCtxt *pDrvCtxt
)
{
  uint32                i;
  uint32                nPL, nConfig;
  npa_resource_state    nInitialRequest;
  ClockPropertyValueType PropVal = NULL;
  ClockNPARemoteNodeSupportType *NPANodeSupport = NULL;
  ClockLPASSCtxtType *pLPASSCtxt = (ClockLPASSCtxtType*)pDrvCtxt->pImageCtxt;
  ClockImageConfigType *pClockLPASSConfig = pLPASSCtxt->pImageConfig;
  ClockNPAResourcePubType *pResourcePub = NULL;


  /*-----------------------------------------------------------------------*/
  /* Get the PLL configurations for this chipset                           */
  /*-----------------------------------------------------------------------*/

  if (DAL_SUCCESS != Clock_GetPropertyValue("NPARemoteNodeSupport", &PropVal))
  {
    DALCLOCK_FREE(pDrvCtxt);
    return(DAL_ERROR);
  }

  NPANodeSupport = (ClockNPARemoteNodeSupportType*)PropVal;

  /*-----------------------------------------------------------------------*/
  /* Create our common remote nodes.                                       */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < SIZEOF_ARRAY(Clock_aNPARemoteResources); i++)
  {
    npa_remote_define_resource(
      &Clock_aNPARemoteResources[i], (npa_resource_state)0, NULL);
  }

  /*-----------------------------------------------------------------------*/
  /* Create our chipset specific remote nodes.                             */
  /*-----------------------------------------------------------------------*/

  if (TRUE == NPANodeSupport->bOCMEM)
  {
    npa_remote_define_resource(
      &Clock_aOCMEMNPARemoteResources[0], (npa_resource_state)0, NULL);
  }

  /*
   * Add additional chipset-based checks here.
   */


  /*-----------------------------------------------------------------------*/
  /* Init the NPA CPU resource/node                                        */
  /*-----------------------------------------------------------------------*/

  Clock_NPALocalResources.CPUNode.data = (npa_user_data)pDrvCtxt;

  nPL     = pClockLPASSConfig->pCPUPerfConfig->nMaxPerfLevel;
  nConfig = pClockLPASSConfig->pCPUPerfConfig->panPerfLevel[nPL];

  Clock_NPALocalResources.CPUResource.max = 
    pClockLPASSConfig->pCPUConfig[nConfig].Mux.nFreqHz / 1000;

  nInitialRequest = 0;

  npa_define_node_cb(&Clock_NPALocalResources.CPUNode, 
                     &nInitialRequest,
                     Clock_CoreCPUAvailableCB,
                     pLPASSCtxt);

  /*-----------------------------------------------------------------------*/
  /* Publish any resources requiring exposure for MPD                      */
  /*-----------------------------------------------------------------------*/

  if (DAL_SUCCESS == Clock_GetPropertyValue("ClockResourcePub", &PropVal))
  {
    pResourcePub = (ClockNPAResourcePubType*)PropVal;

    if ((NULL != pResourcePub) && (pResourcePub->nTotalResources > 0))
    {
      npa_remote_publish_resources(pResourcePub->nDomain, 
                                   pResourcePub->nTotalResources, 
                                   pResourcePub->ppszResourceList);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitDCVS */


/* =========================================================================
**  Function : Clock_EnableDCVS
** =========================================================================*/
/*
  See DDIClock.h
*/ 

DALResult Clock_EnableDCVS
(
  ClockDrvCtxt *pDrvCtxt
) 
{
  //struct npa_resource *pResource;

  /*-----------------------------------------------------------------------*/
  /* Set flag to enable DCVS.                                              */
  /*-----------------------------------------------------------------------*/

  if (pDrvCtxt->bDCVSEnabled)
  {
    return DAL_SUCCESS;
  }

  pDrvCtxt->bDCVSEnabled = TRUE;

  /*
   * No state update triggering here.  We keep Q6 at constant frequency until
   * ADSPPM is ready to request different performance levels.
   */

  return DAL_SUCCESS;

} /* END Clock_EnableDCVS */


/* =========================================================================
**  Function : Clock_GetIntermediateConfig
** =========================================================================*/
/**
  Selects an intermediate config.

  This function selects an intermediate configuration on a different source
  in order to allow a particular source to be reconfigured.

  @param *pDrvCtxt [in] -- Pointer to driver context.
  @param  pCurrentConfig [in] -- The current configuration.

  @return
  DAL_SUCCESS -- Request was successful.
  DAL_ERROR -- Request failed.

  @dependencies
  The clock mutex must be locked.
*/
#if 0
static ClockCPUConfigType *Clock_GetIntermediateConfig
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockMuxConfigType  *pCurrentConfig
)
{
  uint32 nIdx, nTotalConfigs;
  ClockLPASSCtxtType *pLPASSCtxt = (ClockLPASSCtxtType *)pDrvCtxt->pImageCtxt;
  ClockCPUConfigType *pPerf = pLPASSCtxt->pImageConfig->pCPUConfig;

  nTotalConfigs = pLPASSCtxt->pImageConfig->nTotalSupportedConfigs;

  for (nIdx = nTotalConfigs-1; nIdx > 0; nIdx--)
  {
    if ((pPerf[nIdx].Mux.HALConfig.eSource != pCurrentConfig->HALConfig.eSource) &&
        (pPerf[nIdx].Mux.nFreqHz <= pCurrentConfig->nFreqHz))
    {
      return((ClockCPUConfigType*)&pPerf[nIdx]);
    }
  }
  if (nIdx == 0)
  {
    return((ClockCPUConfigType*)&pPerf[0]);
  }

  return(NULL);

} /* Clock_GetIntermediateConfig */
#endif /* 0 */

/* =========================================================================
**  Function : Clock_SetCPUConfigGFMux
** =========================================================================*/
/**
  Set QDSP6 configuration.

  This function sets QDSP6 configuration based on input parameters.
  This configures the Q6 MUX and GFMUX.

  @param *pDrvCtxt [in] -- Pointer to driver context.
  @param  pConfig  [in] -- New configuration.

  @return
  DAL_SUCCESS -- Request was successful.
  DAL_ERROR -- Request failed.

  @dependencies
  The clock mutex must be locked.
*/

static DALResult Clock_SetCPUConfigGFMux
(
  ClockDrvCtxt       *pDrvCtxt,
  ClockCPUConfigType *pConfig
)
{
  DALResult           eResult;
  ClockLPASSCtxtType  *pLPASSCtxt;
  ClockNodeType       *pClock;
  ClockSourceNodeType *pSource;

  /*-----------------------------------------------------------------------*/
  /* Get QDSP6 clock.                                                      */
  /*-----------------------------------------------------------------------*/

  pLPASSCtxt = (ClockLPASSCtxtType *)pDrvCtxt->pImageCtxt;
  pClock = pLPASSCtxt->QDSP6Ctxt.pQDSP6Clock;

  /*-----------------------------------------------------------------------*/
  /* Save domain source                                                    */
  /*-----------------------------------------------------------------------*/

  pSource = pClock->pDomain->pSource;

  /*-----------------------------------------------------------------------*/
  /* Put an extra vote to keep current source ON - we do this since        */
  /* Clock_SetClockConfig could turn OFF current source (if unused), but   */
  /* we want to keep it ON until we switch to GFMUX in HAL_clk_ConfigClock */
  /* function.                                                             */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_EnableSourceInternal(pDrvCtxt, pSource, TRUE);
  if (eResult != DAL_SUCCESS)
  {
    return eResult;
  }

  /*-----------------------------------------------------------------------*/
  /* Switch QDSP6 core clock.                                              */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_SetClockConfig(pDrvCtxt, pClock->pDomain, &pConfig->Mux);
  if (eResult != DAL_SUCCESS)
  {
    return eResult;
  }

  /*-----------------------------------------------------------------------*/
  /* Set QDSP6 core configuration.                                         */
  /*-----------------------------------------------------------------------*/

  HAL_clk_ConfigClock(pClock->HALHandle, pConfig->CoreConfig);

  /*-----------------------------------------------------------------------*/
  /* Releasing our vote for old source.                                    */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_DisableSourceInternal(pDrvCtxt, pSource, TRUE, FALSE);

  if (eResult != DAL_SUCCESS)
  {
    return eResult;
  }

  /*-----------------------------------------------------------------------*/
  /* Update state.                                                         */
  /*-----------------------------------------------------------------------*/

  pLPASSCtxt->QDSP6Ctxt.pCPUConfig = pConfig;

  return DAL_SUCCESS;

} /* END Clock_SetCPUConfigGFMux */


/* =========================================================================
**  Function : Clock_SetQDSP6Config
** =========================================================================*/
/**
  Set QDSP6 configuration.
 
  This function sets QDSP6 configuration based on input parameters.
 
  @param *pDrvCtxt [in] -- Pointer to driver context.
  @param  pConfig  [in] -- New configuration.

  @return
  None.

  @dependencies
  None.
*/ 

void Clock_SetQDSP6Config
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockCPUConfigType  *pConfig
)
{
  ClockLPASSCtxtType *pLPASSCtxt = (ClockLPASSCtxtType *)pDrvCtxt->pImageCtxt;
  uint32 nOldFreqHz, nNewFreqHz;
  ClockNodeType *pClock = pLPASSCtxt->QDSP6Ctxt.pQDSP6Clock;
  DALResult eResult = DAL_ERROR;
  //ClockVRegLevelType nCurrentVdd = 0;
  ClockVRegRequestType VRegRequest;
  ClockMuxConfigType   *pMux, *pPreviousMux;
  ClockCPUConfigType *pPreviousConfig;

  VRegRequest.bSuppressible = pClock->pDomain->VRegRequest.bSuppressible;
  VRegRequest.eVRegLevel = pConfig->Mux.eVRegLevel;
  pPreviousConfig = pLPASSCtxt->QDSP6Ctxt.pCPUConfig;

  /*
   * Nothing to do if the new frequency is the same as the current one.
   */
  if (pConfig == pPreviousConfig)
  {
    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Thread safety.                                                        */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Get old and new frequency values.                                     */
  /*-----------------------------------------------------------------------*/

  nOldFreqHz = pLPASSCtxt->QDSP6Ctxt.pCPUConfig->Mux.nFreqHz;
  nNewFreqHz = pConfig->Mux.nFreqHz;

  /*-----------------------------------------------------------------------*/
  /* Pre-frequency busywait/voltage update                                 */
  /*-----------------------------------------------------------------------*/

  if( nNewFreqHz > nOldFreqHz )
  {
    eResult = Clock_VoltageRequest(pDrvCtxt, &pClock->pDomain->VRegRequest, &VRegRequest);

    if(eResult == DAL_ERROR)
    {
      DALCLOCK_FREE(pDrvCtxt);
      return;
    }

    /*-----------------------------------------------------------------------*/
    /* Pre-frequency STRAP_ACC update                                        */
    /*-----------------------------------------------------------------------*/

    HWIO_OUT(LPASS_QDSP6SS_STRAP_ACC, pConfig->nStrapACCVal);
  }

  /*-------------------------------------------------------------------------*/
  /* Set the clock flag to bypass voltage requests.                          */
  /*------------------------------------------------------------------------ */

  CLOCK_FLAG_SET(pClock->pDomain, DOMAIN_HOLD_VREG_REQUEST);

  /*-----------------------------------------------------------------------*/
  /* If we are switching between levels using the same source A but the    */
  /* configurations of that source A are different then we must switch to  */
  /* a level using a different source B temporarily while we reconfigure   */
  /* source A for the new level.                                           */
  /* The intermediate performanace level must require a voltage <= the MAX */
  /* of our current performance level voltage requirement or the new       */
  /* performance level voltage requirement.                                */
  /*-----------------------------------------------------------------------*/

  pMux = &pConfig->Mux;
  pPreviousMux = &pPreviousConfig->Mux;

  if (pPreviousMux->pSourceFreqConfig != NULL && pMux->pSourceFreqConfig != NULL)
  {
    if ((pPreviousMux->HALConfig.eSource == pMux->HALConfig.eSource) &&
        (pPreviousMux->pSourceFreqConfig->nFreqHz != pMux->pSourceFreqConfig->nFreqHz))
    {
      if(pLPASSCtxt->pImageConfig->pIntermediateCPUConfig != NULL)
      {
        Clock_SetCPUConfigGFMux(pDrvCtxt, pLPASSCtxt->pImageConfig->pIntermediateCPUConfig);
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Switch to the requested configuration.                                */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_SetCPUConfigGFMux(pDrvCtxt, pConfig);
  if (eResult != DAL_SUCCESS)
  {
    DALCLOCK_FREE(pDrvCtxt);

    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Clear the clock flag to allow voltage requests.                       */
  /*---------------------------------------------------------------------- */

  CLOCK_FLAG_CLEAR(pClock->pDomain, DOMAIN_HOLD_VREG_REQUEST);

  /*-----------------------------------------------------------------------*/
  /* Post-frequency busywait/voltage update                                */
  /*-----------------------------------------------------------------------*/

  if(nNewFreqHz < nOldFreqHz )
  {
    /*-----------------------------------------------------------------------*/
    /* Post-frequency STRAP_ACC update                                       */
    /*-----------------------------------------------------------------------*/

    HWIO_OUT(LPASS_QDSP6SS_STRAP_ACC, pConfig->nStrapACCVal);

    eResult = Clock_VoltageRequest(pDrvCtxt, &pClock->pDomain->VRegRequest, &VRegRequest);

    if(eResult == DAL_ERROR)
    {
      DALCLOCK_FREE(pDrvCtxt);
      return;
    }
  }

  Clock_SWEvent(CLOCK_EVENT_FREQ, 1, nNewFreqHz);

  /*-----------------------------------------------------------------------*/
  /* Free.                                                                 */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_FREE(pDrvCtxt);  

} /* END Clock_SetQDSP6Config */


/* =========================================================================
**  Function : Clock_NPACPUDriverFunc
** =========================================================================*/
/**
  NPA node driver function for the CPU (LPASS QDSP6) node.
 
  This function handles minimum frequency requests for the CPU NPA node.  If
  preferred PLL is set, this function will try to use that for the given
  frequency request.  If preferred PLL cannot provide the required frequency,
  any other PLL (as listed in the LPASS BSP data) that satisfies minimum frequency
  request will be selected.
 
  @param *resource [in] -- Pointer to resource whose state changed.
  @param client    [in] -- Client handle that triggered the change.
  @param state     [in] -- New request state.

  @return
  npa_resource_state -- The new active state of the resource.

  @dependencies
  None.
*/ 

npa_resource_state Clock_NPACPUDriverFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
)
{
  uint32 nPL, nConfig, nMinPL, nMaxPL;
  uint32 nMinFreqHz = (uint32)nState * 1000;
  ClockDrvCtxt *pDrvCtxt = (ClockDrvCtxt *)pResource->node->data;
  ClockLPASSCtxtType *pLPASSCtxt = pDrvCtxt->pImageCtxt;
  ClockImageConfigType *pClockLPASSConfig = 
    (ClockImageConfigType*)pLPASSCtxt->pImageConfig;
  ClockCPUConfigType *pCPUConfig = pClockLPASSConfig->pCPUConfig;


  /*-----------------------------------------------------------------------*/
  /* Check if dynamic switching is disabled                                */
  /*-----------------------------------------------------------------------*/

  if (!pDrvCtxt->bDCVSEnabled)
  {
    return pResource->active_state;
  }

  nMinPL = pClockLPASSConfig->pCPUPerfConfig->nMinPerfLevel;
  nMaxPL = pClockLPASSConfig->pCPUPerfConfig->nMaxPerfLevel;

  /*-----------------------------------------------------------------------*/
  /* Find minimum performance level.                                       */
  /*-----------------------------------------------------------------------*/

  if (nState == NPA_MAX_STATE)
  {
    nPL = nMaxPL;
  }
  else
  {
    for (nPL = nMinPL; nPL < nMaxPL; nPL++)
    {
      nConfig = pClockLPASSConfig->pCPUPerfConfig->panPerfLevel[nPL];

      if (pCPUConfig[nConfig].Mux.nFreqHz >= nMinFreqHz)
      {
        break;
      }
    }
  }

  nConfig = pClockLPASSConfig->pCPUPerfConfig->panPerfLevel[nPL];

  /*-----------------------------------------------------------------------*/
  /* Switch the QDSP6FW clock.                                             */
  /*-----------------------------------------------------------------------*/

  Clock_SetQDSP6Config(pDrvCtxt, &pCPUConfig[nConfig]);

  /*-----------------------------------------------------------------------*/
  /* Return new state of this resource.                                    */
  /*-----------------------------------------------------------------------*/

  return pCPUConfig[nConfig].Mux.nFreqHz / 1000;

} /* END Clock_NPACPUDriverFunc */


/* =========================================================================
**  Function : Clock_CoreCPUAvailableCB
** =========================================================================*/
/**
  Callback when a /clk/cpu node is created.
 
  This function is called by the NPA framework when the given /clk/cpu node
  is created.  The creation is delayed until all dependencies are also
  created.
 
  @param *pContext     [in] -- Context passed in npa_define_node_cb
  @param nEventType    [in] -- Zero.
  @param *pNodeName    [in] -- Name of the node being created.
  @param nNodeNameSize [in] -- Length of the name.

  @return
  None.

  @dependencies
  None.
*/ 

void Clock_CoreCPUAvailableCB 
(
  void        *pContext,
  unsigned int nEventType,
  void        *pNodeName,
  unsigned int nNodeNameSize
)
{
  ClockLPASSCtxtType *pLPASSCtxt = (ClockLPASSCtxtType *)pContext;

  /*
   * Create an impulse client for triggering re-aggregation on the CPU resource.
   */
  pLPASSCtxt->QDSP6Ctxt.NPAImpulseHandle = 
      npa_create_sync_client(
        Clock_NPALocalResources.CPUResource.name, "/clock/impulse", NPA_CLIENT_IMPULSE);

  if (pLPASSCtxt->QDSP6Ctxt.NPAImpulseHandle == NULL)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to create NPA sync client for /clock/impulse.");
  }

} /* END Clock_CoreCPUAvailableCB */


/* =========================================================================
**  Function : Clock_NPAResourceQuery
** =========================================================================*/
/**
  NPA resource query function.
 
  This function is called to get a list of supported QDSP6 frequencies.
 
  @param *pResource  [in]  -- Pointer to the resource in question
  @param id         [in]  -- ID of the query.
  @param *result    [out] -- Pointer to the data to be filled by this function.

  @return
  npa_query_status - NPA_QUERY_SUCCESS, if query supported.
                   - NPA_QUERY_UNSUPPORTED_QUERY_ID, if query not supported.

  @dependencies
  None.
*/ 

npa_query_status Clock_NPAResourceQuery
( 
  npa_resource    *pResource, 
  unsigned int     id,
  npa_query_type  *result
)
{
  uint32 nMinPL, nMaxPL, nConfig, nFreqPerfLevel, nVddPerfLevel;
  uint32 nMinFreq = 0;
  uint32 nNumPerfLevels = 0;
  //uint32 nVoltageLevel = 0;
  ClockLPASSCtxtType* pClock_LPASSCtxt = Clock_GetImageCtxt();
  npa_query_status  nStatus  = NPA_QUERY_UNSUPPORTED_QUERY_ID;
  ClockCPUConfigType *pCPUConfig = pClock_LPASSCtxt->pImageConfig->pCPUConfig;
  ClockCPUPerfConfigType *pCPUPerfConfig = NULL;

  /*-----------------------------------------------------------------------*/
  /* Get offset for any performance level requests.                        */
  /*-----------------------------------------------------------------------*/

  nFreqPerfLevel = (id - (uint32)CLOCK_NPA_QUERY_PERF_LEVEL_KHZ);
  nVddPerfLevel = (id - (uint32)CLOCK_NPA_QUERY_PERF_VDD_MV);

  /*-----------------------------------------------------------------------*/
  /* Get a handle to QDSP6 performance data                                */
  /*-----------------------------------------------------------------------*/

  pCPUPerfConfig = pClock_LPASSCtxt->pImageConfig->pCPUPerfConfig;

  if( pCPUPerfConfig != NULL )
  {
    /*
     * Get min and max performance levels of QDSP6
     */
    nMinPL = pCPUPerfConfig->nMinPerfLevel;
    nMaxPL = pCPUPerfConfig->nMaxPerfLevel;
    nNumPerfLevels = nMaxPL - nMinPL + 1;
    nConfig = pCPUPerfConfig->panPerfLevel[nMinPL];
    nMinFreq = pCPUConfig[nConfig].Mux.nFreqHz/1000;

    /* 
     * If this is a performance level indexing request then return the 
     * frequency corresponding to this performance level. 
     */
    if(nFreqPerfLevel < nNumPerfLevels)
    {
      nConfig = pCPUPerfConfig->panPerfLevel[nFreqPerfLevel];
      result->type = NPA_QUERY_TYPE_VALUE;
      result->data.value = pCPUConfig[nConfig].Mux.nFreqHz/1000;
      nStatus = NPA_QUERY_SUCCESS;
    }
    else if((nVddPerfLevel >= CLOCK_NPA_QUERY_PERF_VDD_MV) &&
            (nVddPerfLevel < (CLOCK_NPA_QUERY_PERF_VDD_MV+nNumPerfLevels)))
    {
      //nVoltageLevel = pCPUConfig[nVddPerfLevel].nVDDCPU;
      result->type = NPA_QUERY_TYPE_VALUE;
      result->data.value = pCPUConfig[nConfig].nVDDCPU;
      nStatus = NPA_QUERY_SUCCESS;
    }
  }

  if( nStatus != NPA_QUERY_SUCCESS )
  {
    switch( id )
    {
      /* 
       * Returns the number of performance levels.
       */
      case CLOCK_NPA_QUERY_NUM_PERF_LEVELS:
        result->type = NPA_QUERY_TYPE_VALUE;
        result->data.value = nNumPerfLevels;
        nStatus = NPA_QUERY_SUCCESS;
        break;
    
      /* 
       * Return the minimum frequency in KHz.
       */
      case CLOCK_NPA_QUERY_MIN_FREQ_KHZ:
        result->type = NPA_QUERY_TYPE_VALUE;
        result->data.value = nMinFreq;
        nStatus = NPA_QUERY_SUCCESS;
        break;
    
      default:
        break;
      }
  }

  return nStatus;

} /* END Clock_NPAResourceQuery */


/* =========================================================================
**  Function : Clock_QDSP6TriggerStateUpdate
** =========================================================================*/
/**
  Trigger function to update QDSP6 LPASS states.
 
  This function updates QDSP6 LPASS states (frequencies) and then
  synchronizes them with NPA framework.
 
  @param *pDrvCtxt [in] -- Pointer to the clock driver context.

  @return
  None.

  @dependencies
  None.
*/ 

void Clock_QDSP6TriggerStateUpdate( ClockDrvCtxt *pDrvCtxt )
{
  struct npa_resource *pResource; 

  /*-----------------------------------------------------------------------*/
  /* Get Q6LPASS resource handle.                                          */
  /*-----------------------------------------------------------------------*/

  pResource = Clock_NPALocalResources.CPUResource.handle;
  if (!pResource)
  {
    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Thread safety.                                                        */
  /*-----------------------------------------------------------------------*/

  npa_resource_lock(pResource);

  /*-----------------------------------------------------------------------*/
  /* Trigger Q6LPASS state update.                                         */
  /*-----------------------------------------------------------------------*/

  npa_assign_resource_state(
    pResource,
    Clock_NPACPUDriverFunc(pResource, NULL, pResource->request_state));

  /*-----------------------------------------------------------------------*/
  /* Free.                                                        */
  /*-----------------------------------------------------------------------*/

  npa_resource_unlock(pResource);

}


/* =========================================================================
**  Function : Clock_NPACPUResourceOverwriteActiveState
** =========================================================================*/
/**
  This Function overwrites the CPU resource's active state. It should ONLY
  be invoked during the Sleep sequence when in Single Threaded Mode (STM).

  We invoke this function after directly configuring the CPU without
  going through the NPA. This results in the CPU resource's active state
  being different from the requested state. Upon wake-up, Sleep must make
  an NPA Impulse request which will re-aggregate the CPU requests and
  trigger our driver function.

  @param nState [in] -- Active state of the CPU resource.

  @return
  DAL_SUCCESS -- Resource active state is set. \n
  DAL_ERROR  --  Resource handle is NULL.

  @dependencies
  None.
*/
DALResult Clock_NPACPUResourceOverwriteActiveState
(
  npa_resource_state nState
)
{
  npa_resource *pResource = Clock_NPALocalResources.CPUResource.handle;

  /*-----------------------------------------------------------------------*/
  /* Make sure the node has been created before we attempt to update.      */
  /*-----------------------------------------------------------------------*/

  if (pResource == NULL)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Thread safety.                                                        */
  /*-----------------------------------------------------------------------*/

  npa_resource_lock(pResource);

  /*-----------------------------------------------------------------------*/
  /* Overwrite the active state.                                           */
  /*-----------------------------------------------------------------------*/

  pResource->active_state = nState;

  /*-----------------------------------------------------------------------*/
  /* Free.                                                                 */
  /*-----------------------------------------------------------------------*/

  npa_resource_unlock(pResource);

  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* Clock_NPACPUResourceOverwriteActiveState */


