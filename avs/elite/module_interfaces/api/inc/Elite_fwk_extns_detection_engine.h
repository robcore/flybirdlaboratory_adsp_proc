#ifndef ELITE_FWK_EXTNS_DETECTION_ENGINE_H
#define ELITE_FWK_EXTNS_DETECTION_ENGINE_H

/**
  @file Elite_fwk_extns_detection_engine.h

  @brief Parameters required to be implemented by Detection Engine module

  This file defines a framework extensions for Detection Engine modules.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      Elite_CAPIv2_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*==============================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.6.1/elite/module_interfaces/api/inc/Elite_fwk_extns_detection_engine.h#3 $

  when        who      what, where, why
  --------    ---      -------------------------------------------------------
  11/23/14    sw      (Tech Pubs) Edited Doxygen markup/comments for 2.6.
  08/05/14    Unni     Publishing as a framework extension in
                                    elite/module_interfaces/api/inc/
  07/07/14    Unni     derived by splitting listen/services/dynamic_svcs/
                                    listen_proc_svc/inc/ListenProcSvc_CustMsg.h
==============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/*------------------------------------------------------------------------------
 * Include Files
 *----------------------------------------------------------------------------*/
#include "Elite_CAPI_V2_types.h"

/** @addtogroup capiv2_ext_det_engine
@{ */

/** Unique identifier used to represent a module that supports the Detection
    Engine Framework extension.

    This extension supports the PARAM_ID_DETECTION_ENGINE_STATUS parameter.
*/
#define FWK_EXTN_DETECTION_ENGINE 0x00012C0F

/*------------------------------------------------------------------------------
 * Parameter definitions - Needs implementation in module/library
 *----------------------------------------------------------------------------*/

/** Parameter used to raise a detection engine status event.
    The endpoint of this event is the aDSP service.

    This parameter does the following:
    - Advertises status updates
    - Attaches the variable payload
    - Enables Debug mode

    For example, the LSM and LAB services currently hosted in the aDSP support
    this extension by doing the following:
    - If a module returns LSM_DETECTION_ENGINE_STATUS_DETECTED, the LSM service
      notifies LSM clients and votes for a hardware duty cycle reset. \n
      If the LAB session or another LSM session is active and sharing the same
      hardware, the votes are aggregated before they are applied.
    - If a module returns LSM_DETECTION_ENGINE_STATUS_DISCOVERY and the LAB
      session is active, the data is buffered. This data is later flushed by
      removing the keyword from it once the keyword position is determined by
      PARAM_ID_KW_END_POSITION.
    - If the module returns LSM_DETECTION_ENGINE_STATUS_REJECTED, the LSM
      service votes for a hardware duty cycle reset. If the module sets
      is_debug_mode = TRUE, the LSM service notifies the client of the
      rejection status. @newpage

    @msgpayload{detection_engine_status_t}
    @tablens{weak__detection__engine__status__t}
*/  /* See also Elite_CAPI_V2_events.h */
#define PARAM_ID_DETECTION_ENGINE_STATUS 0x00012C10

/** @weakgroup weak_detection_engine_status_t
@{ */
/** Generic data structure used when querying the detection engine status.
*/
typedef struct 
{
  bool_t is_debug_mode;
  /**< Specifies whether debugging is enabled.

       @values
       - 0 -- FALSE
       - 1 -- TRUE

       When set to TRUE, the aDSP service forwards additional events to HLOS
       application clients. */

  uint8_t status;
  /**< Status returned by algorithm
       
       @values
       - 0x2 (LSM_DETECTION_STATUS_DETECTED)
         - Notifies the aDSP service that the module has detected a keyword.
         - This status is forwarded to the client regardless of the
           is_debug_mode value.
       - 0x4 (LSM_DETECTION_STATUS_REJECTED)
         - Notifies the aDSP service that the module has rejected a keyword.
         - This status is forwarded to the client only if is_debug_mode 
           is enabled (is_debug_mode = 1).
       - 0x5 (LSM_DETECTION_STATUS_DISCOVERY)
         - Notifies the aDSP service that the module is in Discovery mode.
         - Discovery is a transitional/predetection state of the module.
         - This status is not forwarded to the client regardless of the
           is_debug_mode value.

       For more information on LSM, refer to @xhyperref{Q6,[Q6]}. */
  /* Q6 = Hex MM: LSM API Interface Spec for ADSP.BF.2.6 (80-NF770-5)
     See also adsp_lsm_session_commands.h */

  uint8_t payload_size;
  /**< Size of the payload returned by the algorithm. */

  int8_t *payload_ptr;
  /**< Pointer to the payload; interpreted by HLOS application clients. */

}detection_engine_status_t;
/** @} */ /* end_weakgroup weak_detection_engine_status_t */

/** @} */ /* end_addtogroup capiv2_ext_det_engine */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* #ifndef ELITE_FWK_EXTNS_DETECTION_ENGINE_H */
