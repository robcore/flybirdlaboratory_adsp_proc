/**
@file Main.c

@brief This file contains the user level boot code for LPASS

*/
/*-------------------------------------------------------------------------------------------*/
/* Version information:                                                                      */



/* $Header: //components/rel/dspcore.adsp/2.5/main/src/main.c#26 $    */
/* $DateTime: 2014/11/06 18:32:25 $                                                          */
/* $Author: pwbldsvc $                                                                            */
/*-------------------------------------------------------------------------------------------*/
/*========================================================================
Edit History

when       who     what, where, why
--------   ---     -------------------------------------------------------

07/04/11   mspk    updated the original main.c
==========================================================================*/

/*-----------------------------------------------------------------------
   Copyright (c) 2010 QUALCOMM Technologies, Incorporated.  All Rights Reserved.
   QUALCOMM Proprietary.
-----------------------------------------------------------------------*/

#include <string.h>
#include <errno.h>
#include <stdio.h>
/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================= */
#include "qurt_elite.h"
#include "EliteMain.h"
//#include "DALSys.h"

#include "engg_timestamp.h"
#include "qcom_timestamp.h"
#include "qurt.h"
//#include "npa.h"

/* APR */
#include "aprv2_api_inline.h"
#include "apr_errcodes.h"
#include "aprv2_msg_if.h"
#include "aprv2_api.h"


//#include "icbarb.h"

#if (PLATFORM_INTEGRATION==1)
#include "platform_libs.h"
#endif

#if (SENSORS_INTEGRATION==1)
#include "sensor_pdinit.h"
#endif

#ifdef MALLOC_DEBUG
    #include "dbg_malloc.h"
#endif

#include "sys_m_smsm.h"

#if defined(SIM)
extern void DALSYS_Init(void);
#else // !SIM
extern void coremain_main(void);
#endif // SIM

#if (ADSPSYSMON_INTEGRATION == 1)
//ADSP SysMon integration
#include "sysmon_prof.h"
#endif

extern void __init_stack_chk_guard(void);
ADSPResult wait_forever(void);
#if (SENSORS_INTEGRATION==1)
//extern void sns_init();
//extern int sns_sensors_playback_test(void);
#endif // Sensors

#if (VIDEO_INTEGRATION==1)
extern int video_init(void);
extern int video_deinit(void);
volatile boolean RunVideo = TRUE;
#endif

#if (WLAN_INTEGRATION==1)
extern void wls_init(void);
volatile boolean RunWlan = TRUE;
#endif

#if (LOWI_INTEGRATION==1)
extern void lowi_init(void);
volatile boolean RunLowi = TRUE;
#endif

#if (STRESS_TEST==1)
extern void stress_test_init(void);
volatile boolean RunLatency = TRUE;
#endif

qurt_elite_signal_t global_wait_signal_at_main;
static char Engg_ImageCreationDate[80];
static char Qcom_ImageCreationDate[80];
volatile boolean do_clk_regime_init = TRUE;
volatile boolean do_icbarb_tests    = TRUE;
// OpenDSP run time control
volatile boolean adsptest_cosim_present = FALSE;
volatile boolean RunCoremain = TRUE;
volatile boolean RunAudio = TRUE;
extern const char IMAGE_VARIANT_STRING_AUTO_UPDATED[];
extern const char OEM_IMAGE_VERSION_STRING_AUTO_UPDATED[];
extern const char QC_IMAGE_VERSION_STRING_AUTO_UPDATED[];
extern const char OEM_IMAGE_UUID_STRING_AUTO_UPDATED[];
static char ImageVersionReproting[128];

int SMP2PSTATUS1;
volatile boolean RunSMP2P = TRUE;

#if defined(SIM)
volatile boolean RunSensors = FALSE;
#else
volatile boolean RunSensors = TRUE;
#endif

volatile boolean RunTests = FALSE;

void multi_pd_spawn(void)
{
   qurt_printf("qurt pid is %d\n", qurt_getpid());
   //Audio image names are Macros defined in the scons based on the build rev and other params
   //The User process are spawned based on whether we have both sensor and user pd or just one
#ifdef SPAWN_AUDIO_USERPD
    int cid2=0;
    cid2=qurt_spawn(AUDIO_IMG_NAME);
    qurt_printf("Process Audio launched with ID=%d\n", cid2);
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Process Audio launched with ID=%d\n", cid2);   
#endif
   
}

int main(void)
{

    // initialize stack canary with random number
    // this function calls PrngML_getdata_lite() 
    // which allows init_stack_chk_guard() to run before coremain_main()
#ifndef SIM
    __init_stack_chk_guard();
#endif


#if defined(SIM)
    DALSYS_Init();
#else // !SIM

    if(RunCoremain)
    {
        coremain_main();
    }
#endif // SIM

    // print imageCreationDate to Diag
    strlcpy(Engg_ImageCreationDate,engg_timestampstring,80);
    strlcpy(Qcom_ImageCreationDate,qcom_timestampstring,80);
    qurt_printf("\n**********************************\n* DSP Image Creation Date: %s\n*******************************************************\n",Engg_ImageCreationDate);
    MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "Engineering Image Creation Date: %s\n", Engg_ImageCreationDate);
    MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "Qcom Image Creation Date: %s\n", Qcom_ImageCreationDate);
    // Do Not Remove. Print out the Image Version and UUID to enable the features.
    strlcpy(ImageVersionReproting, IMAGE_VARIANT_STRING_AUTO_UPDATED, 128);
    MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "IMAGE_VARIANT_STRING_AUTO_UPDATED: %s\n", ImageVersionReproting);
    strlcpy(ImageVersionReproting, OEM_IMAGE_VERSION_STRING_AUTO_UPDATED, 128);
    MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "OEM_IMAGE_VERSION_STRING_AUTO_UPDATED: %s\n", ImageVersionReproting);
    strlcpy(ImageVersionReproting, QC_IMAGE_VERSION_STRING_AUTO_UPDATED, 128);	
    MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "QC_IMAGE_VERSION_STRING_AUTO_UPDATED: %s\n", ImageVersionReproting);
    strlcpy(ImageVersionReproting, OEM_IMAGE_UUID_STRING_AUTO_UPDATED, 128);	
    MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "OEM_IMAGE_UUID_STRING_AUTO_UPDATED: %s\n", ImageVersionReproting);

#ifdef SPAWN_AUDIO_USERPD 
    apr_init();
#endif

#if (BAREBONE_ADSP != 1)
	
  #if (PLATFORM_INTEGRATION==1)
    if (0 != pl_init())
    {
        qurt_printf("\n Platform init pl_init() failed \n"); 
        ERR_FATAL("QDSP6 Main.c: pl_init() failed ",0,0,0);
    }
  #endif

  #ifdef SPAWN_AUDIO_USERPD
    multi_pd_spawn();
  #else // don't run elite_framework_init() if Audio is in User PD, AUdio has to init and run from PD
    if (ADSP_EOK != elite_framework_init())
    {
        qurt_printf("\n elite_framework_init() failed \n"); 
        ERR_FATAL("QDSP6 Main.c: elite_framework_init() failed ",0,0,0);
    }
  #endif // SPAWN_AUDIO_USERPD

#if (SENSORS_INTEGRATION==1)    
    if (RunSensors)
    {
	     // multi-pd spawn
        pd_sensor_init();
    }
#endif

#ifdef DALTF_APTTEST_ON
    apttests_daltf_init();
#endif

#if (ADSPSYSMON_INTEGRATION == 1)
    /*
     * ADSP SysMon:
     * 	Starts a thread for sysmon
     * 	Needs header 'sysmon_prof.h'
     */
    sysmon_profiler_init();
#endif

#endif // BAREBONE_ADSP


#if (BAREBONE_ADSP != 1)
#ifndef SPAWN_AUDIO_USERPD // don't run elite_framework_start() if Audio is in User PD, AUdio has to init and run from PD
    if(RunAudio)
    {
        if (ADSP_EOK != elite_framework_start())
        {
#if defined(SIM)
            elite_framework_deinit();
#endif
            qurt_printf("\n elite_framework_start() failed \n"); 
            ERR_FATAL("QDSP6 Main.c: elite_framework_start() failed ",0,0,0);
        }
    }
#endif // SPAWN_AUDIO_USERPD
#if (VIDEO_INTEGRATION==1)
    if (RunVideo)
    {
        video_init();
    }
#endif //video

#if (LOWI_INTEGRATION==1)
	if (RunLowi)
	{
		lowi_init();
	}
#endif //lowi


#if (WLAN_INTEGRATION==1)
    if (RunWlan)
    {
        wls_init();
    }
#endif //wlan

#if (STRESS_TEST==1)
   MSG( MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Initializing stress test");
   if (RunLatency)
   {
	   stress_test_init();
   }
#endif //latency

#ifndef SIM
  #ifndef SPAWN_AUDIO_USERPD 
    // back ground indefinite wait starts
    qurt_elite_channel_t aChannel;
    qurt_elite_channel_init( &aChannel);

    if (ADSP_FAILED( qurt_elite_signal_init( &global_wait_signal_at_main)))
    {
        qurt_printf("\n qurt_elite_signal_init() failed to create signal \n"); 
        ERR_FATAL("QDSP6 Main.c: qurt_elite_signal_init() failed ",0,0,0);
    }
    if (ADSP_FAILED( qurt_elite_channel_add_signal( &aChannel, &global_wait_signal_at_main, 0) ) )
    {
        qurt_printf("\n qurt_elite_channel_add_signal() failed to add signal \n"); 
        ERR_FATAL("QDSP6 Main.c: qurt_elite_channel_add_signal() failed ",0,0,0);
    }
    uint32 unListenerChannelBits = qurt_elite_signal_get_channel_bit(&global_wait_signal_at_main);
  #endif // SPAWN_AUDIO_USERPD
    //IPC INIT HACK
    if ( apr_call( APRV2_CMDID_HACK_INIT_IPC, NULL, 0 ) != APR_EOK )
    {
        qurt_printf("\n APR IPC INIT failed \n"); 
        ERR_FATAL("QDSP6 Main.c: APR IPC INIT failed ",0,0,0);
    }

    // call this smp2p api to be able to set QMI bit
    if (RunSMP2P)
    {
       SMP2PSTATUS1 = 0;
       if (sys_m_smsm_apps_set(SYS_M_SUBSYS2AP_SMSM_ERR_HDL_RDY) != SYS_M_SMP2P_SUCCESS) {
          qurt_printf("main.c: smp2p bit set did not succeed\n");
          MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "main.c: smp2p bit set did not succeed");
          SMP2PSTATUS1=-1;
       }
       else {
          qurt_printf("main.c: smp2p bit set succeed\n");
          MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "main.c: smp2p bit set succeed");
          SMP2PSTATUS1=1;
       }
    }

	
  #ifdef SPAWN_AUDIO_USERPD
    wait_forever();
  #else
   // Block here foreever on target
    (void) qurt_elite_channel_wait(&aChannel, unListenerChannelBits );
  #endif //SPAWN_AUDIO_USERPD

#endif // !SIM

  #ifndef SPAWN_AUDIO_USERPD
   if (ADSP_EOK != elite_framework_stop())
   {
#if defined(SIM)
        elite_framework_deinit();
#endif
        qurt_printf("\n elite_framework_stop() failed \n"); 
        ERR_FATAL("QDSP6 Main.c: elite_framework_stop() failed ",0,0,0);
   }

    if (ADSP_EOK != elite_framework_deinit())
    {
        qurt_printf("\n elite_framework_deinit() failed \n"); 
        ERR_FATAL("QDSP6 Main.c: elite_framework_deinit() failed ",0,0,0);
    }
  #endif // SPAWN_AUDIO_USERPD

#if (VIDEO_INTEGRATION == 1)
    if (ADSP_EOK != video_deinit())
    {
        qurt_printf("\n video_deinit() failed \n"); 
        ERR_FATAL("QDSP6 Main.c: video_deinit() failed ",0,0,0);
    }
#endif


#if (PLATFORM_INTEGRATION==1)
    pl_deinit();
#endif
#endif // BAREBONE_ADSP
    return 0;
}


ADSPResult wait_forever( )
{
#ifndef SIM
   MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADSP enter wait forever status \n");
   while(1) {
   }
   return ADSP_EOK;
#else
   return ADSP_EFAILED;
#endif
}
