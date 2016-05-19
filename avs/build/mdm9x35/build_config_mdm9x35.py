#===============================================================================
#
# AVS build configuration
#
# GENERAL DESCRIPTION
#    AVS build configuration for different chipsets & AVSTest must be specified here.
#
#    set in the AVS image scons script file.
#       1) A normal library with symbols - no need specify it
#       2) A stub library  USES_<LIB NAME IN CAPITAL CASE>_STUB
#       3) A stripped library USES_<LIB NAME IN CAPITAL CASE>_STRIP
#
# Copyright (c) 2013 Qualcomm Technologies, Inc.  All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/avs.adsp/2.6.1/build/mdm9x35/build_config_mdm9x35.py#3 $
#  $DateTime: 2014/12/26 03:33:20 $
#  $Author: svutukur $
#  $Change: 7198050 $
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
# 09/21/12   kk      Build configuration
# 04/18/13   nr      Stub out ultrasound stream manager for 8x10 and 9x25
#
#===============================================================================


def chipset_specific_build_config(env):
    env.Replace(USES_DTS =False)
    env.Replace(USES_MIDI =False)

    shared_lib_dict={}
    
    if env.get('AVS_TEST') == True:
        env.Append(CFLAGS='-DADSP_TEST_ENTRY -DSIM -DSIM_DEFINED')
        env.Replace(USES_DTS =True)
        env.Replace(USES_MIDI =True)
        import re
        temp=env.get('CC_DFLAGS')
        yy = re.sub('-DASSERT=ASSERT_FATAL','',temp)
        env.Replace(CC_DFLAGS=yy)

        #Stubbing out DTS for SIM builds
        if env.get('USES_DTS') == True:
            env.Replace(USES_DTSMODULE_STUB = True)
        #Stubbing out dts:hpx
        env.Replace(USES_DTS_HPX_MODULE_STUB = True)

        env.Replace(USES_DOLBYPLUS_ENCODER_STUB = True)
        env.Replace(USES_DS2AP_MODULE_STUB =  True)
        env.Replace(USES_MS12DOLBYPULSEDECODERMODULE_STUB = True)
        env.Replace(USES_AFEVFRDRIVER_V1_STUB = True)
        env.Replace(USES_AFEVFRDRIVER_V2_STUB = True)
        #env.Replace(USES_AFEVFRDRIVER_V3_STUB = True)
        #env.Replace(USES_LPASSTIMESTAMPLIB_STUB = True)

    else:

   
        env.Replace(USES_MIDI =False)
        env.Replace(USES_DTS =True)
        env.Replace(USES_DTS_HPX_MODULE_STUB = True)

        #Add AVS Voice Library Types for this image
        env.Replace(USES_SAMPLE_SLIP_STRIP = True)
        #env.Replace(USES_RSBY2_STRIP = True)
        #env.Replace(USES_IIR_FILTER_STRIP = True)
        #env.Replace(USES_FIR_FILTER_STRIP = True)
        #env.Replace(USES_CTM_STRIP = True)
        #env.Replace(USES_CROSS_FADE_STRIP = True)
        #env.Replace(USES_CNG_STRIP = True)
        #env.Replace(USES_VFE_FILTERS_STRIP = True)
        #env.Replace(USES_TTY_STRIP = True)
        #env.Replace(USES_VOCODER_AMRWB_STRIP = True)
        #env.Replace(USES_VOCODER_AMRNB_STRIP = True)
        #env.Replace(USES_VOCODER_FR_STRIP = True)
        #env.Replace(USES_VOCODER_FOURGV_STRIP = True)
        #env.Replace(USES_VOCODER_EVRC_STRIP = True)
        #env.Replace(USES_VOCODER_EFR_STRIP = True)
        env.Replace(USES_VOCODER_EAMR_STRIP = True)
        #env.Replace(USES_VOCODER_CAPI_STRIP = True)
        #env.Replace(USES_VOLUME_CONTROL_STRIP = True)
        #env.Replace(USES_VOICE_RESAMPLER_STRIP = True)
        #env.Replace(USES_VOCODER_V13K_STRIP = True)
        #env.Replace(USES_VOCODER_HR_STRIP = True)
        #env.Replace(USES_VOCODER_G729AB_STRIP = True)
        #env.Replace(USES_VOCODER_G711_STRIP = True)

        # Add AVS Afe Library Types for this image
        #env.Replace(USES_ADAP_ANC_STRIP =True)
        #env.Replace(USES_FFSPKRPROT_STRIP=True)
        #env.Replace(USES_POP_SUPPRESSOR_STRIP=True)
        #env.Replace(USES_DTMFGENERATION_STRIP=True)
        #env.Replace(USES_REMOVECLICKLIB_STRIP=True)
        #env.Replace(USES_AFERIVADRIVER_STRIP=True)
        #env.Replace(USES_AFESLIMBUSDRIVER_STRIP=True)
        env.Replace(USES_AFEVFRDRIVER_V1_STUB = True)
        env.Replace(USES_AFEVFRDRIVER_V2_STUB = True)
        #env.Replace(USES_AFEVFRDRIVER_V3_STUB = True)
        #env.Replace(USES_LPASSTIMESTAMPLIB_STUB = True)

        #Add AVS Audio Library Types for this image
        if env.get('USES_MDM9X35_VOCODER') == True:

            env.Replace(USES_MBDRCAppi24Bit_STUB=True)
            #env.Replace(USES_DTMFGENERATION_STRIP=True)
            env.Replace(USES_AFECODECDRIVER_STUB = True)
            env.Replace(USES_AFERIVADRIVER_STUB = True)
            env.Replace(USES_AFERTPROXYDRIVER_STUB = True)
            env.Replace(USES_AFESLIMBUSDRIVER_STUB = True)
            env.Replace(USES_DML_HAL_STUB = True)
            env.Replace(USES_RS_DRIVER_STUB = True)
            env.Replace(USES_SSR_HAL_STUB = True)
            env.Replace(USES_AFESWMAD_ALGO_STUB = True)
            env.Replace(USES_AFESWMAD_FWK_STUB = True)
            env.Replace(USES_ADAP_ANC_STUB =True)
            env.Replace(USES_FBSPKRPROT_STUB = True)
            env.Replace(USES_FFSPKRPROT_STUB = True)
            env.Replace(USES_REMOVECLICKLIB_STUB = True)
            env.Replace(USES_AFESPDIFDRIVER_STUB = True)
            env.Replace(USES_AFEHDMIINPUTDRIVER_STUB = True)
            env.Replace(USES_AFEDMAMANAGER_STUB = True)

            #Add AVS Listen Library Types for this image
            env.Replace(USES_VOICEWAKEUPMODULE_STUB = True)
            env.Replace(USES_VOICEWAKEUPV2MODULE_STUB = True)
            env.Replace(USES_SVA_CMN_LIB_STUB = True)
            env.Replace(USES_LISTEN_FEATURE_EXTRACTION_STUB = True)
            env.Replace(USES_LISTEN_PROC_SVC_STUB = True)
            env.Replace(USES_LISTEN_SIGNAL_PROCESSING_STUB = True)
            env.Replace(USES_LISTEN_STREAM_MGR_STUB = True)

            env.Replace(USES_AUDIO_STREAM_MGR_STUB=True)
            env.Replace(USES_AUDIO_DEV_MGR_STUB=True)
            env.Replace(USES_AVCS_STUB=True)
            env.Replace(USES_AUDIO_PROC_SVC_STUB=True)
            env.Replace(USES_SLOW_TALK_STUB = True)
            env.Replace(USES_WIDE_VOICE_STUB = True)
            env.Replace(USES_WIDE_VOICE_V2_STUB = True)
            env.Replace(USES_VFE_FILTERS_STUB = True)
            env.Replace(USES_QUARTET_STUB = True)
            env.Replace(USES_IIR_FILTER_STUB = True)
            env.Replace(USES_FLUENCE_VOICEPLUS_STUB = True)
            env.Replace(USES_FIR_FILTER_STUB = True)
            env.Replace(USES_ECHO_CANCELLER_STUB = True)
            env.Replace(USES_DTMF_DETECT_STUB = True)
            env.Replace(USES_RVE_STUB = True)
            env.Replace(USES_AVC_TX_STUB = True)
            env.Replace(USES_AVC_RX_STUB = True)
            env.Replace(USES_TIME_WARPING_STUB = True)
            env.Replace(USES_VOCODER_G729AB_STUB = True)
            env.Replace(USES_VOCODER_G711_STUB = True)
            env.Replace(USES_CNG_STUB = True)
            env.Replace(USES_EANSMODULE_STUB = True)
            env.Replace(USES_MBDRCMODULE_STUB = True)
            env.Replace(USES_PBEMODULE_STUB = True)
            env.Replace(USES_RESAMPLERMODULE_STUB = True)
            env.Replace(USES_CDRCLIB_STUB = True)
            env.Replace(USES_AIGMODULE_STUB = True)
            env.Replace(USES_FILTERMODULE_STUB = True)
        else:
    # Add AVS Afe Library Types for this image
            env.Replace(USES_AFESWMAD_ALGO_STUB = True)
            env.Replace(USES_AFESWMAD_FWK_STUB = True)
            env.Replace(USES_AFERIVADRIVER_STUB = True)
            env.Replace(USES_FBSPKRPROT_STUB = True)
            env.Replace(USES_DML_HAL_STUB = True)
            env.Replace(USES_RS_DRIVER_STUB = True)
            env.Replace(USES_AFESPDIFDRIVER_STUB = True)
            env.Replace(USES_AFEHDMIINPUTDRIVER_STUB = True)
            env.Replace(USES_AFEDMAMANAGER_STUB = True)
            env.Replace(USES_SP_V2_STUB =True)


            #Add AVS Listen Library Types for this image
            env.Replace(USES_VOICEWAKEUPMODULE_STUB = True)
            env.Replace(USES_VOICEWAKEUPV2MODULE_STUB = True)
            env.Replace(USES_SVA_CMN_LIB_STUB = True)
            env.Replace(USES_LISTEN_FEATURE_EXTRACTION_STUB = True)
            env.Replace(USES_LISTEN_PROC_SVC_STUB = True)
            env.Replace(USES_LISTEN_SIGNAL_PROCESSING_STUB = True)
            env.Replace(USES_LISTEN_STREAM_MGR_STUB = True)
            env.Replace(USES_SLOW_TALK_STRIP = True)
            env.Replace(USES_WIDE_VOICE_STRIP = True)
            env.Replace(USES_WIDE_VOICE_V2_STRIP = True)
            env.Replace(USES_VFE_FILTERS_STRIP = True)
            env.Replace(USES_QUARTET_STRIP = True)
            env.Replace(USES_IIR_FILTER_STRIP = True)
            env.Replace(USES_FLUENCE_VOICEPLUS_STRIP = True)
            env.Replace(USES_FIR_FILTER_STRIP = True)
            env.Replace(USES_ECHO_CANCELLER_STRIP = True)
            env.Replace(USES_DTMF_DETECT_STRIP = True)
            env.Replace(USES_RVE_STRIP = True)
            env.Replace(USES_AVC_TX_STRIP = True)
            env.Replace(USES_AVC_RX_STRIP = True)
            env.Replace(USES_TIME_WARPING_STRIP = True)
            env.Replace(USES_VOCODER_G729AB_STRIP = True)
            env.Replace(USES_VOCODER_G711_STRIP = True)
            env.Replace(USES_CNG_STRIP = True)

        env.Replace(USES_ALACDECODERMODULE_STUB= True)  
        env.Replace(USES_AACDECODERMODULE_STUB=True)
        #env.Replace(USES_ETSIBITBUFFLIB_STUB=True)
        #env.Replace(USES_ETSIFFRLIB_STUB=True)
        #env.Replace(USES_ETSIOPLIB_STUB=True)
        env.Replace(USES_ETSIEAACPLUSENCODERMODULE_STUB=True)
        env.Replace(USES_ADPCMDECODERMODULE_STUB=True)
        env.Replace(USES_ADPCMENCODERMODULE_STUB=True)
        #env.Replace(USES_AMRBITBUFFERLIB_STUB=True)
        #env.Replace(USES_AMRCORELIB_STUB=True)
        #env.Replace(USES_AMRMATHLIB_STUB=True)
        #env.Replace(USES_ETSIAMROPLIB_STUB=True)
        env.Replace(USES_ETSIAMRWBPLUSDECMODULE_STUB=True)
        env.Replace(USES_FLACDECODERMODULE_STUB=True)
        env.Replace(USES_COMBOMP3DECODERMODULE_STUB=True)
        env.Replace(USES_HPMP3DECODERMODULE_STUB=True)
        env.Replace(USES_MP3DECODERMODULE_STUB=True)
        env.Replace(USES_HPMP2DECODERMODULE_STUB=True)
        env.Replace(USES_MP3ENCODERMODULE_STUB=True)
        env.Replace(USES_SBCENCODERMODULE_STUB=True)
        env.Replace(USES_WMAPRODECODERMODULE_STUB=True)
        env.Replace(USES_WMASTDDECODERMODULE_STUB=True)
        env.Replace(USES_WMASTDV8ENCODERMODULE_STUB=True)
        env.Replace(USES_DOLBYMOBILEMODULE_STUB = True)
        env.Replace(USES_DOLBYPULSEDECODERMODULE_STUB = True)
        env.Replace(USES_DOLBYSURROUNDMODULE_STUB = True)
        env.Replace(USES_AC3PACKETIZERMODULE_STUB = True)
        env.Replace(USES_VORBISDECODERMODULE_STUB = True)
        env.Replace(USES_CSPECTRUMANALYZERLIB_STUB = True)
        if env.get('USES_DTS') == True:
            env.Replace(USES_DTSMODULE_STUB = True)
        env.Replace(USES_SRSTRUMEDIAMODULE_STUB=True)
        env.Replace(USES_EAC3PACKETIZERMODULE_STUB=True)
        env.Replace(USES_GENERICDEPACKETIZERMODULE_STUB=True)
        env.Replace(USES_PASSTHRUFORMATTERMODULE_STUB=True)
        env.Replace(USES_ULTRASOUND_STREAM_MGR_STUB=True)
        env.Replace(USES_DOLBYPLUS_ENCODER_STUB = True)
        env.Replace(USES_AFEHDMIINPUTDRIVER_STUB = True)
        env.Replace(USES_AFEDMAMANAGER_STUB = True)
        env.Replace(USES_SRSSS3DMODULE_STUB = True)
        env.Replace(USES_DS1LICENSEHANDLER_STUB = True)
        
    env.Replace(SHARED_LIB_DICT=shared_lib_dict)
    return



