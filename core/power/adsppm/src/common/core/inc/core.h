/*
* Copyright (c) 2013 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * core.h
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#ifndef CORE_H_
#define CORE_H_

#include "adsppm.h"


/**
 * @fn RM_CreateClient - Create ADSPPM Resource manager's client
 * @param coreId - Core ID which the client is created for
 * @param instanceId - Instance ID which the client is created for
 * @param name - client's name
 * @param callback - Client's callback function pointer
 * @return Client ID for the newly created client
 */
uint32 RM_CreateClient(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, char *name, void *callback, AdsppmClientTypeType clientType);

/**
 * @fn RM_GetClientInfo - returns information about registered client
 * @param clientId - [IN] ID of the client the Info is requested for
 * @param pCoreId - [OUT] Core ID the client was registered for
 * @param callback - [OUT] Callback function registered for the client
 * @return completion status @see Adsppm_Status
 */
Adsppm_Status RM_GetClientInfo(uint32 clientId, AdsppmCoreIdType *pCoreId, uint32 *callback, AdsppmClientTypeType *clientType);

/**
 * @fn RM_DeleteClient - delete client
 * @param clientId - client ID identifying client
 * @return completion status @see Adsppm_Status
 */
Adsppm_Status RM_DeleteClient(uint32 clientId);

/**
 * @fn RM_AddRequest - fill in the client’s request data for the specified resource and mark the request as valid.
 * @param input uint32 clientId - client ID.
 * @param input AdsppmRscIdType resourceId - resource ID that client request.
 * @param input void* pAdsppmReqData - pointer for request data, it'll cast to different data structure based on resource ID.
 * @param input uint32 extData - if non-zero extended data will be updated instead of request data.
 * @return completion code
 */
Adsppm_Status RM_AddRequest(uint32 clientId, AdsppmRscIdType resourceId, void *pAdsppmReqData, uint32 extData);

/**
 * @fn RM_ReleaseRequest - mark request for the client/resource pair as invalid.
 * @param clientId - ID of the client releasing the resource
 * @param resourceId - Resource ID being released
 * @param input uint32 extData - if non-zero extended data will be updated instead of request data.
 * @return completion status @see Adsppm_Status
 */
Adsppm_Status RM_ReleaseRequest(uint32 clientId, AdsppmRscIdType resourceId, uint32 extData);

/**
 * @fn send request to resource managers.
 * @param resourceId - Resource ID the request is made for.
 * @return completion status @see Adsppm_Status
 */
Adsppm_Status RM_RequestResource(AdsppmRscIdType resourceId);

/**
 * @fn AM_AsyncRequest - schedules request for asynchronous execution.
 * @param clientId - client ID obtained during registration with ADSPPM
 * @param rscMap - resource map - a bitmap encoding all the resources requested as a part of this bundle.
 *                 Each bit is 1<<resourceID
 * @param reqTag - user defined identificator of the request.
 * @return completion status @see Adsppm_Status
 */
Adsppm_Status AM_AsyncRequest(uint32 clientId, uint32 rscMap, uint32 reqTag);

/**
 * @fn RM_SetParameter - sets optional configuration parameter for the specific client
 * @param clientId - client ID obtained during registration with ADSPPM
 * @param pParamConfigData - pointer to the parameter configuration data
 * @return completion status @see Adsppm_Status
 */
Adsppm_Status RM_SetParameter(uint32 clientId, AdsppmParameterConfigType *pParamConfigData);

/**
 * @fn RM_GetResourceInfo - get resource information, no need to register client
 * @param rsc_Id - Resource ID the get infor is made for
 * @param pInfo  - the pointer that pointer to information
 */
Adsppm_Status RM_GetResourceInfo(AdsppmRscIdType rsc_Id, void *pInfo, AdsppmInfoType infoType);

/**
 * @fn Core_EnterSleep - Prepare LPASS resources for power collapse.
 * Currently it will just ramp down AHB clock to the lowest possible frequency while still satisfying
 * non-suppressible requests.
 * TODO: Handle the clock gates as well
 * @return completion status
 */
Adsppm_Status Core_EnterSleep(void);

/**
 * @fn Core_ExitSleep - Restore LPASS resources after power collapse.
 * Currently it will just ramp up AHB clock to the pre-PC state.
 * TODO: Handle the clock gates as well
 * @return completion status
 */
Adsppm_Status Core_ExitSleep(void);

/**
 * @fn Core_Init - Initialize all components within ADSPPM Core
 * @return completion status @see Adsppm_Status
 */
Adsppm_Status Core_Init(void);

/**
 * Get register programming speed
 * @param Register Programming Match
 * @return Speed in bytes per sec
 */
uint64 ACMBus_GetRegProgSpeed(AdsppmRegProgMatchType);


#endif /* CORE_H_ */
