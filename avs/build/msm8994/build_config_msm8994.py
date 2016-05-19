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
# Copyright (c) 2013-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/avs.adsp/2.6.1/build/msm8994/build_config_msm8994.py#3 $
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
        env.Replace(USES_DTS_HPX_MODULE_STRIP = True)

        env.Replace(USES_DOLBYPLUS_ENCODER_STUB = True)
        env.Replace(USES_DS2AP_MODULE_STUB =  True)
        env.Replace(USES_DOLBYPULSEDECODERMODULE_STUB = True)
        env.Replace(USES_MS12DOLBYPULSEDECODERMODULE_STRIP = True)
        env.Replace(USES_SRSSS3DMODULE_STUB = True)
        env.Replace(USES_AFEVFRDRIVER_V1_STUB = True)
        env.Replace(USES_AFEVFRDRIVER_V2_STUB = True)
        #env.Replace(USES_AFEVFRDRIVER_V3_STUB = True)
        #env.Replace(USES_LPASSTIMESTAMPLIB_STUB = True)
        env.Replace(USES_AVSYNC_MGR_STUB = True)
        env.Replace(USES_WMASTDV8ENCODERMODULE_STUB=True)
        env.Replace(USES_VOICE_PROC_TX_SENSORS_STUB = True)
        env.Replace(USES_VOICEWAKEUPMODULE_STUB=True)

        if 'GEN_SHARED_LIBS' in env:
            #format: shared_lib_dict['USES_LIBNAME_STRIP_SO']:[ [lib major version, lib minor version], [is Qurt used], ['depends on library 1','depends on library 2']]
            # lib major version, lib minor version : version of the library (Different from shared lib API version). This needs to be incremented whenever library code is changed. 
            # is Qurt used - whether or not qurt is used by the library.

            shared_lib_dict['USES_MP3DECODERMODULE_STRIP_SO'] = [ [1,0] , [1] , ];
            shared_lib_dict['USES_HPMP3DECODERMODULE_STRIP_SO'] = [ [1,0] , [1] , ];
            shared_lib_dict['USES_COMBOMP3DECODERMODULE_STRIP_SO'] = [ [1,0] , [1], ['HpMp3DecoderModule','Mp3DecoderModule'] ];
            shared_lib_dict['USES_ETSIEAACCOMMONMODULE_STRIP_SO'] = [ [1,0] , [1] , ];
            shared_lib_dict['USES_ETSIEAACPLUSENCODERMODULE_STRIP_SO'] = [ [1,0] , [1], ['EtsiEaacCommonModule']];

            shared_lib_dict['USES_SAPLUSCMNMODULE_STRIP_SO'] = [ [1,0] , [1] , ];
            shared_lib_dict['USES_POPLESSEQUALIZERMODULE_STRIP_SO'] = [ [1,0] , [1] , ['SAPlusCmnModule']];
            shared_lib_dict['USES_BASSBOOSTMODULE_STRIP_SO'] = [ [1,0] , [1] , ['SAPlusCmnModule']];
            shared_lib_dict['USES_VIRTUALIZERMODULE_STRIP_SO'] = [ [1,0] , [1] , ['SAPlusCmnModule']];
            shared_lib_dict['USES_REVERBMODULE_STRIP_SO'] = [ [1,0] , [1] , ['SAPlusCmnModule']];


    else:

        env.Replace(USES_DTS =True)
        env.Replace(USES_MIDI =True)
        # NOTE: Please ensure that every newly added library should be properly stripped
        # for those symbols which are proprietary.

        env.Replace(USES_DTS_HPX_MODULE_STRIP = True)
        env.Replace(USES_AVSYNC_MGR_STUB = True)

        if env.get('COSIM_PROFILING_TEST') != True: # disabling library stripping for cosim based testfwk used for profiling.
            #Add AVS Voice Library Types for this image
            env.Replace(USES_QUARTET_STRIP = True)
            env.Replace(USES_SAMPLE_SLIP_STRIP = True)
            env.Replace(USES_RVE_STRIP = True)
            #env.Replace(USES_RSBY2_STRIP = True)
            #env.Replace(USES_IIR_FILTER_STRIP = True)
            #env.Replace(USES_FLUENCE_VOICEPLUS_STRIP = True)
            #env.Replace(USES_FIR_FILTER_STRIP = True)
            env.Replace(USES_ECHO_CANCELLER_STRIP = True)
            env.Replace(USES_DTMF_DETECT_STRIP = True)
            #env.Replace(USES_CTM_STRIP = True)
            #env.Replace(USES_CROSS_FADE_STRIP = True)
            #env.Replace(USES_CNG_STRIP = True)
            env.Replace(USES_AVC_TX_STRIP = True)
            env.Replace(USES_AVC_RX_STRIP = True)
            #env.Replace(USES_VFE_FILTERS_STRIP = True)
            #env.Replace(USES_TTY_STRIP = True)
            env.Replace(USES_TIME_WARPING_STRIP = True)
            #env.Replace(USES_VOCODER_AMRWB_STRIP = True)
            #env.Replace(USES_VOCODER_AMRNB_STRIP = True)
            #env.Replace(USES_VOCODER_FR_STRIP = True)
            #env.Replace(USES_VOCODER_FOURGV_STRIP = True)
            #env.Replace(USES_VOCODER_EVRC_STRIP = True)
            #env.Replace(USES_VOCODER_EFR_STRIP = True)
            env.Replace(USES_VOCODER_EAMR_STRIP = True)
            env.Replace(USES_SLOW_TALK_STRIP = True)
            #env.Replace(USES_VOCODER_CAPI_STRIP = True)
            #env.Replace(USES_VOLUME_CONTROL_STRIP = True)
            #env.Replace(USES_VOICE_RESAMPLER_STRIP = True)
            #env.Replace(USES_VOCODER_V13K_STRIP = True)
            #env.Replace(USES_VOCODER_HR_STRIP = True)
            #env.Replace(USES_VOCODER_G729AB_STRIP = True)
            #env.Replace(USES_VOCODER_G711_STRIP = True)
            #env.Replace(USES_WIDE_VOICE_STRIP = True)

            # Add AVS Afe Library Types for this image
            env.Replace(USES_ADAPANC_STRIP_ONLY =True)
            env.Replace(USES_FFSPKRPROT_STUB=True)
            env.Replace(USES_DTMFGENERATION_STRIP_ONLY=True)
            env.Replace(USES_REMOVECLICKLIB_STRIP_ONLY=True)
            env.Replace(USES_FBSPKRPROT_STUB=True)
            env.Replace(USES_AFESWMAD_ALGO_STRIP_ONLY=True)
            env.Replace(USES_AFESWMAD_FWK_STRIP_ONLY=True)
            env.Replace(USES_POP_SUPPRESSOR_STRIP_ONLY=True)
            env.Replace(USES_SP_V2_STRIP_ONLY =True)
            #env.Replace(USES_AFERIVADRIVER_STRIP=True)
            #env.Replace(USES_AFESLIMBUSDRIVER_STRIP=True)
            env.Replace(USES_AFEVFRDRIVER_V1_STUB = True)
            env.Replace(USES_AFEVFRDRIVER_V2_STUB = True)
            #env.Replace(USES_AFEVFRDRIVER_V3_STUB = True)
            #env.Replace(USES_LPASSTIMESTAMPLIB_STUB = True)

            #Add AVS Audio Library Types for this image
            env.Replace(USES_AACDECODERMODULE_STRIP=True)
            #env.Replace(USES_ETSIBITBUFFLIB_STRIP=True)
            #env.Replace(USES_ETSIFFRLIB_STRIP=True)
            #env.Replace(USES_ETSIOPLIB_STRIP=True)
            env.Replace(USES_ADPCMDECODERMODULE_STRIP=True)
            env.Replace(USES_ADPCMENCODERMODULE_STRIP=True)
            #env.Replace(USES_AMRBITBUFFERLIB_STRIP=True)
            #env.Replace(USES_AMRCORELIB_STRIP=True)
            #env.Replace(USES_AMRMATHLIB_STRIP=True)
            #env.Replace(USES_ETSIAMROPLIB_STRIP=True)
            #env.Replace(USES_ETSIAMRWBPLUSDECMODULE_STRIP=True)
            #env.Replace(USES_SBCENCODERMODULE_STRIP=True)
            #env.Replace(USES_WMAPRODECODERMODULE_STRIP=True)
            env.Replace(USES_WMASTDDECODERMODULE_STRIP=True)
            env.Replace(USES_WMASTDV8ENCODERMODULE_STUB=True)
            env.Replace(USES_DOLBYPLUS_ENCODER_STUB = True)
            env.Replace(USES_SRSSS3DMODULE_STUB = True)
            env.Replace(USES_DS2AP_MODULE_STUB =  True)
            env.Replace(USES_MS12DOLBYPULSEDECODERMODULE_STRIP = True)
            env.Replace(USES_ALACDECODERMODULE_STUB= True)

            if env.get('USES_DTS') == True:
                env.Replace(USES_DTSMODULE_STUB = True)

            if env.get('USES_MIDI') == True:
                env.Replace(USES_MIDICOREMODULE_STRIP=True)
            env.Replace(USES_HPMP2DECODERMODULE_STRIP=True)
            env.Replace(USES_SRSTRUMEDIAMODULE_STRIP=True)
            env.Replace(USES_AC3PACKETIZERMODULE_STRIP=True)
            env.Replace(USES_SPECTRUMANALYZERMODULE_STRIP=True)
            env.Replace(USES_ETSIAMRWBPLUSDECMODULE_STRIP=True)
            env.Replace(USES_FLACDECODERMODULE_STRIP=True)

            if 'GEN_SHARED_LIBS' in env:
            #format: shared_lib_dict['USES_LIBNAME_STRIP_SO']:[ [lib major version, lib minor version], [is Qurt used], ['depends on library 1','depends on library 2']]
            # lib major version, lib minor version : version of the library (Different from shared lib API version). This needs to be incremented whenever library code is changed. 
            # is Qurt used - whether or not qurt is used by the library.

                shared_lib_dict['USES_MP3DECODERMODULE_STRIP_SO'] = [ [1,0] , [1] , ];
                shared_lib_dict['USES_HPMP3DECODERMODULE_STRIP_SO'] = [ [1,0] , [1] , ];
                shared_lib_dict['USES_COMBOMP3DECODERMODULE_STRIP_SO'] = [ [1,0] , [1], ['HpMp3DecoderModule','Mp3DecoderModule'] ];
                shared_lib_dict['USES_ETSIEAACCOMMONMODULE_STRIP_SO'] = [ [1,0] , [1] , ];
                shared_lib_dict['USES_ETSIEAACPLUSENCODERMODULE_STRIP_SO'] = [ [1,0] , [1], ['EtsiEaacCommonModule']];

                shared_lib_dict['USES_SAPLUSCMNMODULE_STRIP_SO'] = [ [1,0] , [1] , ];
                shared_lib_dict['USES_POPLESSEQUALIZERMODULE_STRIP_SO'] = [ [1,0] , [1] , ['SAPlusCmnModule']];
                shared_lib_dict['USES_BASSBOOSTMODULE_STRIP_SO'] = [ [1,0] , [1] , ['SAPlusCmnModule']];
                shared_lib_dict['USES_VIRTUALIZERMODULE_STRIP_SO'] = [ [1,0] , [1] , ['SAPlusCmnModule']];
                shared_lib_dict['USES_REVERBMODULE_STRIP_SO'] = [ [1,0] , [1] , ['SAPlusCmnModule']];

            else:
                env.Replace(USES_HPMP3DECODERMODULE_STRIP=True)
                env.Replace(USES_MP3DECODERMODULE_STRIP=True)
                env.Replace(USES_COMBOMP3DECODERMODULE_STRIP=True)
                env.Replace(USES_ETSIEAACPLUSENCODERMODULE_STRIP=True)

            env.Replace(USES_VORBISDECODERMODULE_STRIP = True)
            env.Replace(USES_PASSTHRUFORMATTERMODULE_STRIP=True)
            env.Replace(USES_DTSHDPACKETIZERMODULE_STRIP=True)
            env.Replace(USES_DOLBYMOBILEMODULE_STRIP = True)
            env.Replace(USES_DOLBYPULSEDECODERMODULE_STUB = True)
            env.Replace(USES_GENERICDEPACKETIZERMODULE_STRIP=True)
            env.Replace(USES_MP3ENCODERMODULE_STRIP=True)
            env.Replace(USES_SBCENCODERMODULE_STRIP=True)
            env.Replace(USES_EAC3PACKETIZERMODULE_STRIP=True)
            env.Replace(USES_WMAPRODECODERMODULE_STRIP=True)
            env.Replace(USES_DOLBYSURROUNDMODULE_STRIP=True)
            #env.Replace(USES_EFFECTSMODULE_STRIP=True)
            env.Replace(USES_DS1LICENSEHANDLER_STRIP=True)
            env.Replace(USES_FLUENCE_VOICEPLUS_STRIP = True)
            env.Replace(USES_WIDE_VOICE_STRIP = True)
            env.Replace(USES_WIDE_VOICE_V2_STRIP = True)
            if 'USES_DISABLE_SENSORS' in env:
               env.Replace(USES_VOICE_PROC_TX_SENSORS_STUB = True)
            else:
               env.Replace(USES_VOICE_PROC_TX_SENSORS_STRIP = True)
            #env.Replace(USES_QUARTET_STRIP = True)
            #env.Replace(USES_SLOW_TALK_STRIP = True)
            env.Replace(USES_AFESPDIFDRIVER_STUB = True)
            env.Replace(USES_AFESIFDRIVER_STUB = True)
            env.Replace(USES_PPLL_STUB = True)
            env.Replace(USES_BSTC_MGR_STUB = True)
            env.Replace(USES_AVSYNC_MGR_STUB = True)
            env.Replace(USES_DOLBYPLUS_ENCODER_STUB = True)
            env.Replace(USES_AFEHDMIINPUTDRIVER_STUB = True)
            env.Replace(USES_AFEDMAMANAGER_STUB = True)
            env.Replace(USES_SRSSS3DMODULE_STUB = True)
            env.Replace(USES_DS2AP_MODULE_STUB =  True)
            env.Replace(USES_DOLBYPULSEDECODERMODULE_STUB = True)
            env.Replace(USES_MS12DOLBYPULSEDECODERMODULE_STRIP = True)
            env.Replace(USES_AFERIVADRIVER_STUB=True)
            env.Replace(USES_VOICEWAKEUPMODULE_STUB=True)

    env.Replace(SHARED_LIB_DICT=shared_lib_dict)
    return



