/*
===========================================================================

FILE:   HALqupe.c

DESCRIPTION:
    This file implements a qup hal.

===========================================================================

        Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/spi/src/hal/HALqupe.c#2 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
06/13/12 ddk    Removed unused include.
06/06/12 ddk    Removed non-common functions related to I2c and SPI.
06/05/12 ddk    Removed unwanted writes in bam mode.
04/19/12 ddk    Added changes for avoiding symbol match with I2C library.
                Added updated HAL implementation used for I2C.
02/22/12 ddk    Added support for SPI BAM interface requirements.
02/14/11 LK     Changed QUP address block initialization from static to
                dynamic. Virtual addresses are intialized at runtime.
10/15/10 LK     Created

===========================================================================
        Copyright c 2008, 2009, 2010-2013 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR

===========================================================================
*/
#include "HALqupe.h"
#include "HALqupeTarget.h"

// Define and include the header file that adds the relevant log headers
#define HAL_QUPE_LOG
#include "QupLog.h"

#define HAL_QUPE_VERSION_STRING "HAL_QUPE_V_2.0"




/*
#ifdef QUP_HAL_DBG
  #define WHERE_STR "FILE: %s LINE: %d"

  #define HAL_QUPE_ASSERT(COND)\
   {\
    if (COND) {\
      IBUSLOG(QUP_HAL_DBG, LOG_LEVEL_5,pQupAddr,2, WHERE_STR, __FILE__, __LINE__);\
      while(1);\
    }\
   }\

#else
*/
#define HAL_QUPE_ASSERT(...)

/*
#endif
*/


#define HAL_QUPE_TRANSFER_SIZE                          8

/** @enum HAL_qupe_RunStateType QUPe run state.                       */
typedef enum HAL_qupe_RunStateCmdType
{
   HAL_QUPE_RUNSTATE_CMD_RESET   = 0x2  , /**<Go to Reset State.          */
   HAL_QUPE_RUNSTATE_CMD_RUN     = 0x1  , /**<Go to RUN state.            */
   HAL_QUPE_RUNSTATE_CMD_PAUSE   = 0x3  , /**<Go to pause state.          */

   HAL_QUPE_RUNSTATE_CMD_EXTEND  = 0x7FFFFFFF
} HAL_qupe_RunStateCmdType;

/** @brief Resets QUPe.
    @param[in]  pQupAddr Qup Block address.
    @return Nothing.
  */
void
HAL_qupe_Reset
(
   uint8  *pQupAddr
)
{
   QUPE_OUT(pQupAddr, QUP_SW_RESET, 1);
   QUPLOG_LOG_WRITE((uint32)pQupAddr, 1,"QUP[0x%x]: Write:  QUP_SW_RESET , VAL: 1", (uint32)pQupAddr);
}

/** @brief This function initializes the qupe HAL.
    @param[in]  pQupAddr        Qup Block address.
    @param[in]  ppszVersion   Version pointer.
    @return Nothing.
  */
void HAL_qupe_Init
(
  uint8 *pQupAddr,
  char **ppszVersion
)
{
   if (NULL != ppszVersion)
   {
      *ppszVersion = HAL_QUPE_VERSION_STRING;
   }
   HAL_qupe_Reset(pQupAddr);
}

/** @brief Gets the state of the run state field.
    @param[in]  pQupAddr Qup Block address.
    @return TRUE if the run state is valid, FALSE otherwise.
  */
boolean
HAL_qupe_RunStateIsValid
(
   uint8 *pQupAddr
)
{
   uint32 uValidField;
   uint32 uRegVal;

   uRegVal = QUPE_IN(pQupAddr, QUP_STATE);
   uValidField = (uRegVal & (QUPE_FMSK(QUP_STATE, STATE_VALID))) >>
         QUPE_SHFT(QUP_STATE, STATE_VALID);
   
   QUPLOG_LOG_READ((uint32)pQupAddr, 3,
                   "QUP[0x%x]: Read: QUP_STATE=0x%x, QUP_STATE[STATE_VALID]=0x%x",
                   (uint32)pQupAddr, uRegVal, uValidField);
   return (boolean)uValidField;
}

/** @brief Sets the state of the QUPe.
    @param[in]  pQupAddr Qup Block address.
    @param[in]  ceQupeRunState Specifies the new state.
    @return HAL_QUPE_RESULT_SUCCESS if successful, error code otherwise.
  */
HAL_qupe_ResultType
HAL_qupe_SetRunState
(
   uint8 *pQupAddr,
   const HAL_qupe_RunStateType ceQupeRunState
)
{
   HAL_qupe_RunStateType curRunState;

   curRunState = HAL_qupe_GetRunState(pQupAddr);


   /* the doc says to write two times */
   switch(ceQupeRunState)
   {
      case HAL_QUPE_RUNSTATE_RESET :
         if (HAL_QUPE_RUNSTATE_PAUSE == curRunState) {
        	 QUPE_OUTF(pQupAddr, QUP_STATE, STATE, HAL_QUPE_RUNSTATE_CMD_RESET);
          //QUPLOG_LOG_WRITE((uint32)pQupAddr, 2, "QUP[0x%x]: Write:  QUP_STATE[STATE] = %x", (uint32)pQupAddr, HAL_QUPE_RUNSTATE_CMD_RESET);
         }
         QUPE_OUTF(pQupAddr, QUP_STATE, STATE, HAL_QUPE_RUNSTATE_CMD_RESET);
         //QUPLOG_LOG_WRITE((uint32)pQupAddr, 2, "QUP[0x%x]: Write:  QUP_STATE[STATE] = %x", (uint32)pQupAddr, HAL_QUPE_RUNSTATE_CMD_RESET);
         break;

     case HAL_QUPE_RUNSTATE_RUN   :
         QUPE_OUTF(pQupAddr, QUP_STATE, STATE, HAL_QUPE_RUNSTATE_CMD_RUN);
         //QUPLOG_LOG_WRITE((uint32)pQupAddr, 2, "QUP[0x%x]: Write:  QUP_STATE[STATE] = %x", (uint32)pQupAddr, HAL_QUPE_RUNSTATE_CMD_RUN);
         break;

      case HAL_QUPE_RUNSTATE_PAUSE :
         QUPE_OUTF(pQupAddr, QUP_STATE, STATE, HAL_QUPE_RUNSTATE_CMD_PAUSE);
         //QUPLOG_LOG_WRITE((uint32)pQupAddr, 2, "QUP[0x%x]: Write:  QUP_STATE[STATE] = %x", (uint32)pQupAddr, HAL_QUPE_RUNSTATE_CMD_PAUSE);
         break;

      default:
         return (HAL_QUPE_RESULT_INVALID_ARG);
   }

   return HAL_QUPE_RESULT_SUCCESS;
}

/** @brief Gets the run state of the QUPe.
    @param[in]   pQupAddr Qup Block address.
    @return QUPe run state.
  */
HAL_qupe_RunStateType
HAL_qupe_GetRunState
(
   uint8                 *pQupAddr
)
{
   uint32 uStateField;
   uint32 uValidField;
   uint32 uRegVal;

   uRegVal = QUPE_IN(pQupAddr, QUP_STATE);
   uValidField = (uRegVal & (QUPE_FMSK(QUP_STATE, STATE_VALID))) >>
         QUPE_SHFT(QUP_STATE, STATE_VALID);
   if ( 1 == uValidField ) {
      uStateField = (uRegVal & (QUPE_FMSK(QUP_STATE, STATE))) >>
         QUPE_SHFT(QUP_STATE, STATE);
   }
   else {
      uStateField = HAL_QUPE_RUNSTATE_INVALID;
   }

   //uTmpField = QUPE_INF(pQupAddr, QUP_STATE, STATE);
   QUPLOG_LOG_READ((uint32)pQupAddr, 4,
                   "QUP[0x%x]: Read: QUP_STATE=0x%x, QUP_STATE[STATE]=0x%x, "
                   "QUP_STATE[STATE_VALID]=0x%x",
                   (uint32)pQupAddr, uRegVal,uStateField, uValidField);
   return (HAL_qupe_RunStateType)uStateField;
}

/**
 * This function configures the specified QUP Mini core selection.
 * 
 * @param[in]  pQupAddr Qup Block address.
 * @param eMiniCoreType - The mini core type.
 */
void HAL_qupe_SetSelectedMinicore
(
   uint8  *pQupAddr, 
   HAL_qupe_MiniCoreType eMiniCoreType
)
{
   QUPE_OUTF(pQupAddr, QUP_CONFIG, MINI_CORE, eMiniCoreType);
   QUPLOG_LOG_WRITE((uint32)pQupAddr, 2, "QUP[0x%x]: Write: QUP_CONFIG[MINI_CORE] = %x", (uint32) pQupAddr, eMiniCoreType);
} /* END HAL_qupe_SetSelectedMinicore */

uint32 HAL_qupe_GetErrStatusFlags (uint8  *pQupAddr)
{
   uint32 uRegVal;
   
   uRegVal = QUPE_IN(pQupAddr, QUP_ERROR_FLAGS);
   QUPLOG_LOG_READ((uint32)pQupAddr, 2,
                   "QUP[0x%x]: Read: QUP_ERROR_FLAGS , VAL:0x%x",
                   (uint32)pQupAddr, uRegVal);   
   return uRegVal;
}

uint32 HAL_qupe_GetOpStatusFlags (uint8  *pQupAddr)
{
   uint32 uRegVal;

   uRegVal = QUPE_IN(pQupAddr, QUP_OPERATIONAL);
   QUPLOG_LOG_READ((uint32)pQupAddr, 2,
                   "QUP[0x%x]: Read: QUP_OPERATIONAL , VAL:0x%x",
                   (uint32)pQupAddr, uRegVal);     
   return uRegVal;
}

HAL_qupe_ResultType
HAL_qupe_ClearOpStatusFlags
(
   uint8         *pQupAddr,
   const uint32  uOpFlagsBitmap
)
{
   if(uOpFlagsBitmap & (~HAL_QUPE_OPSTATE_FIELD)){
      return (HAL_QUPE_RESULT_INVALID_ARG);
   }
   QUPE_OUT(pQupAddr, QUP_OPERATIONAL, uOpFlagsBitmap);
   QUPLOG_LOG_WRITE((uint32)pQupAddr, 2, "QUP[0x%x]: Write:  QUP_OPERATIONAL = 0x%x", (uint32)pQupAddr, uOpFlagsBitmap);
   return HAL_QUPE_RESULT_SUCCESS;
}


uint32
HAL_qupe_GetNumOutputFifoBlockSlots
(
   uint8  *pQupAddr
)
{
   uint32 uOutBlockSizeFld;

   uOutBlockSizeFld   = QUPE_INF(pQupAddr, QUP_IO_MODES, OUTPUT_BLOCK_SIZE);
   QUPLOG_LOG_READ((uint32)pQupAddr, 2,
                   "QUP[0x%x]: Read: QUP_IO_MODES[OUTPUT_BLOCK_SIZE] , VAL:0x%x",
                   (uint32)pQupAddr, uOutBlockSizeFld);
   switch(uOutBlockSizeFld)
   {
      case 0: return 1;
      case 1: return 4;
      case 2: return 8;
      default: return 0;
   }
}

uint32
HAL_qupe_GetNumInputFifoBlockSlots
(
   uint8  *pQupAddr
)
{
   uint32 uInBlockSizeFld   = QUPE_INF(pQupAddr, QUP_IO_MODES, INPUT_BLOCK_SIZE);
   QUPLOG_LOG_READ((uint32)pQupAddr, 2,
                   "QUP[0x%x]: Read: QUP_IO_MODES[INPUT_BLOCK_SIZE] , VAL:0x%x",
                   (uint32)pQupAddr, (int32)uInBlockSizeFld);
   switch(uInBlockSizeFld)
   {
      case 0: return 1;
      case 1: return 4;
      case 2: return 8;
      default: return 0;
   }
}


/** @brief Reads the RTL info and returns it.
    @param[in]  pQupAddr Qup Block address.
    @param[in]  pHwInfo Pointer to struct used to store hw info.
    @return Nothing.
  */
void HAL_qupe_GetHwInfo
(
   uint8               *pQupAddr          ,
   HAL_qupe_HwInfoType *pHwInfo
)
{
   uint32 uTmpField;
   HAL_QUPE_ASSERT(NULL == pHwInfo);

   pHwInfo->uNumOutputBlockSlots = HAL_qupe_GetNumOutputFifoBlockSlots(pQupAddr);
   pHwInfo->uNumInputBlockSlots  = HAL_qupe_GetNumInputFifoBlockSlots(pQupAddr);

   uTmpField = QUPE_INF(pQupAddr, QUP_IO_MODES, INPUT_FIFO_SIZE);
   QUPLOG_LOG_READ((uint32)pQupAddr, 2,
                   "QUP[0x%x]: Read: QUP_IO_MODES[INPUT_FIFO_SIZE] , VAL:0x%x",
                   (uint32)pQupAddr, (int32)uTmpField);
   pHwInfo->uNumInputBlocks   = 1 << (uTmpField + 1);

   uTmpField = QUPE_INF(pQupAddr, QUP_IO_MODES, OUTPUT_FIFO_SIZE);
   QUPLOG_LOG_READ((uint32)pQupAddr, 2,
                   "QUP[0x%x]: Read: QUP_IO_MODES[OUTPUT_FIFO_SIZE] , VAL:0x%x",
                   (uint32)pQupAddr, uTmpField);
   pHwInfo->uNumOutputBlocks  = 1 << (uTmpField + 1);

   pHwInfo->uNumInputSlots = pHwInfo->uNumInputBlocks * pHwInfo->uNumInputBlockSlots;
   pHwInfo->uNumOutputSlots = pHwInfo->uNumOutputBlocks * pHwInfo->uNumOutputBlockSlots;

   pHwInfo->uHWVersion = QUPE_IN(pQupAddr,QUP_HW_VERSION);
   QUPLOG_LOG_READ((uint32)pQupAddr, 2,
                   "QUP[0x%x]: Read: QUP_HW_VERSION , VAL:0x%x",
                   (uint32)pQupAddr, (int32)pHwInfo->uHWVersion);
}

/** @brief Puts a word into output fifo.
    @param[in]  pQupAddr Qup Block address.
    @param[in]  uOutWord the word to be put in output fifo.
    @return HAL_QUPE_RESULT_SUCCESS if successful, error code otherwise.
  */
HAL_qupe_ResultType
HAL_qupe_PutWordIntoOutFifo
(
   uint8        *pQupAddr,
   const uint32 uOutWord
)
{
   QUPE_OUTI(pQupAddr, QUP_OUTPUT_FIFOc, 0, uOutWord);
   QUPLOG_LOG_WRITE((uint32)pQupAddr, 2, "QUP[0x%x]: Write:  QUP_OUTPUT_FIFOc[] = %x", 
                    (uint32)pQupAddr, uOutWord);
   return HAL_QUPE_RESULT_SUCCESS;
}

HAL_qupe_ResultType
HAL_qupe_GetWordFromInFifo
(
   uint8  *pQupAddr,
   uint32 *pInWord
)
{
   uint32 uRegVal;

   if(NULL == pInWord){
      return (HAL_QUPE_RESULT_INVALID_ARG);
   }

   /* Reading from address 0 emties the input fifo. */
   uRegVal = QUPE_INI(pQupAddr, QUP_INPUT_FIFOc, 0);
   QUPLOG_LOG_READ((uint32)pQupAddr, 2,
                   "QUP[0x%x]: Read: QUP_INPUT_FIFO0 , VAL:0x%x",
                   (uint32)pQupAddr, uRegVal);
   *pInWord = uRegVal;
   return HAL_QUPE_RESULT_SUCCESS;
}
