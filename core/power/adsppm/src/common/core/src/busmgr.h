/*
* Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * busmgr.h
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#ifndef BUSMGR_H_
#define BUSMGR_H_

#include "requestmgr.h"


/**
 * @fn BUS_Init  - bus management init
 */
Adsppm_Status BUS_Init(void);

/**
 * @fn BUS_ProcessRequest  - bus management main function
 */
Adsppm_Status BUS_ProcessRequest(coreUtils_Q_Type *pBWReqQ);


#endif /* BUSMGR_H_ */

