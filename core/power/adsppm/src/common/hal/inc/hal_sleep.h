/*
* Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * hal_sleep.h
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#ifndef HAL_SLEEP_H_
#define HAL_SLEEP_H_


#define HAL_SLEEP_LATENCY_DONT_CARE (-1)


AdsppmStatusType Slp_Init(void);

AdsppmStatusType Slp_RequestLatency(uint32 latency);

AdsppmStatusType Slp_ReleaseLatency(void);

boolean Slp_IsUSleepNpaAvailable(void);

AdsppmStatusType Slp_AllowUSleep(void);

AdsppmStatusType Slp_DisallowUSleep(void);


#endif /* HAL_SLEEP_H_ */

