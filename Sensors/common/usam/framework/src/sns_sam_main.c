/*============================================================================
  @file sns_sam.c

  @brief
  Implementation of the Sensors Algorithm Manager Framework.

  Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include "sns_init.h"
#include "sns_common.h"
#include "sns_debug_str.h"
#include "sns_em.h"
#include "sns_osa.h"
#include "sns_sam.h"
#include "sns_sam_algo_api.h"
#include "sns_sam_req.h"
#include "sns_sam_reg.h"
#include "sns_sam_init.h"
#include "sns_sam_client.h"
#include "sns_sam_service.h"
#include "sns_sam_resp.h"
#include "sns_sam_ind.h"
#include "sns_sam_cb.h"
#include "sns_sam_memmgr.h"
#include "sns_sam_pm.h"
#include "sns_profiling.h"
#include "sns_sam_algo_gpio.h"

/*============================================================================
  Static Data
  ===========================================================================*/

/* SAM task stack */
static OS_STK sns_sam_task_stk[SNS_SAM_MODULE_STK_SIZE] SNS_SAM_UIMAGE_DATA;

/* mutex to protect setting of snsLowMemSigBusy */
STATIC OS_EVENT *snsSamLowMemSigMutex SNS_SAM_UIMAGE_DATA;

/**
 * Low memory signal busy flag. Set to true when there's existing signal without
 * getting handled yet
 */
STATIC bool snsLowMemSigBusy SNS_SAM_UIMAGE_DATA = false;

/*============================================================================
  Global Data
  ===========================================================================*/

sns_proc_type_e_v01 localProcessor SNS_SAM_UIMAGE_DATA = SNS_SAM_PROCESSOR_TYPE;

/* SAM event signal */
OS_FLAG_GRP *sns_sam_sig_event SNS_SAM_UIMAGE_DATA;

sns_debug_module_id_e samModule SNS_SAM_UIMAGE_DATA = SNS_SAM_DBG_MOD;

sns_q_s algoInstQ SNS_SAM_UIMAGE_DATA;
sns_q_s sensorQ SNS_SAM_UIMAGE_DATA;

/*============================================================================
  Static Function Definitions
  ===========================================================================*/

/**
 * If input argument is true, sending out all batched output. If not, drop output
 */
SNS_SAM_UIMAGE_CODE void
sns_sam_send_batched_output( bool sendOutput )
{
  sns_q_link_s *qCurrAI, *qCurrCR;
  for( qCurrAI = sns_q_check( &algoInstQ ); NULL != qCurrAI;
       qCurrAI = sns_q_next( &algoInstQ, qCurrAI ) )
  {
    sns_sam_algo_inst *algoInst = (sns_sam_algo_inst*)qCurrAI;

    for( qCurrCR = sns_q_check( &algoInst->clientRequests ); NULL != qCurrCR;
         qCurrCR = sns_q_next( &algoInst->clientRequests, qCurrCR ) )
    {
      sam_client_req *clientReq = (sam_client_req*)qCurrCR;

      if( true == sendOutput )
      {
        //Sending out all the existing output
        if( 0 != clientReq->batchPeriod )
      {
        sns_sam_handle_batch_send_ind( clientReq );
        sns_sam_register_client_timer( clientReq );
      }
      else if( SNS_SAM_REPORT_MODE_ASYNC == clientReq->clientAttr.reportMode &&
               clientReq->missedEvent )
      {
        sns_sam_handle_report( clientReq );
        clientReq->missedEvent = false;
        }
      }
      else
      {
        //Dropping all the output
        if( 0 != clientReq->batchPeriod )
        {
          clientReq->nextBatchTS += sns_sam_pm_ap_suspend()
          ? sns_em_convert_sec_in_q16_to_localtick( clientReq->batchPeriod )
          : sns_em_convert_sec_in_q16_to_localtick( clientReq->batchPeriodActive );

          while( 0 != sns_q_cnt( &clientReq->outputDataQ ) )
          {
            sns_sam_algo_output *curr = (sns_sam_algo_output*)sns_q_get( &clientReq->outputDataQ );
            SNS_SAM_IO_MEM_FREE( curr );
          }
          sns_sam_register_client_timer( clientReq );
        }
        sns_sam_prune_output_head( algoInst );
      }
    }
  }
}

/**
 * Handle an event from PM where the AP processor state transitions between
 * suspend and awake.
 */
void
sns_sam_handle_pm_event( void )
{
  if( !sns_sam_pm_ap_suspend() )
  {
    sns_sam_send_batched_output(true);
  }
}

/**
 * Check if there's any wakeup sensor client existing
 */
bool
sns_sam_any_wakeup_sensor(void)
{
  sns_q_link_s *qCurrAI, *qCurrCR;
  for( qCurrAI = sns_q_check( &algoInstQ ); NULL != qCurrAI;
       qCurrAI = sns_q_next( &algoInstQ, qCurrAI ) )
  {
    sns_sam_algo_inst *algoInst = (sns_sam_algo_inst*)qCurrAI;
    for( qCurrCR = sns_q_check( &algoInst->clientRequests ); NULL != qCurrCR;
         qCurrCR = sns_q_next( &algoInst->clientRequests, qCurrCR ) )
    {
      sam_client_req *clientReq = (sam_client_req*)qCurrCR;
      if( SNS_PROC_APPS_V01 == clientReq->clientAttr.notifySuspend.proc_type &&
            clientReq->clientAttr.notifySuspend.send_indications_during_suspend )
      {
        SNS_PRINTF_STRING_LOW_3( samModule,
          "found a wakeup sensor! AlgoInst sensorUID %x, batchedPeriod %x, clientReq sensorUID %x",
          algoInst->algorithm->sensor.sensorUID, clientReq->batchPeriod, clientReq->algorithm->sensor.sensorUID );
        return true;
      }
    }
}
  SNS_PRINTF_STRING_LOW_0( samModule,
    "no wakeup sensor found" );
  return false;
}


/**
 * Handle an event from sensors memmgr that low memory state is detected
 */
SNS_SAM_UIMAGE_CODE void
sns_sam_handle_sensors_heap_lowmem_event( void )
{
  uint8_t os_err;
  bool lowMemStateBusy;

  sns_os_mutex_pend(snsSamLowMemSigMutex, 0, &os_err);
  SNS_ASSERT(OS_ERR_NONE == os_err);
  lowMemStateBusy = snsLowMemSigBusy;
  os_err = sns_os_mutex_post(snsSamLowMemSigMutex);
  SNS_ASSERT(OS_ERR_NONE == os_err);

  if(lowMemStateBusy)
  {
    sns_sam_uimage_exit(SNS_SAM_UIMAGE_BLOCK_SAM_BUSY);

    SNS_PRINTF_STRING_HIGH_1( samModule,
      "handle_sensors_heap_lowmem_event ap_suspend %d",  sns_sam_pm_ap_suspend());

    if( !sns_sam_pm_ap_suspend() || sns_sam_any_wakeup_sensor() )
    {
      SNS_PRINTF_STRING_LOW_0( samModule,
        "sending out batched output due to low memory status detected" );
      sns_sam_send_batched_output(true);
    }
    else
    {
      SNS_PRINTF_STRING_LOW_0( samModule,
        "dropping batched output due to low memory status detected" );
      sns_sam_send_batched_output(false);
    }

    sns_os_mutex_pend(snsSamLowMemSigMutex, 0, &os_err);
    SNS_ASSERT(OS_ERR_NONE == os_err);
    snsLowMemSigBusy = false;
    os_err = sns_os_mutex_post(snsSamLowMemSigMutex);
    SNS_ASSERT(OS_ERR_NONE == os_err);
    SNS_PRINTF_STRING_LOW_0( samModule,
      "done with sending out batched ind due to low memory status detected" );

    sns_sam_uimage_vote_enter(SNS_SAM_UIMAGE_BLOCK_SAM_BUSY);

  }
}

/**
* Callback function for Apps suspend/wakeup
*/
SNS_SAM_UIMAGE_CODE static void sns_sam_sensors_heap_lowmem_cb( void )
{
  uint8_t os_err;

  if(!snsLowMemSigBusy)
  {
    SNS_PRINTF_STRING_LOW_0(SNS_SAM_DBG_MOD, "lowMemSig idle, post the sig");

    sns_os_mutex_pend(snsSamLowMemSigMutex, 0, &os_err);
    SNS_ASSERT(OS_ERR_NONE == os_err);
    snsLowMemSigBusy = true;
    os_err = sns_os_mutex_post(snsSamLowMemSigMutex);
    SNS_ASSERT(OS_ERR_NONE == os_err);

    sns_os_sigs_post( sns_sam_sig_event, SNS_SAM_LOWMEM_CB_SIG,
        OS_FLAG_SET, &os_err );
    SNS_ASSERT( OS_ERR_NONE == os_err );

  }
}

/**
 * The SAM Framework thread.
 *
 * @param[i] argPtr Not used
 */
SNS_SAM_UIMAGE_CODE void
sns_usam_task( void *argPtr )
{
  UNREFERENCED_PARAMETER(argPtr);
  uint8_t errOS;
  OS_FLAGS sigFlags;
  OS_FLAGS sam_sig_mask = SNS_SAM_SIGNAL_MASK;
  sns_sam_err errSAM;

  errSAM = sns_sam_pm_init();
  SNS_ASSERT( SAM_ENONE == errSAM );
  errSAM = sns_sam_init_fw();
  SNS_ASSERT( SAM_ENONE == errSAM );
  errSAM = sns_sam_init_algos();
  SNS_ASSERT( SAM_ENONE == errSAM );

  sns_sam_init_gpio();

  sns_init_done();

  sns_sam_pm_enter_sleep();

  for( ;; )
  {
    sns_profiling_log_qdss(SNS_SAM_EXIT, 0);

    sigFlags = sns_os_sigs_pend( sns_sam_sig_event, sam_sig_mask,
      OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &errOS );
    sns_profiling_log_qdss( SNS_SAM_ENTER, 1, sigFlags );
    SNS_ASSERT( OS_ERR_NONE == errOS );

    if( sigFlags & SNS_SAM_LOWMEM_CB_SIG )
    {
      sns_sam_handle_sensors_heap_lowmem_event();
    }
    // PEND: Register a callback with PM to set this signal
    if( sigFlags & SNS_SAM_PM_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
      sns_sam_handle_pm_event();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
    }

    if( sigFlags & SNS_SAM_ALGO_TIMER_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_ALGO );
      sns_sam_handle_algo_timer();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_ALGO );
    }

    if( sigFlags & SNS_SAM_REQ_MSG_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_MSG );
      sns_sam_process_req_q();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_MSG );
    }

    if( sigFlags & SNS_SAM_RESP_MSG_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_MSG );
      sns_sam_process_resp_q();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_MSG );
    }

    if( sigFlags & SNS_SAM_REPORT_TIMER_SIG )
    {
      sns_sam_handle_report_timer();
    }

    if( sigFlags & SNS_SAM_BATCH_TIMER_SIG )
    {
      sns_sam_handle_batch_timer();
    }

    if( sigFlags & SNS_SAM_DC_TIMER_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_TIMER );
      sns_sam_handle_dc_timer();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_TIMER );
    }

    if( sigFlags & SNS_SAM_REG_INIT_TIMER_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_TIMER );
      sns_sam_handle_reg_timeout();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_TIMER );
    }

    if( sigFlags & SNS_SAM_CLIENT_INIT_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
      sns_sam_init_clients();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
    }

    if( sigFlags & SNS_SAM_CLIENT_ERROR_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
      sns_sam_process_error_q();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
    }

    if( sigFlags & SNS_SAM_SVC_RESUME_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
      sns_sam_process_resume_q();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
    }

    if( sigFlags & SNS_SAM_SVC_DISC_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
      sns_sam_process_disc_q();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
    }

    if( sigFlags & SNS_SAM_CLIENT_RELEASE_SIG )
    {
      sns_sam_uimage_exit( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
      sns_sam_process_release_q();
      sns_sam_uimage_vote_enter( SNS_SAM_UIMAGE_BLOCK_SAM_BUSY );
    }

    if ( sigFlags & SNS_SAM_IND_MSG_SIG )
    {
      sns_sam_process_ind_q();
    }

    //Reset the SAM MIPS vote based on Queue count after processing all signals
    sns_sam_pm_adjust_mips( );
  }
}

/*============================================================================
  Public Function Definitions
  ===========================================================================*/

sns_sam_sensor*
sns_sam_lookup_sensor_from_suid( sns_sam_sensor_uid const *sensorUID )
{
  sns_q_link_s *qCurr;

  for( qCurr = sns_q_check( &sensorQ ); NULL != qCurr;
       qCurr = sns_q_next( &sensorQ, qCurr ) )
  {
    sns_sam_sensor *sensor = (sns_sam_sensor*)qCurr;

    if( *sensorUID == sensor->sensorUID )
    {
      return sensor;
    }
  }

  return NULL;
}

sns_sam_sensor_algo*
sns_sam_lookup_algo( sns_sam_sensor_uid const *sensorUID )
{
  sns_q_link_s *qCurr;
  sns_sam_sensor_algo *algo = NULL;

  for( qCurr = sns_q_check( &sensorQ ); NULL != qCurr;
       qCurr = sns_q_next( &sensorQ, qCurr ) )
  {
    algo = (sns_sam_sensor_algo*)qCurr;

    if( !algo->sensor.isLocal )
    {
      break;
    }
    else if( *sensorUID == algo->sensor.sensorUID )
    {
      return algo;
    }
  }

  return NULL;
}

sns_sam_err
sns_sam_init_sensor( sns_sam_sensor **sensor )
{
  uint32_t i;

  sns_sam_sensor *sensorOut = SNS_OS_U_MALLOC( SNS_SAM_DBG_MOD,
    sizeof(sns_sam_sensor));
  SNS_ASSERT(NULL != sensorOut); // Assert if we run out of mem during initialization

  sensorOut->sensorUID = 0;
  sensorOut->sensorLocation = localProcessor; // As good of a default as any
  sensorOut->isAvailable = false;
  sensorOut->isLocal = false;
  sensorOut->sensorReq.clientHndl = NULL;
  sensorOut->sensorReq.sensor = sensorOut;

  for( i = 0; i < SAM_ALGO_ATTR_CNT; i++ )
  {
    sensorOut->attributes[ i ].attribute = i;
    sensorOut->attributes[ i ].supported = false;
  }

  *sensor = sensorOut;

  sns_q_link( sensorOut, (sns_q_link_s*)sensorOut );
  sns_q_put( &sensorQ, (sns_q_link_s*)sensorOut );

  return SAM_ENONE;
}

uint32_t
sns_sam_enable_req_size( sns_sam_sensor_uid const *sensorUID )
{
  UNREFERENCED_PARAMETER(sensorUID);
  static uint32_t maxSize = 1500;
  // PEND: This could be implemented to look-up the actual request message size
  return maxSize;
}

/**
 * SAM Framework initialization.  Called by the Sensors module initializer.
 *
 * @return SNS_SUCCESS
 *         SNS_ERR_FAILED Failure to create signal event or SAM task
 */
sns_err_code_e
sns_usam_init( void )
{
  uint8_t errOS;

  SNS_PRINTF_STRING_LOW_0( samModule, "sns_sam_init" );

  sns_sam_sig_event = sns_os_sigs_create(
    (OS_FLAGS)SNS_SAM_SVC_RESUME_SIG, &errOS );
  SNS_ASSERT( NULL != sns_sam_sig_event );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_REPORT_TIMER_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_REG_INIT_TIMER_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_CLIENT_INIT_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_CLIENT_ERROR_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_DC_TIMER_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_BATCH_TIMER_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_REQ_MSG_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_RESP_MSG_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_IND_MSG_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_PM_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_ALGO_TIMER_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_LOWMEM_CB_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_SVC_DISC_SIG );
  sns_os_sigs_add( sns_sam_sig_event, SNS_SAM_CLIENT_RELEASE_SIG );

  snsSamLowMemSigMutex = sns_os_mutex_create_uimg(0, &errOS);
  sns_memmgr_lowmem_cb_register( sns_sam_sensors_heap_lowmem_cb, SNS_SENSORS_HEAP_TYPE );

  errOS = sns_os_task_create_ext( sns_usam_task, NULL,
      &sns_sam_task_stk[ SNS_SAM_MODULE_STK_SIZE - 1 ], SNS_SAM_MODULE_PRIORITY,
      SNS_SAM_MODULE_PRIORITY, &sns_sam_task_stk[0], SNS_SAM_MODULE_STK_SIZE,
      (void *)0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_ISLAND,
      (uint8_t*)("SNS_USAM") );

  SNS_ASSERT( OS_ERR_NONE == errOS );
  return SNS_SUCCESS;
}
