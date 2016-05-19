/*
* Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * mipsmgr.h
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#ifndef MIPSMGR_H_
#define MIPSMGR_H_

#include "requestmgr.h"


Adsppm_Status MIPS_Init(void);

Adsppm_Status MIPS_ProcessRequest(coreUtils_Q_Type *pMipsReqQ);


#endif /* MIPSMGR_H_ */

