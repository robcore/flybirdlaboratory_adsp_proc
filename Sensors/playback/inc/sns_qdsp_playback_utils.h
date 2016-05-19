/******************************************************************************
  @file    sns_qdsp_playback_util.h
  @brief   SAM client for QDSP SIM Playback


  ---------------------------------------------------------------------------
  Copyright (c) 2013 Qualcomm Technologies Incorporated. All Rights Reserved. 
  QUALCOMM Proprietary and Confidential.
  ---------------------------------------------------------------------------
 *******************************************************************************/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. 

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2013-11-21  ae   Initial version

============================================================================*/
#include <stdint.h>

#define QDSP_PLAYBACK_SAMPLE_LAST_TICK_DELTA 30 

uint32_t sns_qdsp_sim_low_tick(void);
