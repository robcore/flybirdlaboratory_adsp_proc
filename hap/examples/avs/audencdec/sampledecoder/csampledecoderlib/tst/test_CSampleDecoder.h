#ifndef __SAMPLE_TEST_H__
#define __SAMPLE_TEST_H__

/***********************************************************************
 * Include Files
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Elite_CAPI.h"
/***********************************************************************
 * Constant Definitions
 ***********************************************************************/
#define NULL_CHAR           '\0'
#define DFLT_OPEXT        ".raw"  /* default output file name extension */
#define MAX_NAME_SIZE        128  /* Maximum size of file name */
#define BUFFER_SIZE         4096
#define OPBUF_SIZE          4096
#define SAMPLE_SUCCESS      0
 

/***********************************************************************
 * Type Definitions
 ***********************************************************************/



typedef struct
{
		ICAPI                                *pDecoderLib;        //Decoder CAPI
		CAPI_BufList_t                       BitStream;
		CAPI_BufList_t                       PcmData;
}AudioDecSvc_Struct;

#endif /*__SAMPLE_TEST_H__*/
