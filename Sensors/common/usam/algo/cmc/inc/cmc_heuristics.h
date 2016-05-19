#ifndef CMC_HEURISTICS_H
#define CMC_HEURISTICS_H
/*=============================================================================
 Qualcomm Motion Classifier (CMC) heuristics block

 Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.
 =============================================================================*/

/*============================================================================
 * EDIT HISTORY
 *
 * This section contains comments describing changes made to the module.
 * Notice that changes are listed in reverse chronological order.
 *
 * when        who        what, where, why
 * ----------  ---        -----------------------------------------------------
 * 2014-05-26  abhinand   Initial version
 *
 *============================================================================*/

#include "cmc.h"

void cmc_apply_vehicle_entry_logic(cmc_state_s *state);

void cmc_apply_heuristics(cmc_state_s *state, cmc_ms_e motion_state);

void cmc_apply_predating_logic(cmc_state_s* state);

#endif // CMC_HYSTERESIS_H
