#ifndef ERR_H
#define ERR_H

/*===========================================================================

                    Error Handling Common Header File

Description
  The error handling services (ERR) provide user error handling services
  through an assert-like ERR_FATAL macro.  Calling this macro indicates an
  unrecoverable error. Other services are provided as defined by the APIs
  in this header file.

Copyright (c) 1992-2014 by Qualcomm Technologies Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                           Edit History

$Header: //components/rel/core.adsp/2.6.1/api/debugtools/err.h#1 $


when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/31/14   din     Added support for Error on User PD. 
04/18/14   din     Added changes for ADSP island mode.
05/23/08   tbg     Added FEATURE_EXTERNAL_ERR_FATAL
04/04/08   tbg     FEATURE_GENERIC_ERR_FATAL_MSG for additional configurations
12/18/07   taw     Use IMAGE_APPS_PROC instead of DIAG_APPS_PROC around
                   err_lcd_message.
01/08/07   tbg     Added support for new err_auto_action API.
12/19/06   as      Reverted FEATURE_ERR_SMALL_BUFFER change.
12/18/06   as      Added support to decrease buffer size under
                   FEATURE_ERR_SMALL_BUFFER.
11/11/05   tbg     Changed ERR_EXTENDED_STORE to share NV item for max files
                   with debug trace (if feature is defined)
06/29/05   as      Increased ERR_DATA_MAX_SIZE.
04/17/04   ash     Added (FEATURE_MEM_USAGE_AT_EXCEPTION)
                   for application memory usage during crash
08/03/04   tbg     Extended FEATURE_ERR_EXTENDED_STORE to support multiple
                   files on EFS, as well as multiple logs per session.
07/09/04   eav     Added feature to save ERR_FATAL to trace buffer as a message
04/27/04   eav     Moved ERR_DATA_MAGIC_NUMBER and ERR_DATA_RESET_MAGIC_NUMBER
                   here so it is accessible from msg.c.
04/06/04   tbg     Added FAETURE_ERR_EXTENDED_STORE
10/08/03   gr      Redefined ERR_FATAL to make one function call instead of
                   three to save code space.
07/24/03   as      Added ERR_FATAL_REPORT(   ) macro
11/14/02   jct     Added REX core dump to ERR_FATAL
09/13/02   et      added ERR_LOG macro to log err to NV w/o F3 msg
08/20/02   lad     F_DIAG_COUPLED_ARCHITECTURE support.
04/06/01   lad     Added T_THOR to feature list.
02/23/01   lad     Changes for portability and re-use.
02/02/00   lad     Changed macros to parse as single expressions.
06/30/99   jct     Added PC_EMULATOR support for ERR_FATAL, made inclusion
                   of target.h conditional, added decoupling of inclusion of
                   nv.h based on assertion of FEATURE_ERR_DECOUPLE_NVM.
                   This allows resuse of ERR_FATAL in environment where NV is
                   not supported.
06/02/99   lad     Fixed multi-line macros to evaluate as single expression.
04/28/99   ms/sk   Inserted call to clear SL register in ERR_FATAL.
11/05/98   jct     Merged in changes for ARM targets.  Make calls to err_
                   functions const correct.
01/22/97   rdh     Used Pascal directive on err_*_put_log to save ROM.
07/24/95   jah     Changed ERR/ERR_FATAL() macro to use msg_file if MSG_FILE
                   is defined.
06/18/93   jah     Removed MSG_FATAL from phone version of ERR_FATAL() macro,
                   as it takes code space and the phone resets before the DM
                   can get the results from MSG.
10/29/92   ip      Updated for release of full error logging.
08/03/92   ip      Removed '{' and '}' from ERR_...
07/06/92   ip      Fixed target include files, added '{' and '}' to ERR_...
05/13/92   ip      Removed parentheses around 'format' in MSG_... calls.
03/07/92   ip      First porting of file from brassboard to subscriber.

===========================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

#include "comdef.h"
#include <stdio.h>

/* DEPRECATION FLAG */
#ifndef ERR_DEPRECATED_ATTRIBUTE
  #define ERR_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#endif

/* NO RETURN FLAG */
#ifndef ERR_NORETURN_ATTRIBUTE
  #define ERR_NORETURN_ATTRIBUTE __attribute__((noreturn))
#endif

/* Island mode code section */
#ifndef UERR_CODE_SECTION
  #define UERR_CODE_SECTION __attribute__((section (".text.uErr")))
#endif

/* Island mode data section */
#ifndef UERR_DATA_SECTION	
#define UERR_DATA_SECTION __attribute__((section (".data.uErr")))
#endif

/*
#if (defined(__ARMCC_VERSION) && (__ARMCC_VERSION > 200000)) || (defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)))
#define ERR_DEPRECATED __attribute__ ((deprecated))
#else
#define ERR_DEPRECATED
#endif
 */

typedef struct
{
 const char *fmt;      /* Printf style format string */
 const char *fname;    /* Pointer to source file name */
 uint16 line;    /* Line number in source file */
} err_FatalParam_type;

#ifdef FEATURE_EXTERNAL_ERR_FATAL

/* This is a generic feature to allow code such as third party operating
 * systems not specifically defined below to remove the definitions of
 * ERR_FATAL found in this file and provide their own.
 */

/* Currently this block is intentionally left empty of code */

#elif defined (FEATURE_Q6SIM)
/* Used for off-target testing using qdsp6-sim */

#include <stdlib.h>
#include "msg.h"

#define ERR(str, a, b, c) MSG_ERROR("ERR: " str, a, b, c)
#define ERR_FATAL(str, a, b, c) \
  do {                          \
    ERR(str, a, b, c);          \
    exit(1);                    \
  } while(0)

#else


#ifdef TG
#include "target.h"
#endif

#include "msg.h"


#define ERR_HAS_NV_LOG_PACKET /* flag to indicate that ERR code will register
                                 the NV log read and clear packets. Definitions
								 for these packets are given below. */

/* -------------------------------------------------------------------------
   Definitions and Declarations
   ------------------------------------------------------------------------- */

/* Type used for post-crash callbacks from error handler */
typedef void (*err_cb_ptr)(void);

/* Status returned from err_get_log and err_clr_log. */

typedef enum
{
  ERR_DONE_S,           /* Request completed OK */
  ERR_NONE_S            /* No such log number */
}
err_stat_type;

#ifdef FEATURE_GENERIC_ERR_FATAL_MSG
extern const char err_generic_msg[];
#endif


/* -------------------------------------------------------------------------
   Function Definitions
   ------------------------------------------------------------------------- */




/*===========================================================================

FUNCTION ERR_INIT

DESCRIPTION
  This function checks if NV has been built.  If so then it loads up the
  error log cache from NV, it initializes error counts and local variables,
  and it sets error services to online.  If NV has not been built then
  error log is not loaded and error services remain offline and error
  logging does not take place.  Any access to NV is performed here directly,
  without relying on the NV task.  Thus error service can be initialized
  and used early in the life of the DMSS and right after boot.  Note
  that if NV has not been built, error services provide no error logging
  capabilities.  However NV is built once, after initial factory startup,
  and rarely thereafter.  Thus except for the first ever powerup of the
  unit after NV build or re-build, error logging will take place as usual.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  Error log is loaded from NVM into RAM resident cache.

===========================================================================*/
  void err_init (void);

/*=========================================================================

FUNCTION err_crash_cb_register

DESCRIPTION
  Registers a function (ptr type err_cb_ptr) to be called after an ERR_FATAL
  Function should NOT rely on any messaging, task switching (or system calls
  that may invoke task switching), interrupts, etc.
 
  !!!These functions MUST NOT call ERR_FATAL under ANY circumstances!!!

DEPENDENCIES
  None
 
RETURN VALUE
  TRUE if function added to table successfully
  FALSE if function not added.
  
SIDE EFFECTS
  None

===========================================================================*/
boolean err_crash_cb_dereg(err_cb_ptr cb);
boolean err_crash_cb_register(err_cb_ptr cb);

/*===========================================================================

FUNCTION ERR_CLR_LOG

DESCRIPTION
  This function clears a specific error record both in cache and in NV.
  An error record is cleared simply by clearing the error count field
  in it.

  If 'log_num' == 0xFF, all logs will be cleared.

DEPENDENCIES
  err_init must be called before this call, otherwise no operation
  takes place and ERR_NONE_S completion status is returned.

RETURN VALUE
  ERR_DONE_S    - Requested error record existed and cleared.
  ERR_NONE_S    - Error record out of range or clear failed.

SIDE EFFECTS
  The specified error record is cleared in NV and in cache and is now
  available to accept a new unique error.

===========================================================================*/
  err_stat_type err_clr_log (byte log_num);

/*===========================================================================

FUNCTION ERR_PUT_LOG

DESCRIPTION
  Stub for functionality not supported on adsp

DEPENDENCIES

RETURN VALUE
  None.

SIDE EFFECTS
  

===========================================================================*/
  void err_put_log (word line, const char *file_ptr);

/*===========================================================================


FUNCTION ERR_FATAL_LOCK
DESCRIPTION
  Obtains err_fatal mutex

============================================================================*/
void err_fatal_lock( void );


/*===========================================================================

MACRO ERR

DESCRIPTION
  Log an error to error log and update cache and return to caller.
  Error is sent to the MSG utility to be routed to DM or PC screen,
  depending on conditional compile switches defined in MSG.  If host
  is a PC then NV logging does not take place and only MSG output
  is used.

DEPENDENCIES
  If MSG_FILE is defined, ERR uses it as the filename.

RETURN VALUE
  None.

SIDE EFFECTS
  When the host is target hardware a call is generated to err_put_log
  to queue log request to NV task.  As a result unexpected execution
  times are likely to take place.  ERR must only be called because of
  an error condition (never as an information announcement -- use MSG
  for that) therefore these timing side effect are OK.

===========================================================================*/

#define ERR_FILE_NAME   msg_file

/* Map to MSG_ERR_LOG for memory savings.
   Equivalent to calling:
     MSG_ERROR(format, (code1), (code2), (code3));
     err_put_log ((word) __LINE__, ERR_FILE_NAME);
 */
#define  ERR(format, code1, code2, code3)          \
  MSG_ERR_LOG (3, format, code1, code2, code3)


/*===========================================================================

MACRO ERR_FATAL

DESCRIPTION
  Log an error to error log, update the cache (for debug purpose only)
  and RESET THE SYSTEM.  Control DOES NOT RETURN to caller.  Error is
  sent to the MSG utility to be routed to DM or PC screen, depending
  on conditional compile switches defined in MSG.  If host is a PC
  then NV logging does not take place.  Instead a MSG output is made
  and the program exits (simulating hardware reset of sorts).

DEPENDENCIES
  If MSG_FILE is defined, ERR_FATAL uses it as the filename.

RETURN VALUE
  None.  Control does NOT return to caller.

SIDE EFFECTS
  When the host is target hardware a call is generated to err_put_log
  to queue log request to NV task.  As a result unexpected execution
  times are likely to take place.  ERR_FATAL must only be called because
  of an error condition (never as an information announcement -- use MSG
  for that) therefore these timing side effects are OK.

===========================================================================*/

/*===========================================================================

MACRO ERR_FATAL_REPORT

DESCRIPTION
  DEPRECATED

===========================================================================*/

  /* Prototypes register core dump function */
  extern void jettison_core( void );

#if defined (FEATURE_FATAL_SECTION)

/********************
 NOTE:
  Define FEATURE_FATAL_SECTION *globally* to enable this feature. Necesary
  scatter loader/linker script sections, etc. must be defined as needed and
  are *not* the responsibility of error services.  This FEATURE is required
  for error compression to work (external dependencies belong to
  modem performance team)

 *********************/

#ifdef __cplusplus
#define SECT_EXT __FILE__
#else
#define SECT_EXT
#endif

#define _XX_MSG_CONST(xx_ss_id, xx_ss_mask, xx_fmt) \
        static const char _xx_fmt [] __attribute__ ((section ("fatal.fmt.rodata." SECT_EXT))) = {xx_fmt}; \
        static const msg_const_type xx_msg_const __attribute__ ((section ("fatal.struct.rodata." SECT_EXT))) = { \
              {__LINE__, (xx_ss_id), (xx_ss_mask)}, (_xx_fmt), msg_file}

#else

#define _XX_MSG_CONST(xx_ss_id, xx_ss_mask, xx_fmt) XX_MSG_CONST(xx_ss_id, xx_ss_mask, xx_fmt)

#endif

void err_SaveFatal3 (const msg_const_type* const_blk, uint32 code1, uint32 code2, uint32 code3) ERR_NORETURN_ATTRIBUTE UERR_CODE_SECTION ;;
void err_SaveFatal0 (const msg_const_type* const_blk) ERR_NORETURN_ATTRIBUTE UERR_CODE_SECTION ;


  #define ERR_FATAL(format, code1, code2, code3) \
  do {                                                                     \
    if ((0!=(uint32)(code1))||(0!=(uint32)(code2))||(0!=(uint32)(code3))) {      \
      ERR_FATAL_VAR(format, 3, code1, code2, code3);                       \
    } else {                                                               \
      ERR_FATAL_VAR(format, 0, code1, code2, code3);                       \
    }                                                                      \
  } while (0)

  #define ERR_SAVE_FATAL_PAR(Msg, NbPar, Par1, Par2, Par3)  \
  switch (NbPar)                                         \
  {                                                      \
   case 0:                                               \
   err_SaveFatal0 (Msg);                                 \
   break;                                                \
   case 3:                                               \
   default:                                              \
   err_SaveFatal3 (Msg, Par1, Par2, Par3);               \
   break;                                                \
  }


#ifdef FEATURE_GENERIC_ERR_FATAL_MSG
  #define ERR_FATAL_VAR(format, NbPar, code1, code2, code3)                     \
    do                                                                       \
    {                                                                        \
        _XX_MSG_CONST( MSG_SSID_DFLT, MSG_LEGACY_FATAL, err_generic_msg );    \
        ERR_SAVE_FATAL_PAR (&xx_msg_const, NbPar, (uint32)(code1), (uint32)(code2), (uint32)(code3))  \
     /*lint -save -e{717} */                                                 \
     } while (0)                                                             \
     /* lint -restore */

#else
  #define ERR_FATAL_VAR(format, NbPar, code1, code2, code3)                     \
    do                                                                       \
    {                                                                        \
        _XX_MSG_CONST( MSG_SSID_DFLT, MSG_LEGACY_FATAL, format );             \
        ERR_SAVE_FATAL_PAR (&xx_msg_const, NbPar, (uint32)(code1), (uint32)(code2), (uint32)(code3))  \
     /*lint -save -e{717} */                                                 \
     } while (0)                                                             \
     /* lint -restore */

#endif /* FEATURE_GENERIC_ERR_FATAL_MSG */

  #define ERR_FATAL_NO_SAVE(format, code1, code2, code3)                     \
          ERR_FATAL_REPORT(format, code1, code2, code3)


/*===========================================================================

MACRO ERR_FATAL_DYNAMIC_MSG

DESCRIPTION
  Accepts a backward compatible, zero-parameter ERR_FATAL string, as well
  as an apporpriate callback function to fill a dynamic messgae buffer
  which is stored in the coredump.err.aux_msg as well as being sent to 
  apps processor via SFR smem.

  The macro is not available for Island mode.

NOTE
  The SFR created by this message is parsed by some HLOS's/customers.
  As such format maybe important.  Please consult with owners before
  using.

DEPENDENCIES
  None

RETURN VALUE
  None.  Control does NOT return to caller.

SIDE EFFECTS
  Terminates processing, dumps core

===========================================================================*/
typedef void (*err_dynamic_msg_cb)(char* const, const uint16, const uint32);

void err_SaveFatal_dynamic (const msg_const_type* const_blk, err_dynamic_msg_cb callback, const uint32 cb_param) ERR_NORETURN_ATTRIBUTE;

#ifdef FEATURE_GENERIC_ERR_FATAL_MSG
  #define ERR_FATAL_DYNAMIC_MSG(legacy_msg, callback, args)                              \
    do                                                                             \
    {                                                                              \
        _XX_MSG_CONST( MSG_SSID_DFLT, MSG_LEGACY_FATAL, err_generic_msg_dynamic ); \
        err_SaveFatal_dynamic (&xx_msg_const, callback, args);                           \
    /*lint -save -e{717} */                                                        \
    } while (0)                                                                    \
    /* lint -restore */

#else /* !FEATURE_GENERIC_ERR_FATAL_MSG */
  #define ERR_FATAL_DYNAMIC_MSG(legacy_msg, callback, args)                              \
    do                                                                             \
    {                                                                              \
        _XX_MSG_CONST( MSG_SSID_DFLT, MSG_LEGACY_FATAL, legacy_msg );              \
        err_SaveFatal_dynamic (&xx_msg_const, callback, args);                           \
    /*lint -save -e{717} */                                                        \
    } while (0)                                                                    \
    /* lint -restore */
#endif /* FEATURE_GENERIC_ERR_FATAL_MSG */

#endif /* from #ifdef FEATURE_EXTERNAL_ERR_FATAL #elif tree */

/*===========================================================================

FUNCTION err_exception_handler
DESCRIPTION
  Expose exception handler entry point for use by main(); no other use
  case is supported. Context running main() blocks permanently at the
  exception handler on REX API targets once kernel initialization of
  rex_init() is completed.
============================================================================*/
void err_exception_handler(void) ERR_NORETURN_ATTRIBUTE; // exposed for main()

#ifdef __cplusplus
}
#endif

//deprecated -- used by diag
//#define err_set_auto_action(X) while(0){}

#endif /* ERR_H */
