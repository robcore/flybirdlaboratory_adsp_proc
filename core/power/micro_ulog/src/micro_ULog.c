/*============================================================================
  micro_ULog.c

  Public-facing/support micro_ULog functions.

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
============================================================================*/
/* $Header: //components/rel/core.adsp/2.6.1/power/micro_ulog/src/micro_ULog.c#1 $ */
#include "micro_ULog.h"
#include "CoreVerify.h"

//global pointer to the ULogs.  The compiler initializes globals to zero. 
MICRO_LOG_CONTEXT micro_ulogContext;

/*---------------------------------------------------------------------------------------
                              Static Function Prototypes                                 
---------------------------------------------------------------------------------------*/
static micro_ULogResult micro_ULogInternal_STMWrite(micro_ULogHandle h, uint32 firstMsgCount,
     const char * firstMsgContent, uint32 secondMsgCount, const char * secondMsgContent);

static micro_ULogResult micro_ULogInternal_Write(micro_ULogHandle h, uint32 firstMsgCount,
     const char * firstMsgContent, uint32 secondMsgCount, const char * secondMsgContent);

static micro_ULogResult micro_ULogInternal_IsEnabled(micro_ULogHandle h, 
     MICRO_ULOG_CORE_VTABLE ** core);


/*---------------------------------------------------------------------------------------
 VTable specifications
---------------------------------------------------------------------------------------*/
static MICRO_ULOG_CORE_VTABLE CoreVtableSTM = 
{
  micro_ULogInternal_STMWrite,
};

static MICRO_ULOG_CORE_VTABLE CoreVtableNormal = 
{
  micro_ULogInternal_Write,
};


/*---------------------------------------------------------------------------------------
                                  INLINE FUNCTIONS
---------------------------------------------------------------------------------------*/

/**
 * <!-- micro_ULogInternal_LockGet -->
 *
 * @brief Use the appropriate type of lock for the log. 
 *
 * @param log : Pointer to the ULog to lock.
 */
#ifdef LOCKABLE_LOGS_SUPPORTED
static MICRO_ULOG_INLINE void micro_ULogInternal_LockGet(MICRO_ULOG_TYPE * log)
{
   if(log->lockHandle)
   {
     MICRO_ULOG_LOCK_GET(log->lockHandle);
   }
}

/**
 * <!-- micro_ULogInternal_LockRelease -->
 *
 * @brief Use the appropriate type of unlock for the log. 
 *
 * @param log : Pointer to a ULog.
 */
static MICRO_ULOG_INLINE void micro_ULogInternal_LockRelease(MICRO_ULOG_TYPE * log)
{
   if(log->lockHandle)
   {
     MICRO_ULOG_LOCK_RELEASE(log->lockHandle);
   }
}
#endif

/*---------------------------------------------------------------------------------------
  micro_ULogInternal_FreeSpaceForNewMsg
  Returns MICRO_ULOG_SUCCESS if it is able to free space (by invalidating older
  messages) for the next incoming message, MICRO_ULOG_ERROR if not
---------------------------------------------------------------------------------------*/
static MICRO_ULOG_INLINE micro_ULogResult micro_ULogInternal_FreeSpaceForNewMsg(MICRO_ULOG_TYPE * log,
	                                                                        uint32 requestingSize)
{
  uint32 oldMsgSize;
  uint32 bufferNeeded;
  uint32 freeAttempts=0; 

  //Impossible to make space if the request amount is bigger than the log. 
  if (requestingSize > log->bufSize){
    log->usageData |= MICRO_ULOG_ERR_LARGEMSG;
    return MICRO_ULOG_ERROR;
  }

  // Determine if there is enough free memory for the new message.  
  // If not, remove old messages until there is enough room.
  // 
  // In order to add the message::
  // Current message data in buffer = write - readWriter
  // current message data + new message <= Buffer Size
  bufferNeeded = (log->write - log->readWriter) + requestingSize;
  
  //loop until the amount of ram needed to hold all the existing
  //messages plus the new one will fit into the log buffer size. 
  while (bufferNeeded > log->bufSize)
  {
    // Detect a wrap condition. We're about to move the readWriter
    // forwards to free up space. This will overwrite the oldest logs.
    // 99% of the time SW on the device isn't reading the logs so read==0 
    // and it's a 0 = 0 check that indicates the log has wrapped for the 
    // first time. We indicate this wrap with MICRO_ULOG_LOG_WRAPPED.
    if (log->read == log->readWriter)
    {
      log->usageData|= MICRO_ULOG_LOG_WRAPPED;
    }

    // Remove the oldest message to free memory for the new message.
    oldMsgSize = ((*((uint32 *)&log->buffer[log->readWriter & log->bufSizeMask]) & MICRO_ULOG_LENGTH_MASK) >> MICRO_ULOG_LENGTH_SHIFT);

    oldMsgSize = MICRO_ULOGINTERNAL_PADCOUNT(oldMsgSize);
    log->readWriter += oldMsgSize;
    bufferNeeded -= oldMsgSize;

    // We've seen rare hardware memory corruption cases where this loop gets  
    // stuck because these critical pointers get corrupted.  
    // If the log is ever in an impossible state.  Reset it. 
    // The log records that it has been reset for debug later if needed.
    if ((log->write - log->readWriter)>log->bufSize){
      micro_ULog_ResetLog((micro_ULogHandle)log);
      bufferNeeded = requestingSize;
    }

    //Making space for new logs relies on the integrity of
    //previous logs. In rare hardware memory corruption cases, there can
    //be problems with this loop. As a safety, this loop cannot run more
    //than the times needed to free space for the largest (ULOG_MAX_MSG_SIZE)
    //message.  There is no log msg smaller than 8 bytes so any attempt to
    //make space more than ULOG_MAX_MSG_SIZE/8 times should cause a log reset. 
    freeAttempts++;
    if ((freeAttempts>MICRO_ULOG_MAX_MSG_SIZE/8) || (oldMsgSize > MICRO_ULOG_MAX_MSG_SIZE) || (oldMsgSize < 8)){
      micro_ULog_ResetLog((micro_ULogHandle)log);
      bufferNeeded = requestingSize;
    }
  }
  return MICRO_ULOG_SUCCESS;
}


/*---------------------------------------------------------------------------------------
  micro_ULogInternal_ReadyForMessage
  Prepares the log for the next message, removing old entries if necessary. Fails if
  the message is too big (>128 bytes) or if space cannot be cleared.
---------------------------------------------------------------------------------------*/
static MICRO_ULOG_INLINE micro_ULogResult micro_ULogInternal_ReadyForMessage(MICRO_ULOG_TYPE * log,
	                                                                     uint32 msgCount)
{
  uint32 requestingSize = MICRO_ULOGINTERNAL_PADCOUNT(msgCount);

  if (requestingSize > MICRO_ULOG_MAX_MSG_SIZE)
  {
    return(MICRO_ULOG_ERROR);
  }
  
  if (micro_ULogInternal_FreeSpaceForNewMsg(log, requestingSize) == MICRO_ULOG_ERROR){
    return(MICRO_ULOG_ERROR);
  }

  return MICRO_ULOG_SUCCESS;
}


/*---------------------------------------------------------------------------------------
  micro_ULogInternal_UseFastRam
  Checks to see if fast RAM writes can be used, or if VTable writes must be
  used instead.
---------------------------------------------------------------------------------------*/
static MICRO_ULOG_INLINE micro_ULogResult micro_ULogInternal_UseFastRam(MICRO_ULOG_TYPE * log)
{
    if (log->transport!=MICRO_ULOG_TRANSPORT_RAM){
      return MICRO_ULOG_ERROR;
    } 
    return MICRO_ULOG_SUCCESS;
}


/*---------------------------------------------------------------------------------------
  micro_ULogInternal_FastFmtSizeTS
  Optimized function to write the format, message size, and timestamp to RAM,
  if possible.
---------------------------------------------------------------------------------------*/
static MICRO_ULOG_INLINE micro_ULogResult micro_ULogInternal_FastFmtSizeTS(micro_ULogHandle h,
                                                                     uint32 size,
                                                                     uint32 msg_format)
{
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;
  uint32* wordPtr;
  uint64 timestamp;
  // See if this log is an ordinary RAM log.
  //See if this is an ordinary RAM ULog.  We can do our fastest writes if it is. 
  if (micro_ULogInternal_UseFastRam(log) == MICRO_ULOG_SUCCESS)
  {
    #ifdef LOCKABLE_LOGS_SUPPORTED
    micro_ULogInternal_LockGet(log);
    #endif
    if(micro_ULogInternal_ReadyForMessage((MICRO_ULOG_TYPE *)h, size) == MICRO_ULOG_ERROR)
    {
      #ifdef LOCKABLE_LOGS_SUPPORTED
      micro_ULogInternal_LockRelease(log);
      #endif
      return(MICRO_ULOG_FAST_TO_RAM_FAIL);
    }

    // len/fmt word
    wordPtr = (uint32*)&(log->buffer[log->write & log->bufSizeMask]);
    //save this important index and size to use at the end of the write
    log->transactionWriteStart = log->write;
    log->transactionWriteCount = size;
    *wordPtr = msg_format;  //keep the size zero until the msg is completely written.
    log->write+=4;

    //Timestamp
    timestamp = MICRO_ULOG_GETTIME64;

    //write the lower 32 bits of the timestamp
    wordPtr = (uint32*)&(log->buffer[log->write & log->bufSizeMask]);
    *wordPtr = (uint32)timestamp;
    log->write+=4;

    //write the upper 32 bits of the timestamp
    wordPtr = (uint32*)&(log->buffer[log->write & log->bufSizeMask]);
    *wordPtr = (uint32)((uint64)timestamp>>32);
    log->write+=4;

    return MICRO_ULOG_FAST_TO_RAM_SUCCESS;
  }

  return MICRO_ULOG_FAST_TO_RAM_FAIL;

}

/*----------------------------------------------------------------------------
 micro_ULog_ConvertSize
 Ulog sizes are always a power of 2. 64 bytes is the minimum. 
----------------------------------------------------------------------------*/
static MICRO_ULOG_INLINE uint32 micro_ULogInternal_ConvertSize(uint32 size)
{
  uint32 output;

  if (size < MICRO_ULOG_MINIMUM_LOG_SIZE)
  {
    // Require logs to be at least 64 bytes long.
    size = MICRO_ULOG_MINIMUM_LOG_SIZE;
  }

  // Ensure the size is an even power of 2.  
  output = 0;
  while(size != 1)
  {
    size >>= 1;
    output++;
  }
  output = 1 << output;

  return(output);
}

/*---------------------------------------------------------------------------------------
  micro_ULogInternal_MemoryAssignLog
  Creates a new top-level micro_ULog structure in the specified memory.
---------------------------------------------------------------------------------------*/
static MICRO_ULOG_INLINE micro_ULogResult micro_ULogInternal_MemoryAssignLog(micro_ULogHandle * h,
                                                                     void * bufferPtr,
                                                                     uint32 bufferSize,
                                                                     const char * logName)
{
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)bufferPtr;

  if (h == NULL){
    return MICRO_ULOG_ERROR;
  }
  
  // ensure the buffer is big enough
  if ( sizeof(MICRO_ULOG_TYPE) > bufferSize )
  {
    return MICRO_ULOG_ERR_BUFFER_TOO_SMALL;
  }

  // zero this structure's space out
  memset(bufferPtr, 0, sizeof(MICRO_ULOG_TYPE));

  // ensure the name is not too big to fit into the buffer, then set the log name
  if((strlen(logName) > MICRO_ULOG_MAX_NAME_SIZE) || (strlen(logName) == 0))
  {
    return MICRO_ULOG_ERR_INVALIDNAME;
  }
  MICRO_ULOG_STRLCPY(log->name, logName, MICRO_ULOG_MAX_NAME_SIZE+1);
  
  // Link the log into the list
  log->next = micro_ulogContext.logHead;
  micro_ulogContext.logHead = log;
  
  // set flags (see ULogCore_LogCreate in ULCoreInterface.c)
  // Copy input parameters to log header.
  log->version               = MICRO_ULOG_TYPE_LOG_HEADER_VERSION;
  log->stmPort               = 0;
  log->transport             = MICRO_ULOG_TRANSPORT_RAM;
  log->feature_flags1        = log->feature_flags1 | MICRO_ULOG_FF1_64_BIT_TS; 

  *h = log;
  
  return MICRO_ULOG_SUCCESS;
}


/*---------------------------------------------------------------------------------------
  micro_ULogInternal_MemoryAssign
  Assigns given memory to a ULog component, such as the message buffer, ReaderCore, etc
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULogInternal_MemoryAssign(micro_ULogHandle h,
                                                 MICRO_ULOG_VALUE_ID id,
                                                 void * bufferPtr,
                                                 uint32 bufferSize)
{
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;
  micro_ULogResult result = MICRO_ULOG_ERROR;
  uint32 realSize;
  if (h == NULL)
  {
    return MICRO_ULOG_ERROR;
  }

  if (((uint32)bufferPtr & 0x03) != 0)  // If the ptr is not word aligned...
  {
    return(MICRO_ULOG_ERROR);
  }

  switch(id)
  {
    case MICRO_ULOG_VALUE_BUFFER:
      // Only assign memory if we don't already have some assigned
      if (log->buffer == NULL)
      {
        realSize = micro_ULogInternal_ConvertSize(bufferSize);
          
        // Make sure we were given enough memory.
        if (realSize > bufferSize)
        {
          result = MICRO_ULOG_ERROR;
          break;
        }
        log->buffer = (char *)bufferPtr;
        log->bufSize = realSize;
        log->bufSizeMask = realSize - 1;
        result = MICRO_ULOG_SUCCESS;
      }
      break;
    case MICRO_ULOG_VALUE_LOCK:
      #ifdef LOCKABLE_LOGS_SUPPORTED
      if (log->lockHandle == NULL)
      {
        log->lockHandle = (MICRO_ULOG_MUTEX_HANDLE_TYPE)bufferPtr;
        result = MICRO_ULOG_SUCCESS;
      }
      #endif
      break;
    default:
      result = MICRO_ULOG_ERROR;
      break;
  }

  // Flag the log as defined after it's buffer is assigned.
  if (log->buffer != NULL)
  {
    log->logStatus |= MICRO_ULOG_STATUS_DEFINED;
  }

  return(result);
}


/*----------------------------------------------------------------------------
                       REGULAR (NON-INLINE) FUNCTIONS
----------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------
  micro_ULog_CreateLog
  Assigns from the given memory space all of the components of a micro_ULog: 
   the top-level micro_ULog structure and the message buffer. 
   The message buffer is sized as large as possible but must be a power of 2 and a minimum 
   64 bytes. CreateNew uses micro_ULog_MemoryAssignLog and micro_ULog_MemoryAssign internally
   to set up each of these components. Alternatively, the user can call these two functions
   manually and follow with a call to micro_ULog_Enable. 
  Returns: MICRO_ULOG_SUCCESS on success
           MICRO_ULOG_ERR_BUFFER_TOO_SMALL if the provided memory cannot provide at least
            64 bytes for a message buffer, in addition to the other components.
           MICRO_ULOG_ERROR on other errors
  Parameters: h: will be returned as a handle to the new micro_ULog
              logName: a string to name the log (max 23 characters plus null terminator)
              mem: pointer to the memory to be used for the ULog header and log buffer.  
              effectiveMessageBufferSize: returns the actual size of the new message
               buffer. Optionally, pass NULL to prevent returning this value.
              memSize: the size of memory pointed to by 'mem' 
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_CreateLog(micro_ULogHandle * h,
                                      const char * logName,
                                      char * mem,
                                      uint32 * effectiveMessageBufferSize,
                                      uint32 memSize)
{
  micro_ULogResult result;
  char * tempMemPtr = mem;
  uint32 tempMemPtrSize = memSize;
  uint32 realBufferSize;
  uint32 remainingSpace = memSize - sizeof(MICRO_ULOG_TYPE);

  if (mem == NULL || h == NULL){
    return MICRO_ULOG_ERROR;
  }

  // verify that there is enough space for at least a minimum-sized buffer
  if (remainingSpace < 64){
    return MICRO_ULOG_ERR_BUFFER_TOO_SMALL;
  }

  // round down to the next power of two
  realBufferSize = micro_ULogInternal_ConvertSize(remainingSpace);

  // zero it out, to have a nice clean structure. 
  memset((void*)mem, 0, memSize);

  // assign the MICRO_ULOG_TYPE
  if (MICRO_ULOG_SUCCESS != (result = micro_ULogInternal_MemoryAssignLog(h, (void *)mem, memSize, logName)))
  {
    return result;
  }
  tempMemPtr += sizeof(MICRO_ULOG_TYPE);
  tempMemPtrSize -= sizeof(MICRO_ULOG_TYPE);
  // do word-alignment just in case
  if ((uint32)tempMemPtr & 0x03){
    tempMemPtr = (char*)(((uint32)tempMemPtr + 4) & (~0x03));
    tempMemPtrSize = tempMemPtrSize & (~0x03);
  }

  // assign the message buffer
  if (MICRO_ULOG_SUCCESS != (result = micro_ULogInternal_MemoryAssign(*h, MICRO_ULOG_VALUE_BUFFER, tempMemPtr, realBufferSize)))
  {
    return result;
  }
  tempMemPtr += realBufferSize;
  tempMemPtrSize -= realBufferSize;
  // this will automatically be word-aligned as buffers are a power of 2, greater than 64 bytes

  // Enable the log and finish up
  micro_ULog_Enable(*h);

  if (effectiveMessageBufferSize != NULL) {
    *effectiveMessageBufferSize = realBufferSize;
  }

  return MICRO_ULOG_SUCCESS;
}

/*---------------------------------------------------------------------------------------
  micro_ULog_CreateLockableLog
  Assigns from the given memory space all of the components of a micro_ULog with a lock: 
   the top-level micro_ULog structure, the message buffer, and the lock. 
   The message buffer is sized as large as possible but must be a power of 2 and a minimum 
   64 bytes. CreateNew uses micro_ULog_MemoryAssignLog and micro_ULog_MemoryAssign internally
   to set up each of these components. Alternatively, the user can call these two functions
   manually and follow with a call to micro_ULog_Enable. 
  Returns: MICRO_ULOG_SUCCESS on success
           MICRO_ULOG_ERR_BUFFER_TOO_SMALL if the provided memory cannot provide at least
            64 bytes for a message buffer, in addition to the other components.
           MICRO_ULOG_ERROR on other errors
  Parameters: h: will be returned as a handle to the new micro_ULog
              logName: a string to name the log (max 23 characters plus null terminator)
              mem: pointer to the memory to be used for the ULog header and log buffer.  
              effectiveMessageBufferSize: returns the actual size of the new message
               buffer. Optionally, pass NULL to prevent returning this value.
              memSize: the size of memory pointed to by 'mem' 
---------------------------------------------------------------------------------------*/
#ifdef LOCKABLE_LOGS_SUPPORTED
micro_ULogResult micro_ULog_CreateLockableLog(micro_ULogHandle * h,
                                              const char * logName,
                                              char * mem,
                                              uint32 * effectiveMessageBufferSize,
                                              uint32 memSize)
{
  micro_ULogResult result;
  char * tempMemPtr = mem;
  uint32 tempMemPtrSize = memSize;
  uint32 realBufferSize;
  uint32 remainingSpace = memSize - sizeof(MICRO_ULOG_TYPE) - sizeof(MICRO_ULOG_MUTEX_TYPE);
  MICRO_ULOG_TYPE * log;

  if ( mem == NULL || h == NULL ){
    return MICRO_ULOG_ERROR;
  }

  // verify that there is enough space for at least a minimum-sized buffer
  if (remainingSpace < 64){
    return MICRO_ULOG_ERR_BUFFER_TOO_SMALL;
  }

  // round down to the next power of two
  realBufferSize = micro_ULogInternal_ConvertSize(remainingSpace);

  // zero it out, to have a nice clean structure. 
  memset((void*)mem, 0, memSize);

  // assign the MICRO_ULOG_TYPE
  if (MICRO_ULOG_SUCCESS != (result = micro_ULogInternal_MemoryAssignLog(h, (void *)mem, memSize, logName)))
  {
    return result;
  }

  tempMemPtr += sizeof(MICRO_ULOG_TYPE);
  tempMemPtrSize -= sizeof(MICRO_ULOG_TYPE);
  // do word-alignment just in case
  if ((uint32)tempMemPtr & 0x03){
    tempMemPtr = (char*)(((uint32)tempMemPtr + 4) & (~0x03));
    tempMemPtrSize = tempMemPtrSize & (~0x03);
  }

  // assign the message buffer
  if (MICRO_ULOG_SUCCESS != (result = micro_ULogInternal_MemoryAssign(*h, MICRO_ULOG_VALUE_BUFFER, tempMemPtr, realBufferSize)))
  {
    return result;
  }
  tempMemPtr += realBufferSize;
  tempMemPtrSize -= realBufferSize;
 
  //create lock
  log = (MICRO_ULOG_TYPE*)*h;
  if (MICRO_ULOG_SUCCESS != (result = micro_ULogInternal_MemoryAssign(*h, MICRO_ULOG_VALUE_LOCK, tempMemPtr, sizeof(MICRO_ULOG_MUTEX_TYPE))))
  {
    return result;
  }
  tempMemPtr += sizeof(MICRO_ULOG_MUTEX_TYPE);
  tempMemPtrSize -= sizeof(MICRO_ULOG_MUTEX_TYPE);
  
  CORE_VERIFY_PTR( log->lockHandle );
  MICRO_ULOG_LOCK_INIT(log->lockHandle);

  if (log->lockHandle == NULL)
  {
    //set error bit(s) in the status flag to document why the create failed
    log->logStatus = MICRO_ULOG_ERR_INITINCOMPLETE;
    return(MICRO_ULOG_ERROR);
  }

  // Enable the log and finish up
  micro_ULog_Enable(*h);

  if (effectiveMessageBufferSize != NULL) {
    *effectiveMessageBufferSize = realBufferSize;
  }

  return MICRO_ULOG_SUCCESS;
}
#endif


/*----------------------------------------------------------------------------
 micro_ULogInternal_IsEnabled
 Check whether a log is enabled and set its ULOG_CORE_VTABLE to the correct
  function table. 
----------------------------------------------------------------------------*/
static micro_ULogResult micro_ULogInternal_IsEnabled(micro_ULogHandle h,
	                                                   MICRO_ULOG_CORE_VTABLE ** core)
{
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;

  if (log == NULL)
  {
    return (MICRO_ULOG_ERROR);
  }
  switch (log->transport){
    case MICRO_ULOG_TRANSPORT_RAM:
      *core = &CoreVtableNormal;
      break;

    case MICRO_ULOG_TRANSPORT_STM:
      *core = &CoreVtableSTM;
      break;

    case MICRO_ULOG_TRANSPORT_ALTERNATE:
      *core = log->altTransportVTable;
      break;
  }

	if (log->logStatus & MICRO_ULOG_STATUS_ENABLED)
	{
    return(MICRO_ULOG_SUCCESS);
  }
  return (MICRO_ULOG_ERROR);
}


/*---------------------------------------------------------------------------------------
  micro_ULog_RealTimeVprintf
  Writes printf data to the specified log. The printf formating is
  not executed until the log is read.
  Example usage: micro_ULog_RealTimeVprintf(handle, 3, "test %d: %s", 1, "complete");
  Returns: MICRO_ULOG_SUCCESS on success
           MICRO_ULOG_ERROR on error
  Parameters: h: the log to which to write the data
              dataCount: the number of data word parameters
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_RealTimeVprintf(micro_ULogHandle h, uint32 dataCount, const char * formatStr, va_list ap)
{
  uint32 total_size;
  uint32 dataArray[15];
  uint64 timestamp;
  uint32 * dataPtr = dataArray;
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;
  uint32* wordPtr;
  uint32 i;
  micro_ULogResult retval = MICRO_ULOG_ERROR;

  if ((dataCount>10) || (h==NULL) || !(log->logStatus & MICRO_ULOG_STATUS_ENABLED)){
    return(MICRO_ULOG_ERROR);
  }

  //size/fmt + TS + data
  total_size = 8 + MICRO_ULOG_TIMESTAMP_SIZE + dataCount*4; 

  switch(micro_ULogInternal_FastFmtSizeTS(h, total_size, MICRO_ULOG_SUBTYPE_REALTIME_PRINTF)){

    case MICRO_ULOG_FAST_TO_RAM_SUCCESS:
      //Success.  We have the lock, and will release it after we finish this msg. 
      //pointer to the format string
      wordPtr = (uint32*)&(log->buffer[log->write & log->bufSizeMask]);
      *wordPtr = (uint32) formatStr;
      log->write+=4;

      //any arguments
      for(i = 0; i < dataCount; i++)
      {
        wordPtr = (uint32*)&(log->buffer[log->write & log->bufSizeMask]);
        *wordPtr = (uint32)va_arg(ap, uint32);
        log->write+=4;
      }

      //fill in the size
      wordPtr = (uint32*)&(log->buffer[log->transactionWriteStart & log->bufSizeMask]);
      *wordPtr |= (((log->transactionWriteCount)<<MICRO_ULOG_LENGTH_SHIFT)& MICRO_ULOG_LENGTH_MASK);

      #ifdef LOCKABLE_LOGS_SUPPORTED
      micro_ULogInternal_LockRelease(log);
      #endif
      return (MICRO_ULOG_SUCCESS);


    case MICRO_ULOG_FAST_TO_RAM_UNAVAIL:
      //It's not a normal RAM log, fill in the array and call the generic writes. 
      if(micro_ULogInternal_IsEnabled(h, &log->altTransportVTable) == TRUE)   
      {
        *dataPtr++ = MICRO_ULOG_SUBTYPE_REALTIME_PRINTF; 
        timestamp = MICRO_ULOG_GETTIME64;
        *dataPtr++ = (uint32)timestamp;
        *dataPtr++ = (uint32)((uint64)timestamp>>32);
        *dataPtr++ = (uint32)timestamp;
        *dataPtr++ = (uint32)((uint64)timestamp>>32);

        *dataPtr++ = (uint32)formatStr;

        for(i = 0; i < dataCount; i++)
        {
          *dataPtr++ = va_arg(ap, uint32);
        }

        retval = log->altTransportVTable->write (h, total_size, (char *)dataArray, 0, NULL);
      }

      return retval;
      
      case MICRO_ULOG_FAST_TO_RAM_FAIL:
        //the log is disabled, or some argument is wrong. 
        return(MICRO_ULOG_ERROR);

      default:
        return(MICRO_ULOG_ERROR);
  }

  return(MICRO_ULOG_ERROR);
}


/*---------------------------------------------------------------------------------------
  micro_ULog_RealTimePrintf
  Writes printf data to the specified log. The printf formating is
  not executed until the log is read.
  Example usage: micro_ULog_RealTimePrintf(handle, 3, "test %d: %s", 1, "complete");
  Returns: MICRO_ULOG_SUCCESS on success
           MICRO_ULOG_ERROR on error
  Parameters: h: the log to which to write the data
              dataCount: the number of data word parameters
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_RealTimePrintf(micro_ULogHandle h, uint32 dataCount,
                                           const char *formatStr, ...)
{
  va_list ap;
  micro_ULogResult status;

  va_start(ap, formatStr);
  status = micro_ULog_RealTimeVprintf(h, dataCount, formatStr, ap);
  va_end(ap);

  return(status);
}

/*---------------------------------------------------------------------------------------
  micro_ULog_ResetLog
  Should be used only rarely in anything but test code. "Resets" a log by moving the read
   and write pointers back to the beginning of the circular RAM buffer.
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_ResetLog(micro_ULogHandle h)
{
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;

  if (log == NULL)
  {
    return MICRO_ULOG_ERROR;
  }

  #ifdef LOCKABLE_LOGS_SUPPORTED
  micro_ULogInternal_LockGet(log);
  #endif
  //Set all the indexes back to zero and clear flags. 
  log->write = 0;
  log->readWriter = 0;
  log->read = 0;
  log->readFlags = 0;

  //set a the reset bit in the usageData variable.
  log->usageData = MICRO_ULOG_ERR_RESET;
  //Increment the resetCount so users will know a bit about how often this has happened.
  log->resetCount = log->resetCount + 1;  
  #ifdef LOCKABLE_LOGS_SUPPORTED
  micro_ULogInternal_LockRelease(log);
  #endif  

  return MICRO_ULOG_SUCCESS;
}


/*----------------------------------------------------------------------------
 micro_ULog_Enable 
 Enable and reset the log. 
----------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_Enable (micro_ULogHandle h)
{
  micro_ULogResult result = MICRO_ULOG_ERROR;
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;

  if (log == NULL)
  {
    return MICRO_ULOG_ERROR;
  }

  if (((log->logStatus & MICRO_ULOG_STATUS_DEFINED) == 0) || 
      (log->buffer == NULL))
  {
    result = MICRO_ULOG_ERR_INITINCOMPLETE;  
  }
  else if (log->logStatus & MICRO_ULOG_STATUS_ENABLED)
  {
    result = MICRO_ULOG_ERR_ALREADYENABLED;  
  }
  else
  {
    log->logStatus |= MICRO_ULOG_STATUS_ENABLED;

    result = MICRO_ULOG_SUCCESS;
  }
  return (result);
}


/*----------------------------------------------------------------------------
 micro_ULog_Disable
 Disable the log, preventing further writes until it is enabled again
----------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_Disable(micro_ULogHandle h)
{
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;
  micro_ULogResult result = MICRO_ULOG_ERROR;

  if (log == NULL)
  {
    return(MICRO_ULOG_ERROR);
  }

  #ifdef LOCKABLE_LOGS_SUPPORTED
  micro_ULogInternal_LockGet(log);
  #endif

  if (log->logStatus & MICRO_ULOG_STATUS_ENABLED)
  {
    log->logStatus &= ~MICRO_ULOG_STATUS_ENABLED;

    result = MICRO_ULOG_SUCCESS;
  }
  #ifdef LOCKABLE_LOGS_SUPPORTED
  micro_ULogInternal_LockRelease(log);
  #endif
  return (result);
}


/*---------------------------------------------------------------------------------------
  micro_ULogInternal_Write
  Does VTable writes to a log
---------------------------------------------------------------------------------------*/
static micro_ULogResult micro_ULogInternal_Write(micro_ULogHandle h,  
                                                 uint32 firstMsgCount,  
                                                 const char * firstMsgContent, 
                                                 uint32 secondMsgCount,  
                                                 const char * secondMsgContent)
{

  /* Stub method.
     This is not used by the current micro_ULog APIs. If future APIs require this VTable
     write functionality, this function should be filled in appropriately.
  */

  return MICRO_ULOG_SUCCESS;
}


/*----------------------------------------------------------------------------
 micro_ULogInternal_STMWrite
 Does VTable QDSS writes to a log
----------------------------------------------------------------------------*/
static micro_ULogResult micro_ULogInternal_STMWrite(micro_ULogHandle h,  
                                                    uint32 firstMsgCount,  
                                                    const char * firstMsgContent, 
                                                    uint32 secondMsgCount,  
                                                    const char * secondMsgContent)
{
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;

  if (log->transport == MICRO_ULOG_TRANSPORT_STM){
    MICRO_ULOG_QDSS_TS_WRITE(log, firstMsgContent, firstMsgCount);
    if (secondMsgCount!=0)
    {
      MICRO_ULOG_QDSS_NO_TS_WRITE(log, secondMsgContent, secondMsgCount);
    }
  }

  return MICRO_ULOG_SUCCESS;
}

/*----------------------------------------------------------------------------
micro_ULog_SetTransportToRAM
----------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_SetTransportToRAM(micro_ULogHandle h)
{

  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;

  if(h == NULL)
  {
    return MICRO_ULOG_ERROR;
  }

  //deregister if leaving STM mode
  if (log->transport == MICRO_ULOG_TRANSPORT_STM)
  {
    MICRO_ULOG_QDSS_FREE(&log->stmPort);
  }

  log->transport = MICRO_ULOG_TRANSPORT_RAM;

  return MICRO_ULOG_SUCCESS;
}


/*----------------------------------------------------------------------------
micro_ULog_SetTransportToSTM
----------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_SetTransportToSTM(micro_ULogHandle h)
{
  micro_ULogResult result = MICRO_ULOG_ERROR;
  
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;

  if(h == NULL)
  {
    return MICRO_ULOG_ERROR;
  }
  
  if (log->transport != MICRO_ULOG_TRANSPORT_STM)
  {
    if (MICRO_ULOG_QDSS_ALLOC(&log->stmPort) == MICRO_ULOG_QDSS_SUCCESS){
      log->transport = MICRO_ULOG_TRANSPORT_STM;
      log->altTransportVTable = &CoreVtableSTM;
      result = MICRO_ULOG_SUCCESS;
    }
    else
    {
      result = MICRO_ULOG_ERROR;
    }
  }
  return result;
}


/*----------------------------------------------------------------------------
micro_ULog_SetTransportToAlt
Take a pointer to a ULOG_CORE_VTABLE and use it for future writes.
----------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_SetTransportToAlt(micro_ULogHandle h,
                                              MICRO_ULOG_CORE_VTABLE* newTansportVTable)
{
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;

  if(h == NULL)
  {
    return MICRO_ULOG_ERROR;
  }

  log->altTransportVTable = newTansportVTable;

  log->transport = MICRO_ULOG_TRANSPORT_ALTERNATE;
  
  return MICRO_ULOG_SUCCESS;
}


#ifdef FEATURE_FAST7
/*----------------------------------------------------------------------------
 RPM_ULog_Fast7WordWrite
 Writes 7 words to the specified log in a format compatible with Raw ULogs.
  This CANNOT be mixed with RealTime ULog writes to the same log.
----------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_Fast7WordWrite(micro_ULogHandle h,
                                           uint32 message[7])
{
  MICRO_ULOG_TYPE * log = (MICRO_ULOG_TYPE *)h;
  uint32 * buffer;
  uint32 bufSize;
  uint32 bufSizeMask;
  uint32 msgSize;
  uint32 msgTotalSize; // size + message
  uint32 size_idx;
  uint32 bufferNeeded;

  if (h == NULL){
    return MICRO_ULOG_ERROR;
  }

  if (micro_ULogInternal_UseFastRam(log) == MICRO_ULOG_SUCCESS)
  {
    buffer = (uint32*)log->buffer;
    bufSize = log->bufSize;
    bufSizeMask = log->bufSizeMask;
    msgSize = 7 * sizeof(uint32);
    msgTotalSize = 4 + msgSize; // size/format + data

    bufferNeeded = log->write - log->readWriter + msgTotalSize;

    if(bufferNeeded > bufSize)
    {
      if(log->read == log->readWriter)
      {
        //indicate that the log has wrapped.  
        log->usageData |= MICRO_ULOG_LOG_WRAPPED;
      }
      // Advance the readWriter pointer forward by 1 message. 
      // Note how this is a speed optimization from normal ULogs.  Since all 
      // messages are 8 words long, erasing the old message doesn't require any
      // reading old messages and advancing the readWriter by the old message size.
      // We simply jump readWriter forward 8 words. This is faster, but exactly
      // why this Fast7 API can't be used with the other APIs in the same log. 
      log->readWriter += msgTotalSize;
    }


    // 'zeroing' size to an appropriate word index and incrementing write pointer
    size_idx = (log->write & bufSizeMask) >> 2;
    buffer[size_idx] = 0;
    log->write += 4;

    // write message out to buffer (except for size)
    memcpy(&buffer[size_idx+1], message, msgSize);
    log->write += msgSize;

    // finally, store size and format
    buffer[size_idx] = (msgTotalSize << 16) | MICRO_ULOG_SUBTYPE_RESERVED_FOR_RAW;
  }
  else {
    // This log is not using RAM logging, use vtable writes instead
    uint32 qdss_logbuf[8];
    //The first word of the message has size and the msg format
    qdss_logbuf[0] = 0x20 << MICRO_ULOG_LENGTH_SHIFT | MICRO_ULOG_SUBTYPE_RESERVED_FOR_RAW;
    //put the rest of the message in the buffer to send out QDSS
    memcpy(qdss_logbuf+1, message, 7*sizeof(message[0]));
    //send the prepared log message to QDSS. 
    log->altTransportVTable->write (h, 8*sizeof(qdss_logbuf[0]), (char *)qdss_logbuf, 0, NULL);
  }
  
  return MICRO_ULOG_SUCCESS;
}
#endif  /* FEATURE_FAST7 */




