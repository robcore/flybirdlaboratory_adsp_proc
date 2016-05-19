#ifndef QMI_CCI_TARGET_EXT_H
#define QMI_CCI_TARGET_EXT_H
/******************************************************************************
  @file    qmi_cci_target_ext.h
  @brief   QMI CCI OS Specific macro/types externalized to clients.

  DESCRIPTION
  QMI OS Specific types and macros required by QCCI clients.

  ---------------------------------------------------------------------------
  Copyright (c) 2010-2011 Qualcomm Technologies Incorporated. All Rights Reserved. 
  QUALCOMM Proprietary and Confidential.
  ---------------------------------------------------------------------------
*******************************************************************************/
#include "comdef.h"
#include "qurt.h"
#include "timer.h"
#include "msg.h"

/* OS Specific parameters provided by User on client and 
 * Notifier initialization. 
 * NULL is a valid OS parameter for qmi_client_init() or qmi_client_init_instance().
 */
typedef struct {
  /***************************
   *     USER SET MEMBERS    *
   ***************************/

  /* (Optional) Use a provided initialized signal structure.
   * This field is useful for notifier clients (initialized
   * using qmi_client_notifier_init() and will be ignored
   * otherwise) */
  qurt_anysignal_t  *ext_signal;

  /* Event signal mask to be used for events.
   * Set to 0 to let QCCI pick one for you */
  unsigned int      sig;

  /* Timer signal mask to be used for timeout. 
   * Set to 0 to let QCCI pick one for you */
  unsigned int      timer_sig;

  /***************************
   *     PRIVATE MEMBERS     *
   ***************************/
  qurt_anysignal_t  signal;
  timer_type        timer;
  boolean           timer_inited;
  boolean           timed_out;
} qmi_cci_os_signal_type;

typedef qmi_cci_os_signal_type qmi_client_os_params;

#define QMI_CCI_OS_SIGNAL qmi_cci_os_signal_type

#define is_pow_2(val) (((val) & ((val) - 1)) == 0 ? TRUE : FALSE)

#define QMI_CCI_OS_SIGNAL_INIT(ptr, os_params) \
  do { \
    if(os_params) { \
      (ptr)->sig = (os_params)->sig; \
      (ptr)->timer_sig = (os_params)->timer_sig; \
    } else {  \
      (ptr)->sig = 1; \
      (ptr)->timer_sig = 2; \
    } \
    (ptr)->ext_signal = NULL; \
    (ptr)->timer_inited = FALSE; \
    (ptr)->timed_out = 0; \
    qurt_anysignal_init(&((ptr)->signal));  \
    if((ptr)->timer_sig != 0 && (ptr)->timer_sig != (ptr)->sig && !is_pow_2((ptr)->timer_sig)) { \
      timer_error_type err; \
      err = timer_def_osal(&((ptr)->timer), NULL, TIMER_NATIVE_OS_SIGNAL_TYPE, &((ptr)->signal), (ptr)->timer_sig); \
      if (err == TE_SUCCESS) { \
        (ptr)->timer_inited = TRUE; \
      } else { \
        MSG_ERROR("QCCI: ATS timer creation failed with error=%d.", err, 0, 0); \
      } \
    } \
  } while(0)

#define QMI_CCI_OS_SIGNAL_DEINIT(ptr) \
  do {  \
    (ptr)->sig = 0;     \
    if((ptr)->timer_inited == TRUE) { \
      timer_clr_64(&((ptr)->timer), T_MSEC); \
      timer_undef(&((ptr)->timer)); \
      (ptr)->timer_inited = FALSE; \
    } \
    if((ptr)->ext_signal == NULL) { \
      qurt_anysignal_destroy(&(ptr)->signal); \
    } \
  } while(0)

#define QMI_CCI_OS_SIGNAL_CLEAR(ptr) \
  qurt_anysignal_clear((ptr)->ext_signal ? (ptr)->ext_signal : &(ptr)->signal, (ptr)->sig | (ptr)->timer_sig)

#define QMI_CCI_OS_SIGNAL_WAIT(ptr, timeout_ms) \
  do { \
    (ptr)->timed_out = 0; \
    if((timeout_ms) && ((ptr)->timer_inited)) { \
      timer_set_64(&((ptr)->timer), (timeout_ms), 0, T_MSEC); \
      qurt_anysignal_wait((ptr)->ext_signal ? (ptr)->ext_signal : &(ptr)->signal, (ptr)->sig | (ptr)->timer_sig); \
      (ptr)->timed_out = (qurt_anysignal_get((ptr)->ext_signal ? (ptr)->ext_signal : &(ptr)->signal) & (ptr)->timer_sig) != 0;  \
      timer_clr_64(&((ptr)->timer), T_MSEC); \
    } else { \
      qurt_anysignal_wait((ptr)->ext_signal ? (ptr)->ext_signal : &(ptr)->signal, (ptr)->sig); \
    } \
  } while(0)

#define QMI_CCI_OS_SIGNAL_TIMED_OUT(ptr) (ptr)->timed_out
#define QMI_CCI_OS_SIGNAL_SET(ptr) qurt_anysignal_set((ptr)->ext_signal ? (ptr)->ext_signal : &(ptr)->signal, (ptr)->sig)

#endif
