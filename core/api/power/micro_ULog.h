/*============================================================================
  micro_ULog.h

  Public-facing micro_ULog structs, enums, and function headers

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
============================================================================*/
#ifndef MICRO_ULOG_H
#define MICRO_ULOG_H
#include <string.h>
#include <stdarg.h>
#include "micro_ULogTargetCustom.h"

//Logs are passed around and used by their handle. 
typedef void * micro_ULogHandle;

/* -----------------------------------------------------------------------
** Micro ULog Constants/Macros
** ----------------------------------------------------------------------- */
// Maximum length of log name stored within the MICRO_ULOG_TYPE struct
#define MICRO_ULOG_MAX_NAME_SIZE 23

// Defines for the logStatus word in the header (ULOG_STRUCT) defined below.
#define MICRO_ULOG_STATUS_DEFINED      (0x01 << 0)    // Set if the log is defined
#define MICRO_ULOG_STATUS_ENABLED      (0x01 << 1)    // Set if the log is enabled

#define MICRO_ULOG_TRANSPORT_RAM  0
#define MICRO_ULOG_TRANSPORT_STM  1
#define MICRO_ULOG_TRANSPORT_ALTERNATE 2

#define MICRO_ULOG_TYPE_LOG_HEADER_VERSION   0x00001000
#define MICRO_ULOG_TIMESTAMP_SIZE      8

//Feature Flags 1 Bits
//Timstamp size is Bit 0 of feature flags 1
#define MICRO_ULOG_FF1_TS_SIZE_MASK 0x1
#define MICRO_ULOG_FF1_32_BIT_TS 0
#define MICRO_ULOG_FF1_64_BIT_TS 1

//the length is the top 16 bits of the first word written in msgs.
#define MICRO_ULOG_LENGTH_MASK  0xFFFF0000 
#define MICRO_ULOG_LENGTH_SHIFT 16

//individual micro ULog messages are limited to 128 bytes or less
#define MICRO_ULOG_MAX_MSG_SIZE 128

//Unless a log is not defined (isn't really a log yet) the minimum size is 64 bytes. 
#define MICRO_ULOG_MINIMUM_LOG_SIZE 64

//Printf Macros - provides some error checking when compiling
#define MICRO_ULOG_RT_PRINTF_0(h, formatStr) \
           micro_ULog_RealTimePrintf(h, 1, formatStr)
#define MICRO_ULOG_RT_PRINTF_1(h, formatStr, p1) \
           micro_ULog_RealTimePrintf(h, 2, formatStr, p1)
#define MICRO_ULOG_RT_PRINTF_2(h, formatStr, p1, p2) \
           micro_ULog_RealTimePrintf(h, 3, formatStr, p1, p2)
#define MICRO_ULOG_RT_PRINTF_3(h, formatStr, p1, p2, p3) \
           micro_ULog_RealTimePrintf(h, 4, formatStr, p1, p2, p3)
#define MICRO_ULOG_RT_PRINTF_4(h, formatStr, p1, p2, p3, p4) \
           micro_ULog_RealTimePrintf(h, 5, formatStr, p1, p2, p3, p4)   
#define MICRO_ULOG_RT_PRINTF_5(h, formatStr, p1, p2, p3, p4, p5) \
           micro_ULog_RealTimePrintf(h, 6, formatStr, p1, p2, p3, p4, p5)          

//This macro returns the amount of memory needed for a micro_ULog with a desiredBufSize
//message buffer size. desiredBufSize must be a power of 2, and greater than 64 in order
//for the result to be accurate. This expression accounts for 32-bit word alignment.
#define MICRO_ULOG_MEM_NEEDED_LOCK(desiredBufSize) (((sizeof(MICRO_ULOG_TYPE) + sizeof(MICRO_ULOG_MUTEX_TYPE) + 3) & 0xFFFFFFFC) + desiredBufSize)
#define MICRO_ULOG_MEM_NEEDED(desiredBufSize) (((sizeof(MICRO_ULOG_TYPE) + 3) & 0xFFFFFFFC) + desiredBufSize)

#define MICRO_ULOGINTERNAL_PADCOUNT(x) ((x + 3) & 0xFFFFFFFC)   

/** The value for x MUST be a 4 byte "float" variable.  It cannot be immediate data or an 8 byte "double" */
#define MICRO_ULOG_RT_FLOAT(x) (*((uint32 *)((void *)&x)))

/** Macros for splitting up a 64 bit value */
#define MICRO_ULOG64_LOWWORD(x)  (uint32)x
#define MICRO_ULOG64_HIGHWORD(x) (uint32)((uint64)x>>32)
#define MICRO_ULOG64_DATA(x)     (uint32)x, (uint32)((uint64)x>>32)


/* -----------------------------------------------------------------------
** Micro ULog Enums
** ----------------------------------------------------------------------- */

// Data subtypes stored in log message headers
typedef enum
{
  MICRO_ULOG_SUBTYPE_RESERVED_FOR_RAW = 0,
  MICRO_ULOG_SUBTYPE_REALTIME_PRINTF,
  MICRO_ULOG_SUBTYPE_REALTIME_BYTEDATA,
  MICRO_ULOG_SUBTYPE_REALTIME_STRINGDATA,
  MICRO_ULOG_SUBTYPE_REALTIME_WORDDATA,
  MICRO_ULOG_SUBTYPE_REALTIME_CSVDATA,
  MICRO_ULOG_SUBTYPE_REALTIME_VECTOR,
  MICRO_ULOG_SUBTYPE_REALTIME_MULTIPART,
  MICRO_ULOG_SUBTYPE_REALTIME_MULTIPART_STREAM_END,
  MICRO_ULOG_SUBTYPE_REALTIME_TOKENIZED_STRING,
  MICRO_ULOG_SUBTYPE_RESERVED1,
  MICRO_ULOG_SUBTYPE_RESERVED2,
  MICRO_ULOG_SUBTYPE_RESERVED3,
  MICRO_ULOG_SUBTYPE_RAW8,
  MICRO_ULOG_SUBTYPE_RAW16,
  MICRO_ULOG_SUBTYPE_RAW32,
  
  MICRO_ULOG_SUBTYPE_REALTIME_UINT32 = 0x7FFFFFFF    // force enum to 32-bits 
} MICRO_ULOG_REALTIME_SUBTYPES;     


// Values that can be OR'ed into the log's usageData variable. 
typedef enum
{
  MICRO_ULOG_LOG_WRAPPED = 0x0001,   // Not an error condition. Just an 
                                     // indicator that the log has wrapped
                                     // at least once.

  MICRO_ULOG_ERR_LARGEMSG = 0x0002,  // A message too large for the buffer 
                                     // was logged, and therefore was dropped.
                                     // This indicates the message was too 
                                     // large for the entire buffer.

  MICRO_ULOG_ERR_LARGEMSGOUT = 0x0004, // A message too large for the output 
                                       // buffer was dropped because it could
                                       // not fit.

  MICRO_ULOG_ERR_RESET = 0x0008,           // The log has been reset at least once.

  MICRO_ULOG_ERR_UINT32 = 0x7FFFFFFF    // force enum to 32-bits 
} MICRO_ULOG_STATUS_TYPE; 


// Error Codes that can be returned from micro_ULog functions.  
typedef enum
{
  MICRO_ULOG_ERROR = -1,
  MICRO_ULOG_SUCCESS,
  MICRO_ULOG_ERR_BUFFER_TOO_SMALL,
  MICRO_ULOG_ERR_INVALIDNAME,
  MICRO_ULOG_ERR_ALREADYCREATED,
  MICRO_ULOG_ERR_ALREADYENABLED,
  MICRO_ULOG_ERR_INVALIDHANDLE,
  MICRO_ULOG_ERR_INITINCOMPLETE,
  MICRO_ULOG_FAST_TO_RAM_UNAVAIL,
  MICRO_ULOG_FAST_TO_RAM_FAIL,
  MICRO_ULOG_FAST_TO_RAM_SUCCESS,
} micro_ULogResult;


// These flags are used with the micro_ULog_MemoryAssign function to indicate which 
// memory block the function should assign. The SHARED_HEADER value is depricated and 
// no longer used. 
typedef enum
{
  MICRO_ULOG_VALUE_BUFFER,
  MICRO_ULOG_VALUE_SHARED_HEADER,
  MICRO_ULOG_VALUE_LOCK,
} MICRO_ULOG_VALUE_ID;


/* -----------------------------------------------------------------------
** Micro ULog Structures
** ----------------------------------------------------------------------- */

//The function pointers here allow additional and custom log write implementations, and for these
//to be changed during runtime as needed without modification to the rest of the ULog logic.
typedef struct
{
  micro_ULogResult (*write) (micro_ULogHandle h, uint32 firstMsgCount, const char * firstMsgContent,
                             uint32 secondMsgCount, const char * secondMsgContent);
  int (*multipartMsgBegin) (micro_ULogHandle h);   /* important to leave these in for
                                                      compatibility's sake */
  void (*multipartMsgEnd) (micro_ULogHandle h);
} MICRO_ULOG_CORE_VTABLE; 


// Top-level micro_ULog structure
typedef struct MICRO_ULOG_STRUCT
{
  struct MICRO_ULOG_STRUCT * next;  // Link to the next log in the system.

  uint32 version;    // Version of this header.  Needed for logs that
                     // exist across processors.
 
  char name[MICRO_ULOG_MAX_NAME_SIZE+1];     // The name of the log.  
  uint32 logStatus;  // See defines above.  Contains status information on the log

  char * buffer;       // The physical log buffer pointer.
  uint32 bufSize;      // The size of the log buffer.
  uint32 bufSizeMask;  // To speed writes, the log buffer is always
                       // powers of two in length.  This value is
                       // bufSize - 1, allowing us to simply mask it with 
                       // the read and write indicies to yield the actual
                       // memory pointer.

#ifdef LOCKABLE_LOGS_SUPPORTED
  MICRO_ULOG_MUTEX_HANDLE_TYPE lockHandle;  //Handle to the actual lock
#endif

  // Read Index.  Maintained by the reader.  Points to the
  // index where the next log message will be read.  Is used
  // by the writer to determine if a log overflow has 
  // occurred.
  volatile uint32 read;

  // Read Status Flags.  These can be updated for anything related to the
  // read path.  The bits are defined in ULOG_READ_FLAGS.
  volatile uint32 readFlags;
  
  // Write Index.  Maintained by the writer, points to the
  // index where the next log message will start.
  volatile uint32 write;

  // Trailing index.  Maintained by the writer, points to the
  // first valid message in the log.  As messages are added to 
  // the log, messages become invalid.  This pointer is maintained
  // to let the reader know where it can start reading.
  volatile uint32 readWriter;

  // Status information.  Maintained by the writer, is a bitfield
  // made up of ULOG_ERR_TYPE errors.
  uint32 usageData;

  uint32 transactionWriteCount;                 // Number of bytes written
  uint32 transactionWriteStart;                 // Starting point of the Write

   //32 bits broken up into 4 chars for various indicators.
  unsigned char transport;                      //RAM, STM, or ALT
  unsigned char protocol_num;                   //STM protocol number 0-127 are used for binary logs, 128-255 are ASCII logs
  unsigned char feature_flags1;                 //currently using one bit for 64 vs 32 bit timestamps 
  unsigned char resetCount;                     //Used to count log resets. Should be rare. 

  uint32 stmPort; 
	
  MICRO_ULOG_CORE_VTABLE* altTransportVTable;

} MICRO_ULOG_TYPE;


// Log context- linked list of all logs in the system
typedef struct 
{
  MICRO_ULOG_TYPE * logHead;          // Pointer to a list of available logs.
} MICRO_LOG_CONTEXT;


/* -----------------------------------------------------------------------
** Micro ULog Function Declarations
** ----------------------------------------------------------------------- */

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
                                              uint32 memSize);
#endif

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
                                     uint32 memSize);


/*---------------------------------------------------------------------------------------
  micro_ULog_MemoryAssign
  Assigns given memory to a ULog component, such as the message buffer, ReaderCore, etc
  Returns: MICRO_ULOG_SUCCESS on success, MICRO_ULOG_INVALID_HANDLE for a NULL h,
           MICRO_ULOG_ERROR on other errors
  Parameters: h: The handle of the micro_ULog for which to allocate memory
              id: the MICRO_ULOG_VALUE_ID code for the type of memory being assigned
              bufferPtr: pointer to the memory to use
              bufferSize: the number of bytes available in the buffer
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_MemoryAssign(micro_ULogHandle h,
                                         MICRO_ULOG_VALUE_ID id,
                                         void * bufferPtr,
                                         uint32 bufferSize);

/*---------------------------------------------------------------------------------------
  micro_ULog_Enable
  Enable and reset the log. Only needed if using micro_ULog_MemoryAssign to manually
   assign log memory components.
  Returns: MICRO_ULOG_SUCCESS on success,
           MICRO_ULOG_ERR_INITINCOMPLETE if other components have not been initialized
           MICRO_ULOG_ERR_ALREADYENABLED if the log has already been enabled
           MICRO_ULOG_ERROR on other errors
  Parameters: h: The handle of the micro_ULog to enable
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_Enable(micro_ULogHandle h);


/*---------------------------------------------------------------------------------------
  micro_ULog_Disable
  Disable the log, preventing further writes until it is enabled again
  Returns: MICRO_ULOG_SUCCESS on success,
           MICRO_ULOG_ERROR on errors
  Parameters: h: The handle of the micro_ULog to disable
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_Disable(micro_ULogHandle h);


/*---------------------------------------------------------------------------------------
  micro_ULog_ResetLog
  Should be used only rarely in anything but test code. "Resets" a log by moving the read
   and write pointers back to the beginning of the circular RAM buffer.
  Returns: MICRO_ULOG_SUCCESS on success
           MICRO_ULOG_ERROR if h is NULL.
  Parameters: h: the micro_ULog to reset
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_ResetLog(micro_ULogHandle h);


/*---------------------------------------------------------------------------------------
 micro_ULog_SetTransportToRAM
 Write log messages to the circular RAM buffer
 Returns: MICRO_ULOG_SUCCESS if the transport is changed
          micro_ULOR_ERROR if it isn't 
 Parameters: h : A ULog handle
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_SetTransportToRAM(micro_ULogHandle h); 


/*---------------------------------------------------------------------------------------
 micro_ULog_SetTransportToSTM
 Write log messages to the QDSS/STM transport
 Returns: MICRO_ULOG_SUCCESS if the transport is changed
          micro_ULOR_ERROR if it isn't 
 Parameters: h : A ULog handle
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_SetTransportToSTM(micro_ULogHandle h);


/*---------------------------------------------------------------------------------------
 micro_ULog_SetTransportToAlt
 Write log messages using the provided handlers
 Returns: MICRO_ULOG_SUCCESS if the transport is changed
          micro_ULOR_ERROR if it isn't 
 Parameters: h : A ULog handle
             newTansportVTable : A function table including the write function
---------------------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_SetTransportToAlt(micro_ULogHandle h,
                                              MICRO_ULOG_CORE_VTABLE * newTansportVTable);


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
micro_ULogResult micro_ULog_RealTimePrintf(micro_ULogHandle h, 
                                           uint32 dataCount, 
                                           const char * formatStr, 
                                           ...);


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
micro_ULogResult micro_ULog_RealTimeVprintf(micro_ULogHandle h, 
                                           uint32 dataCount, 
                                           const char * formatStr, 
                                           va_list ap);


/*----------------------------------------------------------------------------
 micro_ULog_Fast7WordWrite
 Writes 7 words to the specified log in a format compatible with Raw ULogs.
  This function works on a log that ONLY contains Fast7 messages to speed optimize 
  way space is freed when the log wraps.  It CANNOT be mixed with other types of 
  ULog writes to the same log. Doing so, would corrupt messages in that log. 
 Returns: MICRO_ULOG_SUCCESS on a successful write
          MICRO_ULOG_ERROR on errors
 Parameters: h : A ULog handle
             message : seven data words to write to the log
----------------------------------------------------------------------------*/
micro_ULogResult micro_ULog_Fast7WordWrite(micro_ULogHandle h,
                                           uint32 message[7]);

#endif // MICRO_ULOG

