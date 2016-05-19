#===============================================================================
#
# AVS Cosim configuration for simulation
#
# GENERAL DESCRIPTION
#    AVS Cosim configuration for simulation
#     
#
# Copyright (c) 2009-2012 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/avs.adsp/2.6.1/build/cosim_config.py#3 $
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
# 09/21/12   kk      AVS Cosim configuration
#
#===============================================================================

import re
import string
import os
import sys
def generate_cosim_config(env):
    ADSP_AFE_COSIM = "adsptest/Audio/drivers/afe/AFECosim8660/scfAudioIfCosim"
    print "----"+env.get('PLATFORM')
    if env.get('PLATFORM') in ["Windows_NT","windows","win32","cygwin"]:
        if env.get('CHECKSIMBOOT') == True:
        
            PLATFORM_DIR="cygwin"    
            COSIM_EXT="w32"
            LIB_EXT="dll"
        else:
                # <-- HACK! --> Force Linux path always. PW cannot build in Linux. So have to use
        #windows builds to test in Linux. Clean-up when Linux builds work in PW.
            PLATFORM_DIR="lnx64"    
            COSIM_EXT="lnx64"
            LIB_EXT="so"
    elif env.get('PLATFORM') == 'linux':
        PLATFORM_DIR="lnx64"    
        COSIM_EXT="lnx64"
        LIB_EXT="so"
    else:
        print "Un supported platform"
        sys.exit(0)
    ADSP_AFE_COSIM_WITH_EXT=ADSP_AFE_COSIM+"_"+COSIM_EXT+"."+LIB_EXT
    BUILD_TARGET = env.get('BUILD_ASIC')
    if BUILD_TARGET in ["8092","8992","8994"]:
        COSIM_TARGET ="8092"
    if BUILD_TARGET in ["8996"]:
        COSIM_TARGET ="8996"


    DMAIOFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/dma_io.cfg"
    AVTIOFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/avtimerCosim.cfg"
    BTFMIOFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/BTFM.cfg"
    DMCOSIMFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/scfdm_cosim_"+COSIM_EXT+"."+LIB_EXT
    MIDICOSIMFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/scfmidiCosim_"+COSIM_EXT+"."+LIB_EXT
    AVTCOSIMFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/scfavtimerCosim_"+COSIM_EXT+"."+LIB_EXT
    RSCOSIMFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/resamplerCosim_"+COSIM_EXT+"."+LIB_EXT
    VFRCOSIMFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/vfrGenerator_"+COSIM_EXT+"."+LIB_EXT
    VIDCOSIMFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/vid_hw_workaround_cosim_"+COSIM_EXT+"."+LIB_EXT
    BTFMCOSIMFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/BTFMcosim_"+COSIM_EXT+"."+LIB_EXT
    DALCHIPINFOCOSIMFILE = "aDSPTest/cosims/common/dalchip_Cosim_"+COSIM_EXT+"."+LIB_EXT
    DMACFGFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/scfAudioIfCosim_"+COSIM_EXT+"."+LIB_EXT
    STCTSCOSIMFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/stcTimestampHwCore_"+COSIM_EXT+"."+LIB_EXT
    
    HDMITXCOSIMFILE = ""
    HDMITXCFGFILE = ""
    if BUILD_TARGET in ["8996"]:
        BTFMCOSIMFILE = ""
        MIDICOSIMFILE = ""
        HDMITXCFGFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/stream_io.cfg"
        HDMITXCOSIMFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/hdmiTxCosim_"+COSIM_EXT+"."+LIB_EXT
    
    if BUILD_TARGET in ["8092", "8996"]:
        HDMICAPTURECOSIMFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/HdmiCaptureCosim_"+COSIM_EXT+"."+LIB_EXT
        ATIMEIOFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/atimeCosim.cfg"
        ATIME2IOFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/atime2Cosim.cfg"
        HDMICAPTUREIOFILE = "aDSPTest/cosims/"+COSIM_TARGET+"/hdmi_capture_properties.cfg"

    DALCHIPINFOPARAMS = " "+env.get('BUILD_ASIC')

    if BUILD_TARGET == "8996":         
        DMACFGPARAMS = " -aifstartaddr 0x09100000\
            -aifendaddr   0x0911D004\
            -aifresetaddr 0x0911FFF4\
            -buslatency 30\
            -l2vicbaseaddr 0x09390000\
            -l2vicintrnum 19\
            -aifcfg "+DMAIOFILE+"\
            -timer_STC_Addr 0x090F700C"
        AVTCOSIMPARAMS = " -l2vicbaseaddr 0x09390000\
            -l2vicintrnum 50\
            -avtstartaddr 0x090F7000\
            -avtendaddr 0x090F70FF\
            -buslatency 30\
            -avtimercfg "+AVTIOFILE        
        DMCOSIMPARAMS =  " 0x090C2000--0x090C2020-10\
            -l2vicbaseaddr 0x09390000\
            -l2vicintrnum 23"
        RSCFGPARAMS = " -rsstartaddr 0x09138000\
            -rsendaddr 0x09140000\
            -buslatency 30\
            -l2vicbaseaddr 0x09390000\
            -l2vicintrnum 53"
        VFR1CFGPARAMS = " -trigger_lpaif TRUE\
            -init_delay_us 0\
            -vfr_period_us 20000\
            -lpaif_irq_force_addr 0x0910A010\
            -lpaif_irq_force_mask 0x08000000\
            -l2vicbaseaddr 0x09390000\
            -l2vicintrnum 51\
            -vfrID 0\
            -stc_timestamp_trigger_addr 0x09095008"
        VFR2CFGPARAMS = " -trigger_lpaif FALSE\
            -init_delay_us 10000\
            -vfr_period_us 20000\
            -lpaif_irq_force_addr 0x0910A010\
            -lpaif_irq_force_mask 0x08000000\
            -l2vicbaseaddr 0x09390000\
            -l2vicintrnum 124\
            -vfrID 7\
            -stc_timestamp_trigger_addr 0x09095008"
        MIDICFGPARAMS = ""
        BTFMCOSIMPARAMS = ""
        STCTSCOSIMPARAMS = " -lpass_cc_startaddr 0x09000000\
            -buslatency 30\
            -timer_STC_reg_addr 0x090F7000"
        HDMITXCOSIMPARAMS = " -hdmitxstartaddr 0x090D8000\
            -hdmitxendaddr 0x090DEFFF\
            -buslatency 30\
            -hdmitxcfg "+HDMITXCFGFILE+"\
            -hdmitxresetaddr 0x090C8000\
            -l2vicbaseaddr 0x09390000\
            -dspl2vicintrnum 94\
            -timer_STC_reg_addr 0x090F700C\
            -appl2vicintrnum 61\
            -trace_level 4\
            -trace_reg_writes 0\
            -trace_reg_reads 0\
            -timer_STC_Addr 0x090F700C"


    if BUILD_TARGET == "8994" or BUILD_TARGET == "8992":         
        DMACFGPARAMS = " -aifstartaddr 0xFE0C0000\
            -aifendaddr 0xFE0DC004\
            -aifresetaddr 0xFE0DFFF4\
            -buslatency 30\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 19\
            -aifcfg "+DMAIOFILE+"\
            -timer_STC_Addr 0xFE09C00C"
        AVTCOSIMPARAMS = " -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 50\
            -avtstartaddr 0xFE09C000\
            -avtendaddr 0xFE09C3FF\
            -buslatency 30\
            -avtimercfg "+AVTIOFILE        
        DMCOSIMPARAMS =  " 0xFE092000--0xFE092014-10\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 23"
        RSCFGPARAMS = " -rsstartaddr 0xFE0B0000\
            -rsendaddr 0xFE0B0FFF\
            -buslatency 30\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 53"
        VFR1CFGPARAMS = " -trigger_lpaif TRUE\
            -init_delay_us 0\
            -vfr_period_us 20000\
            -lpaif_irq_force_addr 0xFE0D1010\
            -lpaif_irq_force_mask 0x08000000\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 51\
            -vfrID 0\
            -stc_timestamp_trigger_addr 0xFE002008"
        VFR2CFGPARAMS = " -trigger_lpaif FALSE\
            -init_delay_us 10000\
            -vfr_period_us 20000\
            -lpaif_irq_force_addr 0xFE0D1010\
            -lpaif_irq_force_mask 0x08000000\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 124\
            -vfrID 7\
            -stc_timestamp_trigger_addr 0xFE002008"
        MIDICFGPARAMS = " -midistartaddr 0xFE070000\
            -midiendaddr 0xFE07FFFF\
            -buslatency 30\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 22"	
        BTFMCOSIMPARAMS = " -ctl_reg 0xFB206000\
            -l2vicbaseaddr 0xfe290000\
            -BT_SPKR_IntNum 10\
            -BT_MIC_IntNum 17\
            -MailBox_IntNum 15\
            -FM_IntNum 16\
            -Cfg_FileName "+BTFMIOFILE+"\
            -stc_timestamp_trigger_addr 0xFE002008"
        STCTSCOSIMPARAMS = " -lpass_cc_startaddr 0xfe000000\
            -buslatency 30\
            -timer_STC_reg_addr 0xFE09C00C"
        
        
    if BUILD_TARGET == "8092":
        BTFMCOSIMPARAMS = " -ctl_reg 0xFB206000\
                        -l2vicbaseaddr 0xfe290000\
                        -BT_SPKR_IntNum 10\
                        -BT_MIC_IntNum 17\
                        -MailBox_IntNum 15\
                        -FM_IntNum 16\
                        -Cfg_FileName "+BTFMIOFILE+"\
                        -lpass_cc_baseaddr 0xfe000000"
        DMCOSIMPARAMS =  " 0xFE0B2000--0xFE0B2014-10\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 23"
        DMACFGPARAMS = " -aifstartaddr 0xFE140000\
            -aifendaddr 0xFE15FFF0\
            -aifresetaddr 0xFE15FFF4\
            -buslatency 30\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 19\
            --timer_STC_Addr  0xFE0C900C\
            -aifcfg "+DMAIOFILE
        MIDICFGPARAMS = " -midistartaddr 0xFE070000\
                        -midiendaddr 0xFE07FFFF\
                        -buslatency 30\
                        -l2vicbaseaddr 0xfe290000\
                        -l2vicintrnum 22"
        AVTCOSIMPARAMS = " -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 50\
            -avtstartaddr 0xFE0C9000\
            -avtendaddr 0xFE0C93FF\
            -buslatency 30\
            -avtimercfg "+AVTIOFILE
        ATCOSIMPARAMS_1 = " -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 50\
            -avtstartaddr 0xFE0CB000\
            -avtendaddr 0xFE0CB3FF\
            -buslatency 30\
            -avtimercfg "+ATIMEIOFILE
        ATCOSIMPARAMS_2 = " -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 50\
            -avtstartaddr 0xFE0CF000\
            -avtendaddr 0xFE0CF3FF\
            -buslatency 30\
            -avtimercfg "+ATIME2IOFILE
        HDMICOSIMPARAMS = " -hdmicapturestartaddr 0xFE134000\
            -hdmicaptureendaddr 0xFE1340D0\
            -buslatency 30\
            -hdmicfg "+HDMICAPTUREIOFILE+"\
            -hdmiresetaddr 0xFE1340D4\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 121\
            -timer_STC_reg_addr 0xFE0C900C\
            -appl2vicintrnum 61\
            -trace_level 0\
            -trace_reg_writes 0\
            -trace_reg_reads 0"
        RSCFGPARAMS = " -rsstartaddr 0xFE0D0000\
            -rsendaddr 0xFE0D0FFF\
            -buslatency 30\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 53"
        VFR1CFGPARAMS = " -trigger_lpaif TRUE\
            -init_delay_us 0\
            -vfr_period_us 20000\
            -lpaif_irq_force_addr 0xFE0D1010\
            -lpaif_irq_force_mask 0x08000000\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 51\
            -vfrID 0\
            -stc_timestamp_trigger_addr 0xFE002008"
        VFR2CFGPARAMS = " -trigger_lpaif FALSE\
            -init_delay_us 10000\
            -vfr_period_us 20000\
            -lpaif_irq_force_addr 0xFE0D1010\
            -lpaif_irq_force_mask 0x08000000\
            -l2vicbaseaddr 0xfe290000\
            -l2vicintrnum 124\
            -vfrID 7\
            -stc_timestamp_trigger_addr 0xFE002008"
        STCTSCOSIMPARAMS = " -lpass_cc_startaddr 0xfe000000\
            -buslatency 30\
            -timer_STC_reg_addr 0xFE0C900C"

    
    if env.get('Q6VERSION')=="v5":
        if env.get('PLATFORM') in ["Windows_NT","windows","win32","cygwin"]:
            if env.get('CHECKSIMBOOT') == True:
                
                TIMERCFGFILE = "C:/Qualcomm/HEXAGON_Tools/"+env.get('HEXAGON_RTOS_RELEASE')+"/qc/lib/iss/qtimer."+LIB_EXT
                L2VICCFGFILE = "C:/Qualcomm/HEXAGON_Tools/"+env.get('HEXAGON_RTOS_RELEASE')+"/qc/lib/iss/l2vic."+LIB_EXT
                TIMERCFGPARAMS = " --csr_base=0xfe280000 --irq_p=2,3 --freq=19200000 --cnttid=17"
                L2VICCFGPARAMS = " 32 0xfe290000"
            else:
                # <-- HACK! --> Force Linux path always. PW cannot build in Linux. So have to use
                #windows builds to test in Linux. Clean-up when Linux builds work in PW.
                TIMERCFGFILE = "/pkg/qct/software/hexagon/releases/tools/"+env.get('HEXAGON_RTOS_RELEASE')+"/qc/lib/iss/qtimer."+LIB_EXT
                L2VICCFGFILE = "/pkg/qct/software/hexagon/releases/tools/"+env.get('HEXAGON_RTOS_RELEASE')+"/qc/lib/iss/l2vic."+LIB_EXT
                TIMERCFGPARAMS = " --csr_base=0xfe280000 --irq_p=2,3 --freq=19200000 --cnttid=17"
                L2VICCFGPARAMS = " 32 0xfe290000"
        elif env.get('PLATFORM') == 'linux':	
            TIMERCFGFILE = "/pkg/qct/software/hexagon/releases/tools/"+env.get('HEXAGON_RTOS_RELEASE')+"/qc/lib/iss/qtimer."+LIB_EXT
            L2VICCFGFILE = "/pkg/qct/software/hexagon/releases/tools/"+env.get('HEXAGON_RTOS_RELEASE')+"/qc/lib/iss/l2vic."+LIB_EXT
            TIMERCFGPARAMS = " --csr_base=0xfe280000 --irq_p=2,3 --freq=19200000 --cnttid=17"
            L2VICCFGPARAMS = " 32 0xfe290000"
        else:
            print "Unsupported flavor(supports only on windows and Linux)"
            sys.exit(0)
    else:
        TIMERCFGFILE = "/pkg/qct/software/hexagon/releases/tools/"+env.get('HEXAGON_RTOS_RELEASE')+"/qc/lib/iss/qtimer."+LIB_EXT
        L2VICCFGFILE = "/pkg/qct/software/hexagon/releases/tools/"+env.get('HEXAGON_RTOS_RELEASE')+"/qc/lib/iss/l2vic."+LIB_EXT
        TIMERCFGPARAMS = " --csr_base=0xfe280000 --irq_p=2,3 --freq=19200000 --cnttid=17"
        L2VICCFGPARAMS = " 32 0xfe290000"               

    # Override for 8996 target w.r.t L2VIC and QTimer params
    if BUILD_TARGET == "8996":         
        L2VICCFGPARAMS = " 32 0x09390000"                      
        TIMERCFGPARAMS = " --csr_base=0x09380000 --irq_p=2,3 --freq=19200000 --cnttid=0x11"
            
    Q6SS_OBJ_FILE_PATH = "../"
    Q6SS_OBJ_FILE_TEMP = Q6SS_OBJ_FILE_PATH+"q6ss1.cfg"
    Q6SS_OBJ_FILE = Q6SS_OBJ_FILE_PATH+"q6ss.cfg"
    ADSP_TEST_COSIMOPTS_FILE = "../adsp_test_cosimopts.cfg"
    ADSP_TEST_INTERNAL_BT_FM_COSIMOPTS_FILE = "../adsp_test_internal_bt_fm_cosimopts.cfg"
    DMAIOFILE_PATH="../"+DMAIOFILE
    BTFMIOFILE_PATH="../"+BTFMIOFILE

    # <-- HACK for SIM to update the path of the qurt_model.so in osam.cfg -->
    OSAMFILE_PATH = "../../obj/qdsp6v5_ReleaseG/osam.cfg"
    fo_osam = open(OSAMFILE_PATH,'w')
    fo_osam.write("../core/kernel/qurt/osam/bin/lnx64/v55/qurt_model.so")
    fo_osam.close()
    
    if env.get('PLATFORM') in ["Windows_NT","windows","win32","cygwin"]:
        # <-- HACK! --> Force Linux path always. PW cannot build in Linux. So have to use
        #windows builds to test in Linux. Clean-up when Linux builds work in PW.
        if env.get('CHECKSIMBOOT') == True:    
            TIMERCFGFILE = TIMERCFGFILE.replace("/","\\")
            DMACFGFILE = DMACFGFILE.replace("/","\\")
            MIDICOSIMFILE = MIDICOSIMFILE.replace("/","\\")
            DMCOSIMFILE = DMCOSIMFILE.replace("/","\\")
            L2VICCFGFILE = L2VICCFGFILE.replace("/","\\")
            AVTCOSIMFILE = AVTCOSIMFILE.replace("/","\\")
            VIDCOSIMFILE = VIDCOSIMFILE.replace("/","\\")
            RSCOSIMFILE = RSCOSIMFILE.replace("/","\\")
            VFRCOSIMFILE = VFRCOSIMFILE.replace("/","\\")
            BTFMCOSIMFILE = BTFMCOSIMFILE.replace("/","\\")
            Q6SS_OBJ_FILE = Q6SS_OBJ_FILE.replace("/","\\")
            Q6SS_OBJ_FILE_PATH = Q6SS_OBJ_FILE_PATH.replace("/","\\")
            ADSP_TEST_COSIMOPTS_FILE = ADSP_TEST_COSIMOPTS_FILE.replace("/","\\")
            ADSP_TEST_INTERNAL_BT_FM_COSIMOPTS_FILE = ADSP_TEST_INTERNAL_BT_FM_COSIMOPTS_FILE.replace("/","\\")
            DMAIOFILE_PATH = DMAIOFILE_PATH.replace("/","\\")
            BTFMIOFILE_PATH = BTFMIOFILE_PATH.replace("/","\\")
         

                
    
    # generate q6ss.cfg
    if env.get('PLATFORM') in ["Windows_NT","windows","win32","cygwin"] :
        if env.get('CHECKSIMBOOT') == True:
            fo_q6ss = open(Q6SS_OBJ_FILE,'wb')
            fo_q6ss.write(TIMERCFGFILE+TIMERCFGPARAMS+"\n")
            fo_q6ss.write(L2VICCFGFILE+L2VICCFGPARAMS+"\n")
            fo_q6ss.close()
        else: 
            fo_q6ss = open(Q6SS_OBJ_FILE,'wb')
            fo_q6ss.write(TIMERCFGFILE+TIMERCFGPARAMS+"\n")
            fo_q6ss.write(L2VICCFGFILE+L2VICCFGPARAMS+"\n")
            fo_q6ss.write(VIDCOSIMFILE+"\n")
            if MIDICOSIMFILE != "":
                fo_q6ss.write(MIDICOSIMFILE+MIDICFGPARAMS+"\n")
            fo_q6ss.write(DMACFGFILE+DMACFGPARAMS+"\n")
            fo_q6ss.write(DMCOSIMFILE+DMCOSIMPARAMS+"\n")
            fo_q6ss.write(AVTCOSIMFILE+AVTCOSIMPARAMS+"\n")
            fo_q6ss.write(RSCOSIMFILE+RSCFGPARAMS+"\n")
            fo_q6ss.write(VFRCOSIMFILE+VFR1CFGPARAMS+"\n")
            fo_q6ss.write(VFRCOSIMFILE+VFR2CFGPARAMS+"\n")
            if BTFMCOSIMFILE != "":
                fo_q6ss.write(BTFMCOSIMFILE+BTFMCOSIMPARAMS+"\n")
            fo_q6ss.write(STCTSCOSIMFILE+STCTSCOSIMPARAMS+"\n")
            fo_q6ss.write(DALCHIPINFOCOSIMFILE+DALCHIPINFOPARAMS+"\n")
            fo_q6ss.close()
    elif env.get('PLATFORM') == 'linux':
        fo_q6ss = open(Q6SS_OBJ_FILE,'wb')
        fo_q6ss.write(TIMERCFGFILE+TIMERCFGPARAMS+"\n")
        fo_q6ss.write(L2VICCFGFILE+L2VICCFGPARAMS+"\n")
        fo_q6ss.write(VIDCOSIMFILE+"\n")
        if MIDICOSIMFILE != "":
            fo_q6ss.write(MIDICOSIMFILE+MIDICFGPARAMS+"\n")
        if HDMITXCOSIMFILE != "":
            fo_q6ss.write(HDMITXCOSIMFILE+HDMITXCOSIMPARAMS+"\n")
        fo_q6ss.write(DMACFGFILE+DMACFGPARAMS+"\n")
        fo_q6ss.write(DMCOSIMFILE+DMCOSIMPARAMS+"\n")
        fo_q6ss.write(AVTCOSIMFILE+AVTCOSIMPARAMS+"\n")
        if BUILD_TARGET == "8092":
            fo_q6ss.write(AVTCOSIMFILE+ATCOSIMPARAMS_1+"\n")
            fo_q6ss.write(AVTCOSIMFILE+ATCOSIMPARAMS_2+"\n")
            fo_q6ss.write(HDMICAPTURECOSIMFILE+HDMICOSIMPARAMS+"\n")
        fo_q6ss.write(RSCOSIMFILE+RSCFGPARAMS+"\n")
        fo_q6ss.write(VFRCOSIMFILE+VFR1CFGPARAMS+"\n")
        fo_q6ss.write(VFRCOSIMFILE+VFR2CFGPARAMS+"\n")
        if BTFMCOSIMFILE != "":
            fo_q6ss.write(BTFMCOSIMFILE+BTFMCOSIMPARAMS+"\n")
        fo_q6ss.write(STCTSCOSIMFILE+STCTSCOSIMPARAMS+"\n")
        fo_q6ss.write(DALCHIPINFOCOSIMFILE+DALCHIPINFOPARAMS+"\n")
        fo_q6ss.close()
    else:
        print "Unsupported flavor"
        sys.exit(0)
     
    

    """
        forg_q6ss = open(Q6SS_OBJ_FILE,'w')
        with open(Q6SS_OBJ_FILE_TEMP,'r') as f:
            for line in f:
                line_mod = re.sub('\r', '', line)
                forg_q6ss.write(line_mod)

        forg_q6ss.close()
        
    """


    #generate adsp_test_cosimopts.cfg
    fo_opts = open(ADSP_TEST_COSIMOPTS_FILE,'wb')
    fo_opts.write(DMACFGFILE+DMACFGPARAMS+"\n")
    if BUILD_TARGET == "8092":
        fo_opts.write(HDMICAPTURECOSIMFILE+HDMICOSIMPARAMS+"\n")
    fo_opts.close()

    #generate adsp_test_internal_bt_fm_cosimopts.cfg
    fo_btfm_opts = open(ADSP_TEST_INTERNAL_BT_FM_COSIMOPTS_FILE,'wb')
    fo_btfm_opts.write(BTFMCOSIMFILE+BTFMCOSIMPARAMS+"\n")
    fo_btfm_opts.close()




    #Making DMA IO File Writeable, for cosim reset option...
    os.chmod(DMAIOFILE_PATH,0777)

    #Making INTERNAL BT FM File Writeable, for cosim reset option...
    os.chmod(BTFMIOFILE_PATH,0777)

    return



