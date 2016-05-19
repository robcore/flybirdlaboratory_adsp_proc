#ifndef ERR_IMG_ADSP_H
#define ERR_IMG_ADSP_H
 
/*===========================================================================

                    Error Handling Service Internal Header File

Description
 
Copyright (c) 2012 by Qualcomm Technologies Incorporated.  All Rights Reserved.

$Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/err_img_adsp.h#1 $
 
===========================================================================*/



#ifndef ERR_IMG_ADSP
#error BAD CONFIGURATION: CHECK DEFINITIONS
#endif

//defines for LPASS
#undef ERR_MASTER
#define FEATURE_ERR_DISABLE_EFS
#define ERR_MSG_PREFIX "LPASS"

#define ERR_DIAG_PROC_ID       DIAG_QDSP6_PROC
#define ERR_DIAG_PROC_BASE     ERR_DIAG_PROC_ADSP

#endif /* ERR_IMG_ADSP_H */
