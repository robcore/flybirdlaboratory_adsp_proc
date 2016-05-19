/*
* Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * usleepmgr.h
 *
 *  Created on: Jan 30, 2015
 *      Author: ltayleon
 */

#ifndef USLEEPMGR_H_
#define USLEEPMGR_H_


typedef enum
{
    USleepMgr_VoterId_None = 0,
    USleepMgr_VoterId_BusMgr,
    USleepMgr_VoterId_MipsMgr,
    USleepMgr_VoterId_Max,
} USleepMgr_VoterIdType;


Adsppm_Status USleepMgr_Init(void);

Adsppm_Status USleepMgr_ProcessRequest(
    USleepMgr_VoterIdType voterId,
    uint64 ddrAb);


#endif /* USLEEPMGR_H_ */

