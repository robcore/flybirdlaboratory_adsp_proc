#ifndef QDSS_CSR_CONFIG_H
#define QDSS_CSR_CONFIG_H

/*=============================================================================

FILE:         qdss_csr_config.h

DESCRIPTION:  

================================================================================
              Copyright (c) 2013 Qualcomm Technologies Incorporated.
                         All Rights Reserved.
                QUALCOMM Proprietary and Confidential
==============================================================================*/


#define QDSS_QDSSCSR_REG_BASE_PHYS      (0xFC301000) 


//Values from hector for bus hang and wdog bite
#define HWEVENT_MUX_CTRL_0 0x00000000 
#define HWEVENT_MUX_CTRL_1 0x00F0F900
#define HWEVENT_MUX_CTRL_2 0x000F0000
#define HWEVENT_MUX_CTRL_3 0x00000D00



#endif //QDSS_CSR_CONFIG_H
