#ifndef DDISLIMBUS_H
#define DDISLIMBUS_H
/*=========================================================================*/
/**
   @file  ddislimbus.h

   This module provides the interface to the SLIMbus driver software.
*/
/*=========================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/api/slimbus/ddislimbus.h#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
07/25/13   MJS     Add support for upper watermark, shadow counter and 
                   hardware capability APIs.
10/03/12   MJS     Add SlimBus_GetBamIOVecEx with user data pointer.
10/04/11   MJS     Fix virtual table dereference for shared data channel API.
09/27/11   MJS     Add shared channel API.
03/29/11   MJS     Add DalSlimBus_RegisterPortEventEx().
11/30/10   MJS     Add flag to indicate channel group ordering 
                   should be preserved.
09/03/10   MJS     Updated based on design review and implementation feedback.
05/28/10   MJS     Initial revision.

===========================================================================
             Copyright (c) 2010, 2011, 2012, 2013 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/

#include "DALSys.h"
#include "DALStdErr.h"
#include "DalDevice.h"

#define DALSLIMBUS_INTERFACE_VERSION DALINTERFACE_VERSION(1,0)

/** Pass in place of event handle to indicate function call
    should be non-blocking for value element and information
    element read/write/clear functions */
#define SLIMBUS_EVENT_HANDLE_NON_BLOCKING  ((DALSYSEventHandle)0xffffffff)

/** Size of enumeration address buffer size */
#define SLIMBUS_ENUM_ADDR_BUF_SIZE  6

/** Flag bits supported by BAM hardware for SlimBusBamIOVecType */
#define SLIMBUS_BAM_IOVEC_FLAG_INT  0x8000  /**< Generate interrupt */
#define SLIMBUS_BAM_IOVEC_FLAG_EOT  0x4000  /**< Generate end-of-transfer indication */

/* SlimBus BAM device handle indicating use of system memory */
#define SLIMBUS_BAM_DEV_HANDLE_MEM       ((void*)0x7fffffffUL)

/** SLIMbus device logical address data type */
typedef uint8 SlimBusLogicalAddrType;

/** SLIMbus resource handle */
typedef uint32 SlimBusResourceHandle;

/** Enumeration of SLIMbus port requirements specified when
    allocating master ports. */
typedef enum
{
  SLIMBUS_PORT_REQ_O_DEFAULT = 0,  /**< Use the default requirements */
  SLIMBUS_PORT_REQ_O_HALF_DUPLEX = 1,  /**< Port must be able to support 
                                            half-duplex data channel */
  SLIMBUS_PORT_REQ_O_MULTI_CHAN_GROUP = 2,  /**< Port is part of a multi-channel group */
  _PLACEHOLDER_SlimBusPortReqType = 0x7fffffff
} SlimBusPortReqType;

/** Enumeration of SLIMbus master port configuration options. */
typedef enum
{
  SLIMBUS_PORT_O_NONE = 0,  /**< No options specified */
  SLIMBUS_PORT_O_PACKED = 1,  /**< Data going to/from the port is packed */
  SLIMBUS_PORT_O_ALIGN_MSB = 2,  /**< Data going to/from the port is MSB-aligned */
  _PLACEHOLDER_SlimBusPortOptionsType = 0x7fffffff
} SlimBusPortOptionsType;

/** SLIMbus master port configuration structure */
typedef struct
{
  uint32 uWaterMark;  /**< Watermark level to set for the port */
  SlimBusPortOptionsType eOptions;  /**< Bitmap of port options to set */
  /** SLIMbus port will assert block_end after uBlockSize bytes,
      only valid for producer data pipe in BAM-to-BAM mode */
  uint32 uBlockSize;
  /** SLIMbus port will assert trans_end after uTransSize
      bytes, closing the current FIFO descriptor early; only
      valid for producer data pipe */
  uint32 uTransSize;
  DALBOOL bUpperWaterMarkValid;  /**< Is the upper watermark level field valid */
  uint32 uUpperWaterMark;  /**< Upper watermark level to set for the port */
} SlimBusPortConfigType;

/** This struct specifies BAM-related memory buffer
    properties */
typedef struct
{
   void *pBase;      /**< Buffer virtual address */
   uint32 uPhysBase; /**< Buffer physical address */
   uint32 uSize;     /**< Specifies buffer size (or maximum size) */
   uint32 uMinSize;  /**< If non-zero, specifies buffer minimum size */
} SlimBusMemBufferType;

/** This enum is a set of bit flag options for BAM connection.
 The enums should be OR'd together to create the option set for 
 the BAM connection. 
 */
typedef enum
{
   /** Options to enable specific BAM hardware interrupts. These
      bit flagsare also used to indicate interrupt source for the 
      SLIMBUS_EVENT_IRQ event. */
   SLIMBUS_BAM_O_DESC_DONE = 0x00000001,  /**< Descriptor processed indication from hardware */
   SLIMBUS_BAM_O_INACTIVE  = 0x00000002,  /**< Inactivity timeout indication from hardware */
   SLIMBUS_BAM_O_WAKEUP    = 0x00000004,  /**< Peripheral wake up indication from hardware */
   SLIMBUS_BAM_O_OUT_OF_DESC = 0x00000008,/**< Out of descriptors indication from hardware */
   SLIMBUS_BAM_O_ERROR     = 0x00000010,  /**< Error indication from hardware */
   SLIMBUS_BAM_O_EOT       = 0x00000020,  /**< End-of-transfer indication from hardware */

  _PLACEHOLDER_SlimBusBamOptionType = 0x7fffffff
} SlimBusBamOptionType;

/** BAM pipe configuration structure */
typedef struct
{
  void *eBamDev;  /**< Device handle for the other endpoint for the pipe */
  uint32 uPipeIndex;  /**< Pipe index for the other endpoint of the pipe, NA for memory */
  SlimBusBamOptionType eOptions;  /**< Options */
  SlimBusMemBufferType DescFifo;  /**< Optional BAM descriptor FIFO to use for the pipe */
  SlimBusMemBufferType Data;   /**< Optional BAM data FIFO for the pipe (BAM-to-BAM mode only) */
} SlimBusPipeConfigType;

/** This enum specifies the event trigger mode and is an
    argument for the DalSlimBus_RegisterBamEvent() function. */
typedef enum
{
   SLIMBUS_BAM_TRIGGER_CALLBACK = 0,  /**< Trigger with payload for callback */
   SLIMBUS_BAM_TRIGGER_WAIT,          /**< Trigger without payload for wait or poll */

  _PLACEHOLDER_SlimBusBamTriggerType = 0x7fffffff
} SlimBusBamTriggerType;

/** BAM event registration structure */
typedef struct
{
   /** Event options that will trigger the event object */
   SlimBusBamOptionType eOptions;
   /** Handle to callback event object to be registered,
     can be NULL to deregister the current object */
   DALSYSEventHandle hEvent;
   /** User pointer that will be provided in event callback data */
   void *pUser;
} SlimBusBamRegisterEventType;

/** This data type corresponds to the native I/O vector (BAM
    descriptor) supported by BAM hardware */
typedef struct
{
  uint32 uAddr;        /**< Buffer physical address */
  uint32 uSize : 16;   /**< Buffer size in bytes */
  uint32 uFlags : 16;  /**< Flag bitmask (see SLIMBUS_BAM_IOVEC_FLAG_ #defines) */
} SlimBusBamIOVecType;

/** This enum indicates the event associated with a client event trigger */
typedef enum
{
   SLIMBUS_BAM_EVENT_INVALID = 0,

   SLIMBUS_BAM_EVENT_EOT,          /**< End-of-transfer indication from hardware */
   SLIMBUS_BAM_EVENT_DESC_DONE,    /**< Descriptor processed indication from hardware */
   SLIMBUS_BAM_EVENT_OUT_OF_DESC,  /**< Out of descriptors indication from hardware */
   SLIMBUS_BAM_EVENT_WAKEUP,       /**< Peripheral wake up indication from hardware */
   SLIMBUS_BAM_EVENT_FLOWOFF,      /**< Graceful halt (idle) indication from hardware */
   SLIMBUS_BAM_EVENT_INACTIVE,     /**< Inactivity timeout indication from hardware */
   SLIMBUS_BAM_EVENT_ERROR,        /**< Error indication from hardware */

   SLIMBUS_BAM_EVENT_MAX,

  _PLACEHOLDER_SlimBusBamEventType = 0x7fffffff
} SlimBusBamEventType;

/** Enumeration of SLIMbus data channel rate families */
typedef enum
{
  SLIMBUS_RATE_FAM_4_KHZ,
  SLIMBUS_RATE_FAM_11p025_KHZ,
  SLIMBUS_RATE_FAM_1_HZ,
  SLIMBUS_RATE_FAM_NUM_ENUMS,
  _PLACEHOLDER_SlimBusRateFamilyType = 0x7fffffff
} SlimBusRateFamilyType;

/** Enumeration of SLIMbus data channel transport protocols */
typedef enum
{
  SLIMBUS_PROTO_HARD_ISO,  /**< Isochronous protocol must be used */
  /** Isochronous protocol will be used if possible, otherwise
      pushed or pulled protocols will be used */
  SLIMBUS_PROTO_AUTO_ISO,
  SLIMBUS_PROTO_PUSHED,  /**< Pushed protocol */
  SLIMBUS_PROTO_PULLED,  /**< Pulled protocol */
  SLIMBUS_PROTO_ASYNC_SIMPLEX,  /**< Asynchronous simplex */
  SLIMBUS_PROTO_ASYNC_HALF_DUPLEX,  /**< Asynchronous half-duplex */
  SLIMBUS_PROTO_EXT_ASYNC_SIMPLEX,  /**< Extended asynchronous simplex */
  SLIMBUS_PROTO_EXT_ASYNC_HALF_DUPLEX,  /**< Extended asynchronous half-duplex */
  SLIMBUS_PROTO_NUM_ENUMS,  /**< Number of enumeration values */
  _PLACEHOLDER_SlimBusProtocolType = 0x7fffffff
} SlimBusProtocolType;

/** Enumeration of SLIMbus data channel options */
typedef enum
{
  SLIMBUS_CHAN_O_NONE = 0,  /**< No options specified */
  /** Automatically activate the channel at the next
      reconfiguration boundary */
  SLIMBUS_CHAN_O_AUTO_ACTIVATE = 1,
  /** Preserve the relative ordering of channels within a group
      across reconfiguration sequences */
  SLIMBUS_CHAN_O_PRESERVE_ORDERING = 2,
  _PLACEHOLDER_SlimBusChannelOptionsType = 0x7fffffff
} SlimBusChannelOptionsType;

/** Enumeration of SLIMbus data channel data formats */
typedef enum
{
  SLIMBUS_DATA_FORMAT_NOT_INDICATED,
  SLIMBUS_DATA_FORMAT_LPCM_AUDIO,
  SLIMBUS_DATA_FORMAT_IEC61937_COMP_AUDIO,
  SLIMBUS_DATA_FORMAT_PACKED_PDM_AUDIO,
  SLIMBUS_DATA_FORMAT_NUM_ENUMS,
  _PLACEHOLDER_SlimBusDataFormatType = 0x7fffffff
} SlimBusDataFormatType;

/** Enumeration of SLIMbus data channel sideband formats */
typedef enum
{
  SLIMBUS_SIDEBAND_FORMAT_NOT_APPLICABLE,
  SLIMBUS_SIDEBAND_FORMAT_IEC60958_TUNNELING,
  SLIMBUS_SIDEBAND_FORMAT_NUM_ENUMS,
  _PLACEHOLDER_SlimBusSidebandFormatType = 0x7fffffff
} SlimBusSideBandFormatType;

/** Enumeration of SLIMbus master port data flow directions */
typedef enum
{
  SLIMBUS_PORT_SOURCE_FLOW = 0,  /**< Data flow source direction */
  SLIMBUS_PORT_SINK_FLOW,  /**< Data flow sink direction */
  SLIMBUS_PORT_NUM_ENUMS,  /**< Number of enumeration values */
  _PLACEHOLDER_SlimBusPortFlowType = 0x7fffffff
} SlimBusPortFlowType;

/** Enumeration of SLIMbus data channel management commands */
typedef enum
{
  SLIMBUS_CHAN_CTRL_ACTIVATE,  /**< Activate the data channel */
  SLIMBUS_CHAN_CTRL_DEACTIVATE,  /**< Deactivate the data channel */
  SLIMBUS_CHAN_CTRL_REMOVE,  /**< Remove the data channel definition */
  SLIMBUS_CHAN_NUM_ENUMS, /**< Number of enumeration values */
  _PLACEHOLDER_SlimBusChannelCtrlType = 0x7fffffff
} SlimBusChannelCtrlType;

/** Structure used to specified requested parameters for data
    channels */
typedef struct
{
  uint32 uSampleSize_bits;  /**< Size of the sample in bits */
  SlimBusRateFamilyType eBaseSampleRate; /**< Base sample rate */
  uint32 uRateMultiplier;  /**< Sample rate multiplier */
  SlimBusProtocolType eDesiredProtocol;  /**< Desired SLIMbus data protocol */
  SlimBusChannelOptionsType eOptions;  /**< Data channel options */
  SlimBusDataFormatType eDataFormat;  /**< Data channel data format */
  SlimBusSideBandFormatType eSidebandFormat;  /**< Data channel sideband format */
} SlimBusChannelReqType;

/** Enumeration of SLIMbus data transfer directions (receive
    or transmit).  Default direction can be used if data
    channel is unidirectional. */
typedef enum
{
  SLIMBUS_BAM_TRANSMIT,
  SLIMBUS_BAM_RECEIVE,
  SLIMBUS_BAM_DEFAULT,
  SLIMBUS_BAM_NUM_ENUMS,
  _PLACEHOLDER_SlimBusBamTransferType = 0x7fffffff
} SlimBusBamTransferType;

/** Enumeration of SLIMbus master port asynchronous events */
typedef enum
{
  SLIMBUS_EVENT_O_NONE = 0,
  SLIMBUS_EVENT_O_FIFO_OVERRUN = 0x2,
  SLIMBUS_EVENT_O_FIFO_RECEIVE_OVERRUN = SLIMBUS_EVENT_O_FIFO_OVERRUN,
  SLIMBUS_EVENT_O_FIFO_TRANSMIT_OVERRUN = SLIMBUS_EVENT_O_FIFO_OVERRUN,
  SLIMBUS_EVENT_O_FIFO_UNDERRUN = 0x4,
  SLIMBUS_EVENT_O_FIFO_TRANSMIT_UNDERRUN = SLIMBUS_EVENT_O_FIFO_UNDERRUN,
  SLIMBUS_EVENT_O_FIFO_RECEIVE_UNDERRUN = SLIMBUS_EVENT_O_FIFO_UNDERRUN,
  SLIMBUS_EVENT_O_PORT_DISCONNECT = 0x10,
  _PLACEHOLDER_SlimBusPortEventType = 0x7fffffff
} SlimBusPortEventType;

/** The default set of SLIMbus master port asynchronous
    events */
#define SLIMBUS_EVENT_O_DEFAULTS \
  ((SlimBusPortEventType)(SLIMBUS_EVENT_O_FIFO_RECEIVE_OVERRUN| \
                          SLIMBUS_EVENT_O_FIFO_TRANSMIT_UNDERRUN| \
                          SLIMBUS_EVENT_O_PORT_DISCONNECT))

/** SLIMbus port event notification structure.  The client
    should zero out the events in the event bitmap for all
    events handled by the client event handler.  Any events
    not handled by the client handler (and zeroed out in the
    bitmap) will be available for retrieval by the
    DalSlimBus_GetPortEvent() function */
typedef struct
{
  void *pUser;  /**< User pointer set during DalSlimBus_RegisterPortEvent() */
  SlimBusPortEventType eEvent;  /**< Bitmap of SLIMbus master port events pending */
  SlimBusResourceHandle hPort;  /**< Handle to SLIMbus master port generating the event */
} SlimBusEventNotifyType;

/** Enumeration of SLIMbus data channel statuses */
typedef enum
{
  SLIMBUS_CHANNEL_STATUS_REMOVED,  /**< Data channel is not scheduled */
  SLIMBUS_CHANNEL_STATUS_INACTIVE,  /**< Data channel is scheduled but not active */
  SLIMBUS_CHANNEL_STATUS_ACTIVE,  /**< Data channel is scheduled and active */
  _PLACEHOLDER_SlimBusDataChannelStatusType = 0x7fffffff
} SlimBusDataChannelStatusType;

/** Enumeration of audio counter types */
typedef enum
{
  SLIMBUS_COUNTER_FREE_RUN,
  SLIMBUS_COUNTER_VFR,
  SLIMBUS_COUNTER_SHADOW,
  _PLACEHOLDER_SlimBusCounterType = 0x7fffffff
} SlimBusCounterType;

/** Enumeration of SLIMbus error conditions */
typedef enum
{
  SLIMBUS_ERR_NONE = DAL_SUCCESS,  /**< No error has occurred */
  SLIMBUS_ERR_MSG_NACKED,  /**< Message transmission was not ACKed */
  /** Timeout occurred waiting for value or information element read response */
  SLIMBUS_ERR_MSG_RESP_TIMEOUT,  
  SLIMBUS_ERR_DATA_CHANNEL_REJECTED,  /**< Data channel definition was rejected */
  _PLACEHOLDER_SlimBusErrorType = 0x7fffffff
} SlimBusErrorType;

/** Enumeration of hardware capabilities */
typedef enum
{
  SLIMBUS_HW_CAP_COMBINED_PORT_DMA_INT =    0x1,
  SLIMBUS_HW_CAP_TIMESTAMP_SHADOW_COUNTER = 0x2,
  SLIMBUS_HW_CAP_PORT_UPPER_WATERMARK =     0x4,
  _PLACEHOLDER_SlimBusHwCapType = 0x7fffffff
} SlimBusHwCapType;

typedef struct DalSlimBus DalSlimBus;
struct DalSlimBus
{
   struct DalDevice DalDevice;
   DALResult (*GetDeviceLogicalAddr)(DalDeviceHandle * _h, const uint8 *pEA, uint32 uEASize, SlimBusLogicalAddrType * pLA);
   DALResult (*RequestRootFreq)(DalDeviceHandle * _h, uint32  uFreqKhz);
   DALResult (*GetLastError)(DalDeviceHandle * _h, SlimBusErrorType * peError);
   DALResult (*AllocMasterPorts)(DalDeviceHandle * _h, SlimBusPortReqType  eReqs, uint32  uMinFifoBytes, SlimBusResourceHandle * phPortBuf, uint32  uPortBufSize);
   DALResult (*DeallocMasterPorts)(DalDeviceHandle * _h, SlimBusResourceHandle * phPortBuf, uint32  uPortBufSize);
   DALResult (*GetSlavePortHandle)(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uPortNum, SlimBusResourceHandle * phPort);
   DALResult (*ConfigMasterPort)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, const SlimBusPortConfigType * pConfig);
   DALResult (*ConfigMasterPipe)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusPortFlowType  eFlow, const SlimBusPipeConfigType * pConfig);
   DALResult (*NextReserveMsgBandwidth)(DalDeviceHandle * _h, uint32  uBandwidth_bps);
   DALResult (*ReadValueElement)(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr,  uint8*  pucReadData,  uint32  uReadDataLen,  uint32*  puActualReadDataLen, DALSYSEventHandle  hEvent);
   DALResult (*WriteValueElement)(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr,  uint32  uByteSize, const uint8*  pucWriteData,  uint32  uWriteDataLen, DALSYSEventHandle  hEvent);
   DALResult (*ExchangeValueElement)(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr,  const uint8*  pucWriteData,  uint32  uWriteDataLen,  uint8*  pucReadData,  uint32  uReadDataLen,  uint32*  puActualReadDataLen, DALSYSEventHandle  hEvent);
   DALResult (*ReadInfoElement)(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr,  uint8*  pucReadData,  uint32  uReadDataLen,  uint32*  puActualReadDataLen, DALSYSEventHandle  hEvent);
   DALResult (*ClearInfoElement)(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr, uint32  uByteSize, const uint8*  pucClearMask,  uint32  uClearMaskLen, DALSYSEventHandle  hEvent);
   DALResult (*ReadAndClearInfoElement)(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr,  const uint8*  pucClearMask,  uint32  uClearMaskLen, uint8*  pucReadData,  uint32  uReadDataLen,  uint32*  puActualReadDataLen, DALSYSEventHandle  hEvent);
   DALResult (*AllocDataChannel)(DalDeviceHandle * _h, SlimBusResourceHandle * phChannel);
   DALResult (*NextDefineDataChannel)(DalDeviceHandle * _h, SlimBusResourceHandle  hChannel, const SlimBusChannelReqType * pChannelReq);
   DALResult (*ConnectPortToChannel)(DalDeviceHandle * _h, SlimBusResourceHandle  hChannel, SlimBusPortFlowType  eFlow, SlimBusResourceHandle  hPort);
   DALResult (*DisconnectPortFromChannel)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort);
   DALResult (*NextDataChannelControl)(DalDeviceHandle * _h, SlimBusResourceHandle  hChannel, SlimBusChannelCtrlType  eCtrl);
   DALResult (*DoReconfigureNow)(DalDeviceHandle * _h);
   DALResult (*GetDataChannelStatus)(DalDeviceHandle * _h, SlimBusResourceHandle  hChannel, SlimBusDataChannelStatusType * peStatus);
   DALResult (*DeallocDataChannel)(DalDeviceHandle * _h, SlimBusResourceHandle  hChannel);
   DALResult (*RegisterBamEvent)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusBamRegisterEventType * pReg);
   DALResult (*SubmitBamTransfer)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusBamIOVecType * pIOVec, void * pUser);
   DALResult (*GetBamIOVec)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusBamIOVecType * pIOVec);
   DALResult (*GetBamEvent)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusBamEventType * peEvent);
   DALResult (*GetPortFifoStatus)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, uint32 * puFifoWordCnt, DALBOOL * pbWatermarkIsHit);
   DALResult (*RegisterPortEventEx)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, DALSYSEventHandle  hEvent, void * pUser, SlimBusPortEventType eType);
   DALResult (*GetPortEvent)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusEventNotifyType * pNotify);
   DALResult (*AllocProgressCounter)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusResourceHandle * phCounter);
   DALResult (*DeallocProgressCounter)(DalDeviceHandle * _h, SlimBusResourceHandle  hCounter);
   DALResult (*InitProgressCounter)(DalDeviceHandle * _h, SlimBusResourceHandle  hCounter, uint32  uCount);
   DALResult (*ReadProgressCounter)(DalDeviceHandle * _h, SlimBusResourceHandle  hCounter, SlimBusCounterType  eType, uint32 * puNumDMA, uint32 * puFifoSamples);
   DALResult (*ReadProgressCounterVFRStatus)(DalDeviceHandle * _h, SlimBusResourceHandle  hCounter, DALBOOL * pbSet);
   DALResult (*ClearProgressCounterVFRStatus)(DalDeviceHandle * _h, SlimBusResourceHandle  hCounter);
   DALResult (*AllocResourceGroup)(DalDeviceHandle * _h, SlimBusResourceHandle * hGroup);
   DALResult (*DeallocResourceHroup)(DalDeviceHandle * _h, SlimBusResourceHandle  hGroup);
   DALResult (*AddResourceToGroup)(DalDeviceHandle * _h, SlimBusResourceHandle  hGroup, uint32  hHandle);
   DALResult (*AllocSharedDataChannel)(DalDeviceHandle * _h, uint32 uChannelNum, SlimBusResourceHandle * phChannel);
   DALResult (*GetBamIOVecEx)(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusBamIOVecType * pIOVec, void **ppUser);
   DALResult (*GetHardwareCapability)(DalDeviceHandle * _h, SlimBusHwCapType *peHwCap);
   DALResult (*ReadProgressCounterTimestamp)(DalDeviceHandle * _h, SlimBusResourceHandle hCounter, uint32 *puNumDMA, uint32 *puFifoSamples, uint64 *puTimestamp, DALBOOL *pbSampleMissed);
   DALResult (*SendUserDefinedMessage)(DalDeviceHandle * _h, SlimBusLogicalAddrType LA, uint32 MC, const uint8* pucPayload, uint32 uPayloadLen, DALSYSEventHandle hEvent);
};

typedef struct DalSlimBusHandle DalSlimBusHandle; 
struct DalSlimBusHandle 
{
   uint32 dwDalHandleId;
   const DalSlimBus * pVtbl;
   void * pClientCtxt;
};


/**
   @name General Purpose Functions
   
   This section describes the general purpose API. 
  */
/** @{ */

/**
  @brief Establish connection to the SLIMbus driver
   
  This function establishes a connection to the SLIMbus driver. 
  If not already initialized, this function will cause the
  SLIMbus software driver and hardware to be initialized.

  @param[in] DevId  DAL device ID of the SLIMbus device to 
        connect
   
  @param[out] phDalDevice  Pointer to location to store 
        allocated handle to SLIMbus driver
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DAL_SlimBusDeviceDetach()
  */
static __inline DALResult
DAL_SlimBusDeviceAttach(DALDEVICEID DevId,DalDeviceHandle **phDalDevice)
{
  return DAL_DeviceAttachEx(NULL,DevId,DALSLIMBUS_INTERFACE_VERSION,phDalDevice);
}


/**
  @brief Close the connection to the SLIMbus driver
   
  This function closes the connection to the SLIMbus driver and 
  relinquishes any SLIMbus resources held by the client.

  @param[in] _h  handle to SLIMbus driver 
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DAL_SlimBusDeviceAttach()
  */
static __inline DALResult
DAL_SlimBusDeviceDetach(DalDeviceHandle *_h)
{
  return DAL_DeviceDetach(_h);
}


/**
  @brief Get logical address of a SLIMbus device 
   
  This function retrieves the logical address corresponding to 
  the enumeration address of a SLIMbus device.

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] pEA  Pointer to buffer containing device 
        enumeration address to query
   
  @param[in] uEASize Size of device enumeration address buffer 
   
  @param[out] pLA  Pointer to location to store of the logical 
        address of the device
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see 
  */
static __inline DALResult
DalSlimBus_GetDeviceLogicalAddr(DalDeviceHandle * _h, const uint8 *pEA, uint32 uEASize, SlimBusLogicalAddrType * pLA)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->GetDeviceLogicalAddr( _h, pEA, uEASize, pLA);
}


/**
  @brief Request a particular SLIMbus root frequency
   
  This function requests a particular SLIMbus root frequency. 
  The frequency request will only be honored if there are no 
  data channels active on the bus.

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] uFreqKhz  Requested root frequency in kilohertz
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see 
  */
static __inline DALResult
DalSlimBus_RequestRootFreq(DalDeviceHandle * _h, uint32  uFreqKhz)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->RequestRootFreq( _h, uFreqKhz);
}


/**
  @brief Get the last SLIMbus driver error.
   
  This function retrieves the last SLIMbus driver errror that 
  occurred.

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[out] peError  Pointer to location to store the last 
        SLIMbus driver error
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_NextDefineDataChannel(), 
       DalSlimBus_ReadValueElement(),
       DalSlimBus_WriteValueElement(),
       DalSlimBus_ExchangeValueElement(),
       DalSlimBus_ReadInfoElement(),
       DalSlimBus_ClearInfoElement(),
       DalSlimBus_ReadAndClearInfoElement()
  */
static __inline DALResult
DalSlimBus_GetLastError(DalDeviceHandle * _h, SlimBusErrorType * peError)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->GetLastError( _h, peError);
}

/**
  @brief Get the SLIMbus hardware capabilities.
 
  This function gets the SLIMbus hardware capabilities and 
  optional functionalities. 
  
  @param[in] _h  Client handle to the SLIMbus driver
   
  @param[out] peHwCap  Pointer to location to store the 
        enumeration of hardware capabilities
  
  @return DAL_SUCCESS on success, error code on error
 */
static __inline DALResult
DalSlimBus_GetHardwareCapability(DalDeviceHandle * _h, SlimBusHwCapType *peHwCap)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->GetHardwareCapability(_h, peHwCap);
}

/** @} */
/**
   @name Port Configuration Functions
   
   This section describes the API to allocate and configure 
   SLIMbus ports.
  */
/** @{ */

/**
  @brief Allocate port from the SLIMbus master 
   
  This function allocates one or more ports from the SLIMbus 
  master. 
   
  Ports allocated by this function correspond to logical ports 
  as defined by the SLIMbus spec, e.g. a half-duplex port is 
  considered a single logical port even though the port may 
  consume additional hardware resources within the SLIMbus 
  master. 

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] eReqs  Bitmap of requirements for the type of
        port(s) to allocate
   
  @param[in] uMinFifoBytes  Minimum required size of port FIFO 
        in bytes
   
  @param[out] phPortBuf  Location to store the handles to the 
        allocated ports
   
  @param[in] uPortBufSize  Size of the buffer of port handles in
        bytes, used to derive the number of port handles to
        allocate

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_DeallocMasterPorts(),
       DalSlimBus_GetSlavePortHandle(), 
       DalSlimBus_ConnectPortToChannel(),
       DalSlimBus_ConfigMasterPort(),
       DalSlimBus_ConfigMasterPipe(),
       DalSlimBus_AllocProgressCounter()
  */
static __inline DALResult
DalSlimBus_AllocMasterPorts(DalDeviceHandle * _h, SlimBusPortReqType  eReqs, uint32  uMinFifoBytes, SlimBusResourceHandle * phPortBuf, uint32  uPortBufSize)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->AllocMasterPorts( _h, eReqs, uMinFifoBytes, phPortBuf, uPortBufSize);
}


/**
  @brief Deallocate ports from the SLIMbus master
   
  This function deallocates ports from the SLIMbus master. 
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] phPortBuf  Location of the handles to the ports to 
        deallocate
   
  @param[in] uPortBufSize  Size of the buffer of port handles 
        in bytes, used to derive the number of port handles to
        deallocate

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocMasterPorts()
  */
static __inline DALResult
DalSlimBus_DeallocMasterPorts(DalDeviceHandle * _h, SlimBusResourceHandle * phPortBuf, uint32  uPortBufSize)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->DeallocMasterPorts( _h, phPortBuf, uPortBufSize);
}


/**
  @brief Get handle to a port on a slave device
   
  This function retrieves a handle to a port on a slave device
  that can be used for setting up a data channel.
   
  @param[in] _h  Client handle to the SLIMbus driver
  
  @param[in] LA  Logical address of slave device containing the port
  
  @param[in] uPortNum  Port number on the slave device
  
  @param[out] phPort  Location to store the port handle

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocMasterPorts(), 
       DalSlimBus_ConnectPortToChannel()
  */
static __inline DALResult
DalSlimBus_GetSlavePortHandle(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uPortNum, SlimBusResourceHandle * phPort)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->GetSlavePortHandle( _h, LA, uPortNum, phPort);
}


/**
  @brief Configure the parameters of a SLIMbus master port
   
  This function configures the parameters of a SLIMbus master 
  port.  SLIMbus slave ports cannot be configured by this 
  function. 
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Client handle to the master port 
   
  @param[in] pConfig  Pointer to the configuration to set for 
        the master port

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocMasterPorts(), 
       DalSlimBus_ConfigMasterPipe()
  */
static __inline DALResult
DalSlimBus_ConfigMasterPort(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, const SlimBusPortConfigType * pConfig)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ConfigMasterPort( _h, hPort, pConfig);
}


/**
  @brief Configure a BAM data pipe for a SLIMbus master port
  
  This function configures the BAM pipe for a SLIMbus master port to 
  source or sink data.  Half-duplex ports are treated logically 
  as a single port with both a source and sink pipe.  All other 
  ports are unidirectional and have either a source or sink 
  pipe. 

  @param[in] _h  Client handle to the SLIMbus driver
  
  @param[in] hPort  Client handle to the master port 
   
  @param[in] eFlow  The pipe flow to configure, either source or 
        sink
  @param[in] pConfig  Pointer to the configuration to set for the BAM pipe

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_ConfigMasterPort() 
  */
static __inline DALResult
DalSlimBus_ConfigMasterPipe(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusPortFlowType  eFlow, const SlimBusPipeConfigType * pConfig)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ConfigMasterPipe( _h, hPort, eFlow, pConfig);
}


/** @} */
/**
   @name Control and Status Messaging Functions
   
   This section describes the API for control and status messaging.
  */
/** @{ */


/**
  @brief Read value elements from a slave device.
  
  This function reads value element(s) from a slave device using
  byte-based access.  This function will perform an asynchronous
  read if the hEvent parameter passed is not NULL, otherwise a 
  synchronous read will be performed. 
   
  For an asynchronous transaction, the hEvent will be signaled 
  when the transaction is complete, and the error status can be 
  retrieved by DalSlimBus_GetLastError(). 
  
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] LA  Logical address of the device to read values 
        elements from
   
  @param[in] uByteAddr  The byte address of the first byte to 
        read.
   
  @param[out] pucReadData  Pointer to the buffer to store the 
        data read from the value elements
   
  @param[in] uReadDataLen  Number of value element bytes to read 
        and the size of the read data buffer; allowed values for
        uReadDataLen are 1, 2, 3, 4, 6, 8, 12 and 16
   
  @param[in] puActualReadDataLen  Optional pointer to location 
        to store the number of value element bytes actually read
   
  @param[in] hEvent  Event handle
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_ReadInfoElement(), 
       DalSlimBus_WriteValueElement(), 
       DalSlimBus_ExchangeValueElement() 
  */
static __inline DALResult
DalSlimBus_ReadValueElement(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr,  uint8*  pucReadData,  uint32  uReadDataLen,  uint32*  puActualReadDataLen, DALSYSEventHandle  hEvent)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ReadValueElement( _h, LA, uByteAddr, pucReadData, uReadDataLen, puActualReadDataLen, hEvent);
}


/**
  @brief Write value elements to a slave device.
  
  This function writes value element(s) to a slave device using 
  byte-based access.  This function will perform a synchronous 
  write if the hEvent parameter is equal to NULL, a non-blocking
  write if the hEvent parameter is equal to 
  SLIMBUS_EVENT_HANDLE_NON_BLOCKING, or otherwise an 
  asynchronous write will be performed.
   
  For an asynchronous transaction, the hEvent will be signaled 
  when the transaction is complete, and the error status can be 
  retrieved by DalSlimBus_GetLastError(). 
  
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] LA  Logical address of the device to write values 
        elements to
   
  @param[in] uByteAddr  The byte address of the first byte to 
        write.
   
  @param[in] uByteSize  The number of value element bytes to 
        write; allowed values for uByteSize are 1, 2, 3, 4, 6,
        8, 12 and 16
   
  @param[in] pucWriteData  Optional pointer to the buffer 
        containing the data to write to the value elements; if
        NULL is passed for pucWriteData then 0 must be passed
        for uWriteDataLen
   
  @param[in] uWriteDataLen  Size of the write data buffer; if 
        the write buffer length is less than the number of bytes
        to write, the destination device will pad the end of the
        write data with zeros; if the write data buffer length
        is larger than the number of bytes to write, the extra
        bytes at the end will be ignored
   
  @param[in] hEvent  Event handle
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_ReadValueElement(), 
       DalSlimBus_ExchangeValueElement()
  */
static __inline DALResult
DalSlimBus_WriteValueElement(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr, uint32  uByteSize, const uint8*  pucWriteData,  uint32  uWriteDataLen, DALSYSEventHandle  hEvent)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->WriteValueElement( _h, LA, uByteAddr, uByteSize, pucWriteData, uWriteDataLen, hEvent);
}


/**
  @brief Perform atomic exchange of value elements on a slave 
         device.
  
  This function performs an atomic exchange of value element(s) 
  on a slave device  This function will perform an asynchronous 
  exchange if the hEvent parameter passed is not NULL, otherwise 
  a synchronous exchange will be performed. 
   
  For an asynchronous transaction, the hEvent will be signaled 
  when the transaction is complete, and the error status can be 
  retrieved by DalSlimBus_GetLastError(). 
  
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] LA  Logical address of the device to exchange 
        values elements on
   
  @param[in] uByteAddr  The byte address of the first byte to 
        read.
   
  @param[in] pucWriteData  Optional pointer to the buffer 
        containing the data to write to the value elements; if
        NULL is passed for pucWriteData then 0 must be passed
        for uWriteDataLen
   
  @param[in] uWriteDataLen  Size of the write data buffer; if 
        the write buffer length is less than the number of bytes
        to read, the destination device will pad the end of
        the write data with zeros; if the write data buffer
        length is larger than the number of bytes to read, the
        extra bytes at the end will be ignored
   
  @param[out] pucReadData  Pointer to the buffer to store the 
        data read from the value elements
   
  @param[in] uReadDataLen  Number of value element bytes to 
        write and read, and the size of the read data buffer;
        allowed values for uReadDataLen are 1, 2, 3, 4, 6, 8, 12
        and 16
   
  @param[in] puActualReadDataLen  Optional pointer to location 
        to store the number of value element bytes actually read
   
  @param[in] hEvent  Event handle
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_ReadValueElement(), 
       DalSlimBus_WriteValueElement()
  */
static __inline DALResult
DalSlimBus_ExchangeValueElement(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr,  const uint8*  pucWriteData,  uint32  uWriteDataLen,  uint8*  pucReadData,  uint32  uReadDataLen,  uint32*  puActualReadDataLen, DALSYSEventHandle  hEvent)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ExchangeValueElement( _h, LA, uByteAddr, pucWriteData, uWriteDataLen, pucReadData, uReadDataLen, puActualReadDataLen, hEvent);
}


/**
  @brief Read information elements from a slave device.
  
  This function reads information element(s) from a slave device 
  using byte-based access.  This function will perform an 
  asynchronous read if the hEvent parameter passed is not NULL, 
  otherwise a synchronous read will be performed. 
   
  For an asynchronous transaction, the hEvent will be signaled 
  when the transaction is complete, and the error status can be 
  retrieved by DalSlimBus_GetLastError().
  
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] LA  Logical address of the device to read 
        information elements from
   
  @param[in] uByteAddr  The byte address of the first byte to 
        read.
   
  @param[out] pucReadData  Pointer to the buffer to store the 
        data read from the information elements
   
  @param[in] uReadDataLen  Number of information element bytes 
        to read and the size of the read data buffer; allowed
        values for uReadDataLen are 1, 2, 3, 4, 6, 8, 12 and 16
   
  @param[in] puActualReadDataLen  Optional pointer to location 
        to store number of information element bytes actually
        read
   
  @param[in] hEvent  Event handle
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_ReadValueElement(), 
       DalSlimBus_ClearInfoElement(),
       DalSlimBus_ReadAndClearInfoElement()
  */
static __inline DALResult
DalSlimBus_ReadInfoElement(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr,  uint8*  pucReadData,  uint32  uReadDataLen,  uint32*  puActualReadDataLen, DALSYSEventHandle  hEvent)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ReadInfoElement( _h, LA, uByteAddr, pucReadData, uReadDataLen, puActualReadDataLen, hEvent);
}


/**
  @brief Clear information elements on a slave device.
  
  This function clears information element(s) on a slave device 
  using byte-based access. This function will perform a synchronous 
  clear if the hEvent parameter is equal to NULL, a non-blocking
  clear if the hEvent parameter is equal to 
  SLIMBUS_EVENT_HANDLE_NON_BLOCKING, or otherwise an 
  asynchronous clear will be performed. 
   
  For an asynchronous transaction, the hEvent will be signaled 
  when the transaction is complete, and the error status can be 
  retrieved by DalSlimBus_GetLastError(). 
  
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] LA  Logical address of the device to clear 
        information elements on
   
  @param[in] uByteAddr  The byte address of the first byte to 
        clear
   
  @param[in] uByteSize  Number of information element bytes to 
        clear; allowed values for uByteSize are 1, 2, 3, 4, 6,
        8, 12 and 16
   
  @param[in] pucClearMask  Optional pointer to the buffer 
        containing the mask to use for clearing information
        elements, where every bit set to '1' in the mask
        indicates that the corresponding information element bit
        should be cleared; if NULL is passed for pucClearMask
        then 0 must be passed for uClearMaskLen
   
  @param[in] uClearMaskLen  Size of the clear mask buffer; if 
        the clear mask length is less than the number of bytes
        to clear, the destination device will pad the end of the
        clear mask with ones; if the clear mask length is larger
        than the number of bytes to clear, the extra bytes at
        the end will be ignored
   
  @param[in] hEvent  Event handle
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_ReadInfoElement(), 
       DalSlimBus_ReadAndClearInfoElement()
  */
static __inline DALResult
DalSlimBus_ClearInfoElement(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr, uint32  uByteSize, const uint8*  pucClearMask,  uint32  uClearMaskLen, DALSYSEventHandle  hEvent)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ClearInfoElement( _h, LA, uByteAddr, uByteSize, pucClearMask, uClearMaskLen, hEvent);
}


/**
  @brief Perform atomic read and clear of information elements 
         on a slave device.
  
  This function performs an atomic read and clear of information
  element(s) on a slave device using byte-based access.  This 
  function will perform an asynchronous operation if the hEvent 
  parameter passed is not NULL, otherwise a synchronous 
  operation will be performed. 
   
  For an asynchronous transaction, the hEvent will be signaled 
  when the transaction is complete, and the error status can be 
  retrieved by DalSlimBus_GetLastError(). 
  
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] LA  Logical address of the device to read and clear
        information elements on
   
  @param[in] uByteAddr  The byte address of the first byte to 
        read and clear
   
  @param[in] pucClearMask  Optional pointer to the buffer 
        containing the mask to use for clearing information
        elements, where every bit set to '1' in the mask
        indicates that the corresponding information element bit
        should be cleared; if NULL is passed for pucClearMask
        then 0 must be passed for uClearMaskLen
   
  @param[in] uClearMaskLen  Size of the clear mask buffer; if 
        the clear mask length is less than the number of bytes
        to clear, the destination device will pad the end of the
        clear mask with ones; if the clear mask length is larger
        than the number of bytes to clear, the extra bytes at
        the end will be ignored
   
  @param[out] pucReadData  Pointer to the buffer to store the 
        data read from the information elements
   
  @param[in] uReadDataLen  Number of information element bytes 
        to read and clear, and the size of the read data buffer;
        allowed values for uReadDataLen are 1, 2, 3, 4, 6, 8, 12
        and 16
   
  @param[out] puActualReadDataLen  Optional pointer to location 
        to store number of information element bytes actually
        read
   
  @param[in] hEvent  Event handle
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_ReadInfoElement(), 
       DalSlimBus_ClearInfoElement()
  */
static __inline DALResult
DalSlimBus_ReadAndClearInfoElement(DalDeviceHandle * _h, SlimBusLogicalAddrType  LA, uint32  uByteAddr,  const uint8*  pucClearMask,  uint32  uClearMaskLen, uint8*  pucReadData,  uint32  uReadDataLen,  uint32*  puActualReadDataLen, DALSYSEventHandle  hEvent)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ReadAndClearInfoElement( _h, LA, uByteAddr, pucClearMask, uClearMaskLen, pucReadData, uReadDataLen, puActualReadDataLen, hEvent);
}

/**
  @brief Send a destination-referred user-defined message to a 
         slave device.
 
  This function sends a destination-referred user-defined 
  message to a slave device.  This function will perform an 
  asynchronous operation if the hEvent parameter is not NULL, 
  otherwise a synchronous operation is performed and the 
  function will return when the message transmission is 
  complete. 
  
  For an asynchronous transaction, the hEvent will be signaled 
  when the transaction is complete, and the error status can be 
  retrieved by DalSlimBus_GetLastError(). 
  
  @param[in] _h  Client handle to the SLIMbus driver
  
  @param[in] LA  Logical address of the device to send the
        user-defined message to
  
  @param[in] MC  Message code of the user-defined message
  
  @param[in] pucPayload  Pointer to the payload data to send
  
  @param[in] uPayloadLen  Size of the payload data in bytes
  
  @param[in] hEvent  Event handle
  
  @return DAL_SUCCESS on success, an error code on error 
   
  @see DalSlimBus_GetLastError()
 */
static __inline DALResult
DalSlimBus_SendUserDefinedMessage(DalDeviceHandle *_h, SlimBusLogicalAddrType LA, uint32 MC, const uint8* pucPayload, uint32 uPayloadLen, DALSYSEventHandle hEvent)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->SendUserDefinedMessage( _h, LA, MC, pucPayload, uPayloadLen, hEvent);
}

/** @} */
/**
   @name Data Channel Management Functions
   
   This section describes the API for data channel management.
  */
/** @{ */


/**
  @brief Allocate SLIMbus data channel
   
  This function allocates a SLIMbus data channel.

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[out] phChannel  Location to store the allocated data 
        channel handle

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_DeallocDataChannel(), 
       DalSlimBus_AllocSharedDataChannel()
  */
static __inline DALResult
DalSlimBus_AllocDataChannel(DalDeviceHandle * _h, SlimBusResourceHandle * phChannel)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->AllocDataChannel( _h, phChannel);
}


/**
  @brief Allocate shared SLIMbus data channel
   
  This function allocates a SLIMbus data channel that can be 
  shared and utilized from more than one execution environment. 

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] uChannelNum  Shared channel number
   
  @param[out] phChannel  Location to store the allocated data 
        channel handle

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_DeallocDataChannel(), 
       DalSlimBus_AllocDataChannel()
  */
static __inline DALResult
DalSlimBus_AllocSharedDataChannel(DalDeviceHandle * _h, uint32 uChannelNum, SlimBusResourceHandle * phChannel)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->AllocSharedDataChannel( _h, uChannelNum, phChannel);
}


/**
  @brief Set or change the requested parameters of a data 
         channel
   
  This function sets or changes the requested parameters of a 
  data channel.  The new parameters take effect at the next 
  reconfiguration boundary. 
   
  The event handle passed as a parameter will be signaled if the
  requested data channel parameters are rejected due to lack of 
  bandwidth.  After requesting data channel parameters, the data 
  channel status returned by DalSlimBus_GetDataChannelStatus() 
  will be updated once the data channel is accepted. 

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hChannel  Data channel handle or resource group 
        handle

  @param[in] pChannelReq  Pointer to the requested data channel 
        parameters
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocDataChannel(), 
       DalSlimBus_NextDataChannelControl(),
       DalSlimBus_GetDataChannelStatus(),
       DalSlimBus_DoReconfigureNow() 
  */
static __inline DALResult
DalSlimBus_NextDefineDataChannel(DalDeviceHandle * _h, SlimBusResourceHandle  hChannel, const SlimBusChannelReqType * pChannelReq)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->NextDefineDataChannel( _h, hChannel, pChannelReq);
}


/**
  @brief Connect a port to a data channel
   
  This function connects the specified port to the data channel. 
  The connection will take effect immediately. 
   
  For master ports, if the BAM pipe has already been configured, 
  the port FIFO will begin to fill as soon as the port is 
  connected. 

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hChannel  Data channel handle 
   
  @param[in] eFlow  The type of port connection to make, source 
        or sink

  @param[in] hPort  Port handle
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocDataChannel(), 
       DalSlimBus_DisconnectPortFromChannel(),
       DalSlimBus_AllocMasterPorts(),
       DalSlimBus_GetSlavePortHandle()
  */
static __inline DALResult
DalSlimBus_ConnectPortToChannel(DalDeviceHandle * _h, SlimBusResourceHandle  hChannel, SlimBusPortFlowType  eFlow, SlimBusResourceHandle  hPort)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ConnectPortToChannel( _h, hChannel, eFlow, hPort);
}


/**
  @brief Disconnect a port from a data channel
   
  This function disconnects the specified port from the data 
  channel. The disconnection will take effect immediately. 
   
  For master ports, data flow will stop and the port and BAM 
  pipe will be reset when the port is disconnected.  It is not 
  necessary to explicitly disconnect ports when removing a data 
  channel as described under 
  DalSlimBus_NextDataChannelControl(). 

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Port handle
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocDataChannel(), 
       DalSlimBus_ConnectPortToChannel(),
       DalSlimBus_NextDataChannelControl()
  */
static __inline DALResult
DalSlimBus_DisconnectPortFromChannel(DalDeviceHandle * _h, SlimBusResourceHandle  hPort)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->DisconnectPortFromChannel( _h, hPort);
}


/**
  @brief Perform data channel control operation
   
  This function performs a data channel control operation, to 
  either activate, deactivate or remove the data channel.  The 
  control operation will take effect at the next reconfiguration 
  boundary. 
   
  For the remove operation, all ports connected to the data 
  channel will be disconnected and reset at the next 
  reconfiguration boundary, and the BAM pipes corresponding to 
  master ports connected to the data channel will be reset at 
  the next reconfiguration boundary.  For the remove operation 
  it is not necessary to explicitly disconnect ports connected 
  to the channel using DalSlimBus_DisconnectPortFromChannel().

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hChannel  Data channel handle or group handle 
   
  @param[in] eCtrl  The type of channel control operation 
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocDataChannel(), 
       DalSlimBus_NextDefineDataChannel(),
       DalSlimBus_GetDataChannelStatus(),
       DalSlimBus_DisconnectPortFromChannel(),
       DalSlimBus_DeallocDataChannel(),
       DalSlimBus_DoReconfigureNow() 
  */
static __inline DALResult
DalSlimBus_NextDataChannelControl(DalDeviceHandle * _h, SlimBusResourceHandle  hChannel, SlimBusChannelCtrlType  eCtrl)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->NextDataChannelControl( _h, hChannel, eCtrl);
}


/**
  @brief Sets the messaging bandwidth required by the client
  
  Sets the total messaging bandwidth required by the client for 
  control and status operations.  Set the required bandwidth to 
  zero to relinquish reserved bandwidth. The bandwidth request 
  will take effect at the next reconfiguration boundary. 
  
  @param[in] _h  Client handle to the SLIMbus driver
  
  @param[in] uBandwidth_bps  The bandwidth to reserve in bits per second

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_DoReconfigureNow()
  */
static __inline DALResult
DalSlimBus_NextReserveMsgBandwidth(DalDeviceHandle * _h, uint32  uBandwidth_bps)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->NextReserveMsgBandwidth( _h, uBandwidth_bps);
}


/**
  @brief Perform reconfigure now operation
   
  This function performs a reconfigure now operation.  All 
  operations queued by Next*() API functions will take effect. 
  
  @param[in] _h  Client handle to the SLIMbus driver 
  
  @return  DAL_SUCCESS if the reconfiguration sequence was 
           accepted, an error code on error or if the
           reconfiguration sequence was rejected
   
  @see DalSlimBus_NextDefineDataChannel(), 
       DalSlimBus_NextDataChannelControl(),
       DalSlimBus_NextReserveMsgBandwidth() 
  */
static __inline DALResult
DalSlimBus_DoReconfigureNow(DalDeviceHandle * _h)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->DoReconfigureNow( _h);
}


/**
  @brief Gets the status of a SLIMbus data channel
   
  This function retrives the status of a SLIMbus data 
  channel.
  
  @param[in] _h  Client handle to the SLIMbus driver 
  
  @param[in] hChannel  Data channel handle 
   
  @param[in] peStatus  Location to store the data channel status
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_NextDefineDataChannel(), 
       DalSlimBus_NextDataChannelControl()
  */
static __inline DALResult
DalSlimBus_GetDataChannelStatus(DalDeviceHandle * _h, SlimBusResourceHandle  hChannel, SlimBusDataChannelStatusType * peStatus)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->GetDataChannelStatus( _h, hChannel, peStatus);
}


/**
  @brief Deallocate SLIMbus data channel

  This function deallocates a SLIMbus data channel.  A data 
  channel that has not yet been removed will be removed as 
  described by DalSlimBus_NextDataChannelControl().

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hChannel  Data channel handle 
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocDataChannel(), 
       DalSlimBus_NextDataChannelControl(),
       DalSlimBus_DisconnectPortFromChannel()
  */
static __inline DALResult
DalSlimBus_DeallocDataChannel(DalDeviceHandle * _h, SlimBusResourceHandle  hChannel)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->DeallocDataChannel( _h, hChannel);
}


/** @} */
/**
   @name BAM Pipe Maintenance Functions
   
   This section describes the API for BAM pipe maintenance. 
  */
/** @{ */


/**
  @brief Register for asynchronous BAM event(s)

  This function registers for asynchronous BAM event(s).  If the 
  registered event is a callback event, a 
  SlimBusBamEventNotifyType structure will be passed back as the
  user data in the callback.  If the event is not a callback 
  event, the SlimBusBamEventNotifyType structure can be 
  retrieved by the DalSlimBus_GetBamEvent() function after the 
  event object has been signaled. 

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Master port handle corresponding to the BAM 
        pipe
   
  @param[in] eTransferDir  Direction of data flow for the BAM 
        pipe to register for.  For bi-directional ports, there
        is one BAM pipe for each of the transmit and receive
        directions.
   
  @param[in] pReg  Pointer to location of BAM registration 
        structure
  
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_GetBamEvent()
  */
static __inline DALResult
DalSlimBus_RegisterBamEvent(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusBamRegisterEventType * pReg)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->RegisterBamEvent( _h, hPort, eTransferDir, pReg);
}


/**
  @brief Submit a new data transfer to the BAM descriptor FIFO 

  This function submits a new data transfer to the BAM 
  descriptor FIFO. 

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Master port handle corresponding to the BAM 
        pipe
   
  @param[in] eTransferDir  Direction of data flow for the BAM 
        pipe to submit the transfer for.  For bi-directional
        ports, there is one BAM pipe for each of the transmit
        and receive directions.
   
  @param[in] pIOVec  Pointer to the IO-vector for the data 
        transfer
   
  @param[in] pUser   User pointer that will be passed back 
        during an asynchronous BAM callback event for the
        descriptor
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_GetBamIOVec(), DalSlimBus_GetBamIOVecEx()
  */
static __inline DALResult
DalSlimBus_SubmitBamTransfer(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusBamIOVecType * pIOVec, void * pUser)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->SubmitBamTransfer( _h, hPort, eTransferDir, pIOVec, pUser);
}


/**
  @brief Get a processed BAM IO-vector 

  This function fetches the next processed BAM IO-vector.  The 
  IO-vector structure will be zeroed if there are no more 
  processed IO-vectors. 

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Master port handle corresponding to the BAM 
        pipe
   
  @param[in] eTransferDir  Direction of data flow for the BAM
        pipe to get the IO-vector for.  For bi-directional
        ports, there is one BAM pipe for each of the transmit
        and receive directions.
   
  @param[out] pIOVec  Pointer to the location to store a 
        processed IO-vector.  The structure will be zeroed if
        there are no more processed IO-vectors.
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_SubmitBamTransfer(), 
       DalSlimBus_GetBamIOVecEx()
  */
static __inline DALResult
DalSlimBus_GetBamIOVec(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusBamIOVecType * pIOVec)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->GetBamIOVec( _h, hPort, eTransferDir, pIOVec);
}


/**
  @brief Get a processed BAM IO-vector with user data

  This function fetches the next processed BAM IO-vector.  The 
  IO-vector structure will be zeroed if there are no more 
  processed IO-vectors.  The user data pointer is optional and 
  if supplied will be filled with the user data pointer passed 
  when the descriptor was submitted. 

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Master port handle corresponding to the BAM 
        pipe
   
  @param[in] eTransferDir  Direction of data flow for the BAM
        pipe to get the IO-vector for.  For bi-directional
        ports, there is one BAM pipe for each of the transmit
        and receive directions.
   
  @param[out] pIOVec  Pointer to the location to store a 
        processed IO-vector.  The structure will be zeroed if
        there are no more processed IO-vectors.
   
  @param[out] ppUser  Pointer to location to store the user data 
        pointer associated with a processed IO-vector.  The
        pointer will be NULL if there are no more processed
        IO-vectors.
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_SubmitBamTransfer(), DalSlimBus_GetBamIOVec()
  */
static __inline DALResult
DalSlimBus_GetBamIOVecEx(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusBamIOVecType * pIOVec, void **ppUser)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->GetBamIOVecEx( _h, hPort, eTransferDir, pIOVec, ppUser);
}


/**
  @brief Read the event queue for a BAM pipe

  This function reads the event queue for a BAM pipe.  Events 
  will be added to the queue when they have been registered 
  using a non-callback trigger. 

  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Master port handle corresponding to the BAM 
        pipe
   
  @param[in] eTransferDir  Direction of data flow for the BAM
        pipe to read the event queue.  For bi-directional ports,
        there is one BAM pipe for each of the transmit and
        receive directions.
   
  @param[out] pEvent  Pointer to the location to store the event
        read from the queue.
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_RegisterBamEvent()
  */
static __inline DALResult
DalSlimBus_GetBamEvent(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusBamEventType * peEvent)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->GetBamEvent( _h, hPort, eTransferDir, peEvent);
}


/** @} */
/**
   @name Port Maintenance Functions
   
   This section describes the API for data port maintenance. 
  */
/** @{ */


/**
  @brief Get the FIFO status of a SLIMbus master port 
   
  This function retrieves the FIFO status of a SLIMbus master 
  port.
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Master port handle
   
  @param[in] eTransferDir  Direction of data flow for FIFO to 
        get the status for.  For bi-directional ports, there is
        one FIFO for each of the transmit and receive
        directions.
   
  @param[out] puFifoWordCnt  Pointer to the location to store 
        the FIFO word count

  @param[out] pbWatermarkIsHit  Pointer to the location to store
        a boolean value indicating whether the watermark has
        been hit or not

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_ConfigMasterPort() 
  */
static __inline DALResult
DalSlimBus_GetPortFifoStatus(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, uint32 * puFifoWordCnt, DALBOOL * pbWatermarkIsHit)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->GetPortFifoStatus( _h, hPort, eTransferDir, puFifoWordCnt, pbWatermarkIsHit);
}


/**
  @brief Register for specific asynchronous SLIMbus master port 
         events
   
  This function registers for specific asynchronous SLIMbus 
  master port events.  When the event object is signaled, the 
  condition that triggered the event will be available for 
  retrieval by the DalSlimBus_GetPortEvent() function.  Calls to 
  this function for a particular port will supersede any 
  previous calls to this function or to 
  DalSlimBus_RegisterPortEvent() for the port. 
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Master port handle
   
  @param[in] hEvent  Event handle to receive asynchronous port 
        event notifications
   
  @param[in] pUser  User pointer that will be returned in event 
        notification structure
   
  @param[in] eType  Type of port events to register for 
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_GetPortEvent()
  */
static __inline DALResult
DalSlimBus_RegisterPortEventEx(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, DALSYSEventHandle  hEvent, void * pUser, SlimBusPortEventType eType)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->RegisterPortEventEx( _h, hPort, hEvent, pUser, eType);
}


/**
  @brief Register for all asynchronous SLIMbus master port 
         events
   
  This function registers for all asynchronous SLIMbus master 
  port events.  When the event object is signaled, the condition
  that triggered the event will be available for retrieval by 
  the DalSlimBus_GetPortEvent() function.  Calls to this 
  function for a particular port will supersede any previous 
  calls to this function or to DalSlimBus_RegisterPortEventEx() 
  for the port. 
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Master port handle
   
  @param[in] hEvent  Event handle to receive asynchronous port 
        event notifications
   
  @param[in] pUser  User pointer that will be returned in event 
        notification structure

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_GetPortEvent()
  */
static __inline DALResult
DalSlimBus_RegisterPortEvent(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, DALSYSEventHandle  hEvent, void * pUser)
{
   return DalSlimBus_RegisterPortEventEx( _h, hPort, hEvent, pUser, SLIMBUS_EVENT_O_DEFAULTS);
}


/**
  @brief Read information on recent port events
   
  This function reads information on recent asynchronous port 
  events.
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Master port handle; this parameter can be 
        set to NULL to get the pending events for any port owned
        by the client
   
  @param[out] pNotify  Pointer to event notification structure 

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_ConfigMasterPort(), 
       DalSlimBus_RegisterPortEvent()
  */
static __inline DALResult
DalSlimBus_GetPortEvent(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusEventNotifyType * pNotify)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->GetPortEvent( _h, hPort, pNotify);
}


/** @} */
/**
   @name Audio Progress Counter Functions
   
   This section describes the API for managing audio progress 
   counters. 
  */
/** @{ */


/**
  @brief Allocate a port progress counter.
   
  This function allocates a progress counter for a SLIMbus 
  master port.  Progress counters are typically used for audio 
  sync applications. 
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hPort  Master port handle that the progress counter 
        should be associated with
  
  @param[in] eTransferDir  Direction of data flow for the BAM 
        pipe to allocate the progress counter for.  For
        bi-directional ports, there is one BAM pipe for each of
        the transmit and receive directions.
   
  @param[out] phCounter  Pointer to location to store allocated
        progress counter handle

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocMasterPorts(), 
       DalSlimBus_DeallocProgressCounter()
  */
static __inline DALResult
DalSlimBus_AllocProgressCounter(DalDeviceHandle * _h, SlimBusResourceHandle  hPort, SlimBusBamTransferType  eTransferDir, SlimBusResourceHandle * phCounter)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->AllocProgressCounter( _h, hPort, eTransferDir, phCounter);
}


/**
  @brief Deallocate a port progress counter.
   
  This function deallocates a progress counter for a SLIMbus 
  master port.  Progress counters are typically used for audio 
  sync applications. 
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hCounter  Progress Counter handle

  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocProgressCounter()
  */
static __inline DALResult
DalSlimBus_DeallocProgressCounter(DalDeviceHandle * _h, SlimBusResourceHandle  hCounter)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->DeallocProgressCounter( _h, hCounter);
}


/**
  @brief Initialize the value of a port progress counter.
   
  This function initializes the value of a SLIMbus master port 
  progress counter.
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hCounter  Progress Counter handle
   
  @param[in] uCount  Value to initialize the progress counter 
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocProgressCounter(), 
       DalSlimBus_ReadProgressCounter()
  */
static __inline DALResult
DalSlimBus_InitProgressCounter(DalDeviceHandle * _h, SlimBusResourceHandle  hCounter, uint32  uCount)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->InitProgressCounter( _h, hCounter, uCount);
}


/**
  @brief Read the value of a port progress counter. 
   
  This function reads the value of a SLIMbus master port 
  progress counter.  Either the free running counter, VFR
  counter or shadow counter can be read. 
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hCounter  Progress Counter handle 
   
  @param[in] eType  The type of counter to read, either the free 
        running, VFR or shadow counter
   
  @param[out] puNumDMA  Pointer to store the number of 32-bit 
        words DMA-ed to or from the associated port
   
  @param[out] puFifoSamples  Number of samples currently in the 
        port FIFO plus and samples in the phy/FL stages,
        taking into account segment length and bit packing
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_InitProgressCounter(), 
       DalSlimBus_ReadProgressCounterVFRStatus()
  */
static __inline DALResult
DalSlimBus_ReadProgressCounter(DalDeviceHandle * _h, SlimBusResourceHandle  hCounter, SlimBusCounterType  eType, uint32 * puNumDMA, uint32 * puFifoSamples)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ReadProgressCounter( _h, hCounter, eType, puNumDMA, puFifoSamples);
}


/**
  @brief Read the value of a port shadow progress counter and 
         timestamp.
 
  This function reads the value of a SLIMbus master port shadow 
  progress counter and timestamp.
  
  @param[in] _h  Client handle to the SLIMbus driver
   
  @param[in] hCounter  Progress Counter handle
   
  @param[out] puNumDMA  Pointer to store the number of 32-bit 
        words DMA-ed to or from the associated port at the last
        DMA interrupt
   
  @param[out] puFifoSamples  Number of samples that were in the 
        port FIFO plus samples in the phy/FL stages, taking
        into account segment length and bit packing, at the
        last DMA interrupt
   
  @param[out] puTimestamp  Pointer to store the timestamp value
        for the last DMA interrupt
   
  @param[out] pbSampleMissed  Pointer to store indication of 
        whether a DMA timestamp values have been missed
  
  @return DAL_SUCCESS if the timestamp sample and counter 
          values are valid, error code otherwise
   
  @see DalSlimBus_ReadProgressCounter() 
 */
static __inline DALResult
DalSlimBus_ReadProgressCounterTimestamp(DalDeviceHandle * _h, SlimBusResourceHandle hCounter, uint32 *puNumDMA, uint32 *puFifoSamples, uint64 *puTimestamp, DALBOOL *pbSampleMissed)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ReadProgressCounterTimestamp( _h, hCounter, puNumDMA, puFifoSamples, puTimestamp, pbSampleMissed);
}

/**
  @brief Read the status of whether a progress counter VFR 
         interrupt pulse has occurred.
   
  This function reads the status of whether a progress counter 
  VFR interrupt pulse has occurred.  The status is cleared by 
  the DalSlimBus_ClearProgressCounterVFRStatus() function.
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hCounter  Progress Counter handle 
   
  @param[out] pbSet  Pointer to store boolean indicating whether
        VFR interrupt pulse has occurred
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_InitProgressCounter(), 
       DalSlimBus_ClearProgressCounterVFRStatus()
  */
static __inline DALResult
DalSlimBus_ReadProgressCounterVFRStatus(DalDeviceHandle * _h, SlimBusResourceHandle  hCounter, DALBOOL * pbSet)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ReadProgressCounterVFRStatus( _h, hCounter, pbSet);
}


/**
  @brief Clear the progress counter VFR interrupt pulse status. 
   
  This function clears the progress counter VFR interrupt pulse 
  status.
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hCounter  Progress Counter handle 
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_InitProgressCounter(), 
       DalSlimBus_ReadProgressCounterVFRStatus()
  */
static __inline DALResult
DalSlimBus_ClearProgressCounterVFRStatus(DalDeviceHandle * _h, SlimBusResourceHandle  hCounter)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->ClearProgressCounterVFRStatus( _h, hCounter);
}


/** @} */
/**
   @name  Resource Group Functions
   
   This section describes the API for managing resource groups. 
  */
/** @{ */


/**
  @brief Allocate a resource group.
   
  This function allocates a resource group used to manipulate
  multiple resources at the same time. 
   
  Resource groups are currently supported by the following 
  functions: DalSlimBus_NextDefineDataChannel(), 
  DalSlimBus_NextDataChannelControl() 
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[out] phGroup  Pointer to location to store allocated 
        resource group handle
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_DeallocResourceGroup(), 
       DalSlimBus_AddResourceToGroup(),
       DalSlimBus_NextDefineDataChannel(),
       DalSlimBus_NextDataChannelControl()
  */
static __inline DALResult
DalSlimBus_AllocResourceGroup(DalDeviceHandle * _h, SlimBusResourceHandle * phGroup)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->AllocResourceGroup( _h, phGroup);
}


/**
  @brief Deallocate a resource group.
   
  This function deallocates a resource group used to manipulate
  multiple resources at the same time. 
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hGroup  resource group handle
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocResourceGroup(), 
       DalSlimBus_AddResourceToGroup()
  */
static __inline DALResult
DalSlimBus_DeallocResourceGroup(DalDeviceHandle * _h, SlimBusResourceHandle  hGroup)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->DeallocResourceHroup( _h, hGroup);
}


/**
  @brief Add a resource to a resource group.
   
  This function adds a resource to a resource group.  All 
  resources within a group must be of the same type.  A resource 
  is limited to belonging to a single group at a time.
   
  Currently only data channel resources can
  be added to a resource group. 
   
  @param[in] _h  Client handle to the SLIMbus driver 
   
  @param[in] hGroup  resource group handle 
   
  @param[in] hResource  resource handle to add to the group 
   
  @return  DAL_SUCCESS on success, an error code on error
   
  @see DalSlimBus_AllocResourceGroup(), 
       DalSlimBus_DeallocResourceGroup(),
       DalSlimBus_NextDefineDataChannel(),
       DalSlimBus_NextDataChannelControl()
  */
static __inline DALResult
DalSlimBus_AddResourceToGroup(DalDeviceHandle * _h, SlimBusResourceHandle  hGroup, SlimBusResourceHandle hResource)
{
   return ((DalSlimBusHandle *)_h)->pVtbl->AddResourceToGroup( _h, hGroup, hResource);
}


/** @} */

#endif /* DDISLIMBUS_H */
