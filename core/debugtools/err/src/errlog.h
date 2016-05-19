#ifndef ERRLOG_H
#define ERRLOG_H
/*===========================================================================

                   L O G  P A C K E T S  F O R  E R R

DESCRIPTION
  This header file contains the definitions of log structure for core dump
 
Copyright (c) 2007,2009    by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/errlog.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/25/07   tbg     Initial revision (pulled code from rexlog.h)

===========================================================================*/


/* -----------------------------------------------------------------------
** Includes 
** ----------------------------------------------------------------------- */
#include "customer.h"
#include "comdef.h"

/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */

typedef enum
{
  ERR_ARCH_UNKNOWN = 0,
  ERR_ARCH_ARM,
  ERR_ARCH_QDSP6,
  SIZEOF_ERR_ARCH_TYPE
} err_arch_type;

typedef enum
{
  ERR_OS_UNKNOWN = 0,
  ERR_OS_REX,
  ERR_OS_L4, 
  ERR_OS_BLAST, 
  ERR_OS_QURT, 
  SIZEOF_ERR_OS_TYPE
} err_os_type;


/************************************************************************
 *                        ARCH_COREDUMP_TYPES
 ************************************************************************/

/****************
 *    QDSP6
 ****************/

typedef enum
{
  QDSP6_GP_R0 = 0,
  QDSP6_GP_R1,
  QDSP6_GP_R2,
  QDSP6_GP_R3,
  QDSP6_GP_R4,
  QDSP6_GP_R5,
  QDSP6_GP_R6,
  QDSP6_GP_R7,
  QDSP6_GP_R8,
  QDSP6_GP_R9,
  QDSP6_GP_R10,
  QDSP6_GP_R11,
  QDSP6_GP_R12,
  QDSP6_GP_R13,
  QDSP6_GP_R14,
  QDSP6_GP_R15,
  QDSP6_GP_R16,
  QDSP6_GP_R17,
  QDSP6_GP_R18,
  QDSP6_GP_R19,
  QDSP6_GP_R20,
  QDSP6_GP_R21,
  QDSP6_GP_R22,
  QDSP6_GP_R23,
  QDSP6_GP_R24,
  QDSP6_GP_R25,
  QDSP6_GP_R26,
  QDSP6_GP_R27,
  QDSP6_GP_R28,
  QDSP6_SP,
  QDSP6_FP,
  QDSP6_LR,
  QDSP6_PC,
  QDSP6_USR,
  QDSP6_UGP,
  QDSP6_GP,
  QDSP6_LC0,
  QDSP6_LC1,
  QDSP6_SA0,
  QDSP6_SA1,
  QDSP6_M0,
  QDSP6_M1,
  QDSP6_P,
  QDSP6_SGP,
  QDSP6_SSR,
  QDSP6_IMASK,
  QDSP6_BADVA,
  QDSP6_ELR,
  QDSP6_TID,
  QDSP6_EVB,
  QDSP6_IPEND,
  QDSP6_SYSCFG,
  QDSP6_MODECTL,
  QDSP6_REV,
  QDSP6_TLBHI,
  QDSP6_TLBLO,
  QDSP6_TLBIDX,
  QDSP6_DIAG,
  QDSP6_IAD,
  QDSP6_IEL,
  QDSP6_IAHL,
  QDSP6_PCYCLEHI,
  QDSP6_PCYCLELO,
  SIZEOF_ARCH_COREDUMP_REGISTERS
} arch_coredump_register_type;


typedef struct
{
  uint32 regs[SIZEOF_ARCH_COREDUMP_REGISTERS];
} arch_coredump_array_type;

typedef struct
{
  uint32 gp_regs[29];
  uint32 sp;
  uint32 fp;
  uint32 lr;
  uint32 pc;
  uint32 usr;
  uint32 ugp;
  uint32 gp;
  uint32 lc0;
  uint32 lc1;
  uint32 sa0;
  uint32 sa1;
  uint32 m0;
  uint32 m1;
  uint32 p;
  uint32 sgp;
  uint32 ssr;
  uint32 imask;
  uint32 badva;
  uint32 elr;
  uint32 tid;
  uint32 evb;
  uint32 ipend;
  uint32 syscfg;
  uint32 modectl;
  uint32 rev;
  uint32 tlbhi;
  uint32 tlblo;
  uint32 tlbidx;
  uint32 diag;
  uint32 iad;
  uint32 iel;
  uint32 iahl;
  uint32 pcyclehi;
  uint32 pcyclelo;
} arch_coredump_field_type;

union arch_coredump_union
{
  uint32 array[SIZEOF_ARCH_COREDUMP_REGISTERS];
  arch_coredump_field_type name;
};

#define NUM_QDSP6_GP_REGS 32

typedef struct
{
  err_arch_type type;
  uint32 version;
  union arch_coredump_union regs;
} arch_coredump_type;

/* update this version whenever QDSP6 arch_coredump_type changes */
#define ERR_ARCH_COREDUMP_VER  1
#define ERR_ARCH_COREDUMP_TYPE ERR_ARCH_QDSP6
#define ERR_ARCH_QDSP_INUSE

/************************************************************************
 *                        OS_COREDUMP_TYPES
 ************************************************************************/

/****************
 *    QURT
 ****************/

#define ERR_OS_TCB_TYPE void

typedef struct
{
  err_os_type type;
  uint32 version;  
  ERR_OS_TCB_TYPE* tcb_ptr; 
} os_coredump_type;

/* update this version whenever L4 os_coredump_type changes */
#define ERR_OS_COREDUMP_VER  0xFF
#define ERR_OS_COREDUMP_TYPE ERR_OS_QURT
#define ERR_OS_QURT_INUSE



/************************************************************************
 *                         ERR_COREDUMP_TYPE
 ************************************************************************/

#define ERR_LOG_MAX_MSG_LEN 80
#define ERR_LOG_MAX_FILE_LEN 50 /* Q6 compiler includes relative path */
/* Needs to match number of msg parameters defined in ERR_FATAL macro */
#define ERR_LOG_NUM_PARAMS 3 

typedef struct
{
  uint32 version;
  uint32 linenum;
  uint64 timestamp;
  //time_type uptime;
  char   filename[ERR_LOG_MAX_FILE_LEN];
  char   message[ERR_LOG_MAX_MSG_LEN];
  uint32 param[ERR_LOG_NUM_PARAMS];
  char   aux_msg[ERR_LOG_MAX_MSG_LEN];
} err_coredump_type;

/* update this version whenever err_coredump_type changes */
#define ERR_COREDUMP_VER  3


/************************************************************************
 *                           COREDUMP_TYPE
 ************************************************************************/


typedef struct
{
  uint32 version;
  arch_coredump_type arch;
  os_coredump_type os;
  err_coredump_type err;
} coredump_type;

 /* update this version whenever coredump_type changes */
#define ERR_COREDUMP_VERSION  1
 
/*===========================================================================
FUNCTION ERR_LOG_INIT

DESCRIPTION
  Initialize buffer to be used for writing log information.
  Calling the function subsequent times will reset the location and size
  of the buffer.

PARAMETERS
  char *buff     Pointer to buffer
  uint32 size    Size of buffer

RETURNS
 
============================================================================*/
void err_log_init(char *buff, uint32 size);

/*===========================================================================
FUNCTION ERR_GENERATE_LOG

DESCRIPTION
  This is the function called by error services when a log report needs to
  be generated.

  err_log_init() must be called prior to calling this function.

PARAMETERS
  None

RETURNS 
  uint32          Number of bytes written to buffer.

============================================================================*/

uint32 err_generate_log(void);

/* DEPRECATED TYPE */
/* No longer used for debugging */
#if (defined(__ARMCC_VERSION) && (__ARMCC_VERSION > 200000)) || (defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)))
#define ERR_LOG_DEPRECATED __attribute__ ((deprecated))
#else
#define ERR_LOG_DEPRECATED
#endif


#endif /* ERRLOG_H */
