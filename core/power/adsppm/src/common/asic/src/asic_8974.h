/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * asic_8974.h - contains ASIC configuration definitions required for 8974
 *
 *  Created on: Apr 27, 2012
 *      Author: yrusakov
 */

#ifndef ASIC_8974_H_
#define ASIC_8974_H_

#include "adsppm.h"
#include "asic_internal.h"


Adsppm_Status getBWFromMips_8974(AdsppmMIPSToBWAggregateType *pMipsAggregateData);

Adsppm_Status getClockFromMips_8974(AdsppmMIPSToClockAggregateType *pMipsAggregateData);

Adsppm_Status getClockFromBW_8974(uint32 *pClock, AdsppmBusBWDataIbAbType *pAHBBwData);

Adsppm_Status aggregateBusBW_8974(AdsppmBusBWDataIbAbType *pAggregateBwIbAbValue, AdsppmBusBWDataType *pBwValue);


#endif /* ASIC_8974_H_ */

