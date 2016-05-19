#ifndef LOG_H
#define LOG_H

/*=============================================================================
 Qualcomm Coarse Motion Classifier (CMC) logging sub-system header file

 Copyright (c) 2013 Qualcomm Technologies Incorporated.  All Rights Reserved.
 QUALCOMM Proprietary and Confidential.
 =============================================================================*/

/*============================================================================
 * EDIT HISTORY
 *
 * This section contains comments describing changes made to the module.
 * Notice that changes are listed in reverse chronological order.
 *
 * when        who  what, where, why
 * ----------  ---  -----------------------------------------------------------
 * 2013-04-08  jayarama   initial version
 *
 *============================================================================*/

#ifdef OFFTARGET_UNIT_TESTING
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...) 
#endif

#endif
