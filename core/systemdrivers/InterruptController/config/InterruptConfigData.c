/*==============================================================================

  D A L I N T E R R U P T   C O N T R O L L E R    

DESCRIPTION
 This file Contains the Interrupt configuration data for all the interrupts for 
 this platform.

REFERENCES

        Copyright © 2011 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/InterruptController/config/InterruptConfigData.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/

#include "DALReg.h"
#include "DALDeviceId.h"
#include "DDIInterruptController.h"
#include "DALInterruptControllerConfig.h"



/*=========================================================================

                           DATA DEFINITIONS

===========================================================================*/

/*
 * Interrupt_Configs
 * BSP data for this target's interrupts.
 * The data layout is the following :
 * {  l2VIC interrupt vector number ,  Interrupt Priority  , Interrupt Service thread stack size }
 *
 */
static InterruptConfigType InterruptConfigs[] =
{
  { 90 ,  7  , DAL_IST_STACK_SIZE }, /* ABT timeout  */    
  {  30 ,  0  , DAL_IST_STACK_SIZE },/* TRAMP_SLEEP_TIMETICK_IRQ  */ 
  {164 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_WATCHDOG_IRQ  */       
  {165 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6DOG_EXPIRED_IRQ  */  
  {167 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6POWERUP_DONE_IRQ  */ 
  {207 ,  4  , DAL_IST_STACK_SIZE }, /* TRAMP_PMIC_SSBI_IRQ  */      
  {267 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI1_UART_IRQ  */     
  {268 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI2_UART_IRQ  */     
  {269 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI3_UART_IRQ  */     
  {270 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI4_UART_IRQ  */     
  {271 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI5_UART_IRQ  */     
  {272 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI6_UART_IRQ  */     
  {273 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI7_UART_IRQ  */     
  {274 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI8_UART_IRQ  */     
  {275 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI9_UART_IRQ  */     
  {276 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI10_UART_IRQ  */    
  {261 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI11_UART_IRQ  */    
  {263 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI12_UART_IRQ  */    
  {220 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_USB_HS_IRQ  */         
  {221 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_SDIOC1_BAM_IRQ  */     
  {222 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_SDIOC2_BAM_IRQ  */     
  {223 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_BAM1_IRQ  */           
  {224 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_BAM2_IRQ  */           
  {225 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_BAM3_IRQ  */           
  {226 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_BAM4_IRQ  */           
  {227 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_BAM4_IRQ  */           
  {277 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI1_QUP_IRQ  */      
  {278 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI2_QUP_IRQ  */      
  {279 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI3_QUP_IRQ  */      
  {280 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI4_QUP_IRQ  */      
  {281 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI5_QUP_IRQ  */      
  {282 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI6_QUP_IRQ  */      
  {283 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI7_QUP_IRQ  */      
  {284 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI8_QUP_IRQ  */      
  {285 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI9_QUP_IRQ  */      
  {286 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI10_QUP_IRQ  */     
  {262 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI11_QUP_IRQ  */     
  {264 ,  2  , DAL_IST_STACK_SIZE }, /* TRAMP_GSBI12_QUP_IRQ  */     
  {288 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_ADM_IRQ  */            
  {215 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_SDC1_0_IRQ  */         
  {216 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_SDC2_0_IRQ  */         
  {217 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_SDC3_0_IRQ  */         
  {218 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_SDC4_0_IRQ  */         
  {219 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_SDC5_0_IRQ  */         
  
  /* 
   * GPIO Interrupts to MSS. 
   */
  {197 ,  1   , DAL_IST_STACK_SIZE },/* TRAMP_GPIO_GROUP1_IRQ  */          
  {199 ,  1   , DAL_IST_STACK_SIZE },/* TRAMP_GPIO_DIRECT_CONNECT_9_IRQ */ 
  {200 ,  1   , DAL_IST_STACK_SIZE },/* TRAMP_GPIO_DIRECT_CONNECT_10_IRQ */
  {201 ,  1   , DAL_IST_STACK_SIZE },/* TRAMP_GPIO_DIRECT_CONNECT_11_IRQ */
  {202 ,  1   , DAL_IST_STACK_SIZE },/* TRAMP_GPIO_DIRECT_CONNECT_12_IRQ */
  {203 ,  1   , DAL_IST_STACK_SIZE },/* TRAMP_GPIO_DIRECT_CONNECT_13_IRQ */
  {204 ,  1   , DAL_IST_STACK_SIZE },/* TRAMP_GPIO_DIRECT_CONNECT_14_IRQ */
  {205 ,  1   , DAL_IST_STACK_SIZE },/* TRAMP_GPIO_DIRECT_CONNECT_15_IRQ */
  

  /* 
   * IPC interrupts to MSS 
   */
  {190 ,  3 , DAL_IST_STACK_SIZE },  /* TRAMP_RIVA2M_0_IRQ  */
  {191 ,  3 , DAL_IST_STACK_SIZE }  /* TRAMP_RIVA2M_1_IRQ  */,
  {192 ,  3 , DAL_IST_STACK_SIZE }  /* TRAMP_RIVA2M_2_IRQ  */,
  {242 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_SPS2MSS_0_IRQ  */ 
  {240 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_SPS2MSS_1_IRQ  */ 
  {184 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_SPS2MSS_2_IRQ  */ 
  {185 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_SPS2MSS_3_IRQ  */ 
  {193 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_RPM2MSS_0_IRQ  */ 
  {194 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_RPM2MSS_1_IRQ  */ 
  {195 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_RPM2MSS_2_IRQ  */ 
  {196 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_RPM2MSS_3_IRQ  */ 
  {174 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_A2M_0_IRQ  */    
  {175 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_A2M_1_IRQ  */    
  {176 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_A2M_2_IRQ  */    
  {177 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_A2M_3_IRQ  */    
  {178 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_A2M_4_IRQ  */    
  {179 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_A2M_5_IRQ  */    
  {180 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_A2M_6_IRQ  */    
  {181 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_A2M_7_IRQ  */    
  {182 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_A2M_8_IRQ  */    
  {183 ,  3 , DAL_IST_STACK_SIZE }, /* TRAMP_A2M_9_IRQ  */    
  {186 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_LPASS2M_0_IRQ  */
  {187 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_LPASS2M_1_IRQ  */
  {188 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_LPASS2M_2_IRQ  */
  {189 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_LPASS2M_3_IRQ  */  
  {29 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6A_0_IRQ  */
  {31 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6A_1_IRQ  */
  {32 ,  7  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6A_2_IRQ  */
  {33 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6A_3_IRQ  */
  {34 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6A_4_IRQ  */
  {35 ,  7  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6A_5_IRQ  */
  {36 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6A_6_IRQ  */
  {37 ,  3  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6A_7_IRQ  */
  {38 ,  7  , DAL_IST_STACK_SIZE }, /* TRAMP_Q6A_8_IRQ  */
 
  /* 
   * Modem combo interrupts 
   */
  {128 ,  6 , DAL_IST_STACK_SIZE },  /* TRAMP_MODEM_COMB_0_IRQ  */ 
  {129 ,  6 , DAL_IST_STACK_SIZE },  /* TRAMP_MODEM_COMB_1_IRQ  */ 
  {130 ,  6 , DAL_IST_STACK_SIZE },  /* TRAMP_MODEM_COMB_2_IRQ  */ 
  {131 ,  6 , DAL_IST_STACK_SIZE },  /* TRAMP_RF_DIRECTOR_IRQ  */
  {132 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_SLEEP_FEE_IRQ  */
  {133 ,  6 , DAL_IST_STACK_SIZE },  /* TRAMP_CDMA_RTC_IRQ  */ 
  {134 ,  6 , DAL_IST_STACK_SIZE },  /* TRAMP_CDMA_RTC_ROLLOVER_IRQ  */ 
  {135 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_CDMA_DEC_DONE_IRQ  */ 
  {136 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_UMTS_F8_IRQ  */
  {137 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_GSM_MICRO_ISR */
  {138 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_EDGE_ENCRYPT_DONE_IRQ  */ 
  {139 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_CDMA_OFFLINE_DONE_IRQ  */ 
  {140 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_CDMA_QUICK_PAGING_IRQ  */ 
  {141 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_CDMA_TIME_1_IRQ  */   
  {142 ,  6  , DAL_IST_STACK_SIZE },/* TRAMP_CDMA_TIME_2_IRQ  */   
  {143 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_MODEM_COMB_15_IRQ  */ 
  {144 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_MODEM_COMB_16_IRQ  */ 
  {145 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_MODEM_COMB_17_IRQ  */ 
  {146 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_MODEM_COMB_18_IRQ  */ 
  {147 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_GP_0_IRQ  */
  {148 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_GP_1_IRQ  */
  {149 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_GP_2_IRQ  */
  {150 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_GP_3_IRQ  */
  {151 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_GP_4_IRQ  */
  {152 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_GP_5_IRQ  */
  {153 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_GP_6_IRQ  */
  {154 ,  6  , DAL_IST_STACK_SIZE }, /* TRAMP_GP_7_IRQ  */
  {155 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_CDMA_MOD_TX_SLOT_IRQ  */ 
  {156 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_CDMA_MOD_TX_FRAME_IRQ  */
  {157 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_CDMA_EVEN_SEC_IRQ  */
  {158 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_GP_8_IRQ  */ 
  {172 ,  6 , DAL_IST_STACK_SIZE }, /* TRAMP_GP_9_IRQ  */ 
  {
    /* 
     * This marks the end of the BSP data. 
    * This is a place holder for data processing.
    */
    INVALID_INTERRUPT, 
    7,
    0x1
  }
};

/*
 * InterruptPlatformDataType 
 * This is used by the Interrupt controller platform to query platform specific data. 
 */
InterruptPlatformDataType  pInterruptControllerConfigData[] =
{
  {
    InterruptConfigs,           /* pIRQConfigs */
    DALINTERRUPT_SUPPORTED_INTERRUPTS
  }
};




  
