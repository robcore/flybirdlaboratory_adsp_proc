/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

              Test Implementation for Diag Interface

GENERAL DESCRIPTION
  Contains main implementation of Diagnostic Services Test Application.

EXTERNALIZED FUNCTIONS
  None

INITIALIZATION AND SEQUENCING REQUIREMENTS
  

Copyright (c) 2013 Qualcomm Technologies Incorporated. 
All Rights Reserved.
Qualcomm Confidential and Proprietary

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/services/diag/diag_lsm_test/src/Diag_LSM_Test_Sensor.c#1 $

when       who    what, where, why
--------   ---     ---------------------------------------------------------- 
03/05/14   xy      Fixed KW issues  
11/27/13   ph      Updated MSG 1.0 API references to MSG.2.0.
02/09/12   sg     Created File
===========================================================================*/
#include <stdio.h>
#include <qurt.h>
#include "event.h"
#include "event_defs.h"
#include "msg.h"
#include "log.h"
#include "Diag_LSM.h" /* For Diag_LSM_Init() and Diag_LSM_DeInit() */
#include "diagpkt.h"
#include "diagcmd.h"

#include "qw.h" /* only to test MSG_TS */
//#include "ts.h" /* for timestamp functions ts_get(), only to test MSG_TS */

/* Global Data */
/* defined this temp struct just for testing logs */
typedef struct
{
  log_hdr_type hdr;    /* Log header (length, code, timestamp) */
  uint32 log_payload;
} shim_log;

/* Subsystem command codes for the test app */
#define DIAG_TEST_APP_F_75            0x0FA0 
#define DIAG_TEST_APP_F_128           0x0FA1
#define DIAG_TEST_APP_F_128_DELAY     0x0FA2 
#define DIAG_TEST_APP_F_75_test       0x0FA3 
#define DIAG_TEST_APP_1_NO_SUBSYS     141

/*=============================================================================*/
/* Local Function declarations */
/*=============================================================================*/

PACKED void * dummy_func_no_subsys (PACKED void *req_pkt,
  uint16 pkt_len);

PACKED void * dummy_func_75 (PACKED void *req_pkt,
  uint16 pkt_len);

PACKED void * dummy_func_128 (PACKED void *req_pkt,
  uint16 pkt_len);

PACKED void * dummy_func_128_delay (PACKED void *req_pkt,
  uint16 pkt_len);

PACKED void * dummy_func_75_test (PACKED void *req_pkt,
  uint16 pkt_len);

/*=============================================================================*/
/* User tables for this client(test app) */
/*=============================================================================*/
/* 141  */
static const diagpkt_user_table_entry_type test_tbl_1[] =
{
  {DIAG_TEST_APP_1_NO_SUBSYS, DIAG_TEST_APP_1_NO_SUBSYS, dummy_func_no_subsys},
};

/*75 18 A0 0F
and
75 18 A3 0F */
static const diagpkt_user_table_entry_type test_tbl_2[] =
{
  {DIAG_TEST_APP_F_75, DIAG_TEST_APP_F_75, dummy_func_75},
  {DIAG_TEST_APP_F_75_test, DIAG_TEST_APP_F_75_test, dummy_func_75_test},
};

/* 128 18 A1 0F 0 0 0 0 0 0 0 0 */
static const diagpkt_user_table_entry_type test_tbl_3[] =
{
  {DIAG_TEST_APP_F_128, DIAG_TEST_APP_F_128, dummy_func_128},
};
/* 128 67 A2 0F 0 0 0 0 0 0 0 0 */
static const diagpkt_user_table_entry_type test_tbl_4[] =
{
  {DIAG_TEST_APP_F_128_DELAY, DIAG_TEST_APP_F_128_DELAY, dummy_func_128_delay},
};
int Diag_LSM_Test_Init(void);
/*=============================================================================*/

/* Main Function. This initializes Diag_LSM, calls the tested APIs and exits. */
int Diag_LSM_Test_Init(void)
{
   boolean bInit_Success = FALSE;
   /* Initialize Diag_LSM in this process space */
   bInit_Success = Diag_LSM_Init(NULL);
   if(!bInit_Success)
   {
     
      return -1;
   }
  

   DIAGPKT_DISPATCH_TABLE_REGISTER (DIAGPKT_NO_SUBSYS_ID, test_tbl_1);
   DIAGPKT_DISPATCH_TABLE_REGISTER (DIAG_SUBSYS_DIAG_SERV, test_tbl_2);
   DIAGPKT_DISPATCH_TABLE_REGISTER_V2 (DIAG_SUBSYS_CMD_VER_2_F,DIAG_SUBSYS_DIAG_SERV, test_tbl_3);
   DIAGPKT_DISPATCH_TABLE_REGISTER_V2_DELAY(DIAG_SUBSYS_CMD_VER_2_F, DIAG_SUBSYS_DIAG_SERV, test_tbl_4);

 return 0;
}

/*=============================================================================*/
/* dummy registered functions */
/*=============================================================================*/
PACKED void * dummy_func_no_subsys (
  PACKED void *req_pkt,
  uint16 pkt_len
)
{
  PACKED void *rsp = NULL;
 
    /* Allocate the same length as the request. */
  rsp = diagpkt_alloc (DIAG_TEST_APP_1_NO_SUBSYS, pkt_len);

  if (rsp != NULL) {
    memcpy ((void *) rsp, (void *) req_pkt, pkt_len);
  }

  return (rsp);
}

/*=============================================================================*/

PACKED void * dummy_func_75 (
  PACKED void *req_pkt,
  uint16 pkt_len
)
{
  PACKED void *rsp = NULL;
   shim_log test_log;
   char event_payload[32] = "DiagTestApp Event with Payload1";
   shim_log* pLog_Test = NULL;
  
   test_log.log_payload = 0x230987;
 
  /* Allocate the same length as the request. */
  rsp = diagpkt_subsys_alloc (DIAG_SUBSYS_DIAG_SERV,DIAG_TEST_APP_F_75, pkt_len);

  if (rsp != NULL) {
    memcpy ((void *) rsp, (void *) req_pkt, pkt_len);

  }
  
	  event_report(EVENT_CAMERA_INVALID_STATE);
	   event_report_payload (EVENT_DIAG_STRESS_TEST_WITH_PAYLOAD,sizeof(event_payload), event_payload);
	   event_report_payload (EVENT_DIAG_STRESS_TEST_WITH_PAYLOAD,sizeof(event_payload), event_payload);

           

	   QSR_MSG(1100110010, MSG_SSID_DIAG, MSG_LEGACY_HIGH, "QSR Message string from TestApp");
           QSR_MSG_1(1100110011, MSG_SSID_DIAG, MSG_LEGACY_HIGH, "QSR Message string from TestApp", 220022);
           QSR_MSG_2(1100110012, MSG_SSID_DIAG, MSG_LEGACY_HIGH, "QSR Message string from TestApp", 220022, 330033);
           QSR_MSG_3(1100110013, MSG_SSID_DIAG, MSG_LEGACY_HIGH, "QSR Message string from TestApp", 220022, 330033, 440044);
           QSR_MSG_4(1100110014, MSG_SSID_DIAG, MSG_LEGACY_HIGH, "QSR Message string from TestApp", 220022, 330033, 440044, 550055);
           QSR_MSG_9(1100110019, MSG_SSID_DIAG, MSG_LEGACY_HIGH, "QSR Message string from TestApp", 110011, 220022, 330033, 440044, 550055, 660066, 770077, 880088, 990099);
	
	   MSG_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH,"HELLO WORLDHIGH %d %d %d",1,2,3);
	
	   //MSG_SPRINTF_1(MSG_SSID_DIAG, MSG_LEGACY_ERROR,"HELLO SPRINTF_1 ERROR %d",1);
	
	   //MSG_SPRINTF_1(MSG_SSID_DIAG, MSG_LEGACY_HIGH,"HELLO SPRINTF_1 HIGH %d",1);
	
	   MSG_1(MSG_SSID_DIAG,MSG_LEGACY_HIGH,"HELLO HIGH1 %d",209387);
	
	   MSG_2(MSG_SSID_DIAG,MSG_LEGACY_HIGH,"HELLO HIGH2 %d %d",209387, 4957);
	   MSG_5(MSG_SSID_DIAG,MSG_LEGACY_HIGH,"HELLO HIGH5 %d %d %d %d %d",1,6,1000,34,209387);
	
	   MSG(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "Test MSG with no arg");
    
	   log_set_code(&test_log, LOG_DIAG_STRESS_TEST_C);
	
	   log_set_length(&test_log, sizeof(shim_log));
	
	   log_set_timestamp(&test_log);
	
	   log_submit(&test_log);
	   pLog_Test = (shim_log*)log_alloc(LOG_WMS_READ_C,sizeof(shim_log));
      if(pLog_Test)
	   log_commit(pLog_Test); 
      pLog_Test = (shim_log*)log_alloc(LOG_WMS_READ_C,sizeof(shim_log));
      if(pLog_Test)
      {   
         log_shorten(pLog_Test, sizeof(shim_log)-2);
         log_commit(pLog_Test); 
      }
	 
	 
  return (rsp);
}

/*=============================================================================*/

/* Note:
Strange why all clients need to define their own struct, all over again..?
Why can't we just put the diagpkt_subsys_hdr_type_v2 etc in some header and let 
clients use it?
*/
typedef struct
{
  uint8 command_code;
  uint8 subsys_id;
  uint16 subsys_cmd_code;
  uint32 status;  
  uint16 delayed_rsp_id;
  uint16 rsp_cnt; /* 0, means one response and 1, means two responses */
}
diagtestapp_subsys_hdr_v2_type;

typedef struct
{
   diagtestapp_subsys_hdr_v2_type hdr;
   char my_rsp[20];
}diagtestapp_delayed_rsp_type; 


PACKED void * dummy_func_128_delay (
  PACKED void *req_pkt,
  uint16 pkt_len
)
{
  PACKED void *rsp = NULL;
  diagtestapp_delayed_rsp_type* p_my_rsp = NULL;
  diagpkt_subsys_delayed_rsp_id_type delay_rsp_id = 0;
  
 
  /* Allocate the length of response. */
  rsp = diagpkt_subsys_alloc_v2(DIAG_SUBSYS_DIAG_SERV,DIAG_TEST_APP_F_128_DELAY, sizeof(diagtestapp_delayed_rsp_type));

  /* Get the delayed_rsp_id that was allocated by diag, to use for the delayed response 
  we're going to send next..
  Doesn't this kind of protocol break encapsulation...??? 
  Also we need to share the delayed_response_id among different processes,
  because this id has to be unique in the system...
  */


  if (rsp != NULL) {
       delay_rsp_id = diagpkt_subsys_get_delayed_rsp_id(rsp);
     /*We cannot just do a memcpy here to loop-back..because even without my_rsp, the size/content of response
     has to be different from the request packet..*/
     char first_resp[]="First response.";
    
     p_my_rsp = (diagtestapp_delayed_rsp_type*) rsp;
     /* Fill in my dummy immediate response. */
     memcpy(p_my_rsp->my_rsp, first_resp,strlen(first_resp));

  
  diagpkt_commit(rsp);

  /* Now work on the dummy delayed response */
  rsp = diagpkt_subsys_alloc_v2_delay (DIAG_SUBSYS_DIAG_SERV,DIAG_TEST_APP_F_128_DELAY, delay_rsp_id, sizeof(diagtestapp_delayed_rsp_type));

  if (rsp != NULL) {
     /* We cannot just do a memcpy here.. */
     char sec_resp[] = "Delayed response.";
	
     diagpkt_subsys_set_rsp_cnt(rsp,1);/* ICD says this means this is the second/final response */
     p_my_rsp = (diagtestapp_delayed_rsp_type*) rsp;
     /* Fill in my dummy delayed response */
     memcpy(p_my_rsp->my_rsp,sec_resp,strlen(sec_resp));
     diagpkt_delay_commit(rsp);
    }
  }
  return NULL;
}

/*=============================================================================*/
PACKED void * dummy_func_75_test (
  PACKED void *req_pkt,
  uint16 pkt_len
)
{
  PACKED void *rsp = NULL;
 
  /* Allocate the same length as the request. */
  rsp = diagpkt_subsys_alloc (DIAG_SUBSYS_DIAG_SERV,DIAG_TEST_APP_F_75_test, pkt_len);

  if (rsp != NULL) {
    memcpy ((void *) rsp, (void *) req_pkt, pkt_len);

  }

  return (rsp);
}

/*=============================================================================*/

PACKED void * dummy_func_128 (
  PACKED void *req_pkt,
  uint16 pkt_len
)
{
  PACKED void *rsp = NULL;

  /* Allocate the same length as the request. */
  rsp = diagpkt_subsys_alloc_v2 (DIAG_SUBSYS_DIAG_SERV,DIAG_TEST_APP_F_128, pkt_len);

  if (rsp != NULL) {
    memcpy ((void *) rsp, (void *) req_pkt, pkt_len);
  }

  return (rsp);
}

