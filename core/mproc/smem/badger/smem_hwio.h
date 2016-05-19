#ifndef __SMEM_HWIO_H__
#define __SMEM_HWIO_H__
/*=========================================================================*/
/**
  @file smem_hwio.h
  @brief Semi-auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    TCSR_TCSR_MUTEX

  'Include' filters applied: MUTEX_REG*[TCSR_TCSR_MUTEX] 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*===========================================================================

  Copyright (c) 2012-2014 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

=============================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/mproc/smem/badger/smem_hwio.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/18/14   bm      Cleanup to make this file support only badger
06/07/12   rs      Updated from latest HWIO Gen
01/25/12   bt      Updated HWIO macro and base names as of Virtio v2.0.0. 
01/05/12   bt      Initial revision for 8974.
===========================================================================*/

#ifdef CORE_TOP_CSR_BASE
#undef CORE_TOP_CSR_BASE
#endif
extern uint8 *smem_hw_mutex_base_ptr;
#define CORE_TOP_CSR_BASE                           smem_hw_mutex_base_ptr
#define smem_hw_mutex_reg_base_phys                 CORE_TOP_CSR_BASE_PHYS
#define smem_hw_mutex_reg_base_size                 CORE_TOP_CSR_BASE_SIZE

/* Needed only for the DAL MapRegion function, on procs that use DAL. */
#define SMEM_HW_MUTEX_BASE_NAME ("CORE_TOP_CSR")

/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_MUTEX
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_MUTEX_REG_BASE                                            ( CORE_TOP_CSR_BASE      + 0x00004000 )
#define TCSR_TCSR_MUTEX_REG_BASE_PHYS                                       ( CORE_TOP_CSR_BASE_PHYS + 0x00004000 )
#define TCSR_TCSR_MUTEX_REG_BASE_SIZE                                       0x00005380

#define HWIO_TCSR_MUTEX_REG_n_ADDR(n)                                       ( TCSR_TCSR_MUTEX_REG_BASE      + 0x00000000 + 0x80 * (n) )
#define HWIO_TCSR_MUTEX_REG_n_RMSK                                                0xff
#define HWIO_TCSR_MUTEX_REG_n_MAXn                                                  31
#define HWIO_TCSR_MUTEX_REG_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_MUTEX_REG_n_ADDR(n), HWIO_TCSR_MUTEX_REG_n_RMSK)
#define HWIO_TCSR_MUTEX_REG_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_MUTEX_REG_n_ADDR(n), (mask))
#define HWIO_TCSR_MUTEX_REG_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_MUTEX_REG_n_ADDR(n),val)
#define HWIO_TCSR_MUTEX_REG_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_MUTEX_REG_n_ADDR(n),mask,val,HWIO_TCSR_MUTEX_REG_n_INI(n))
#define HWIO_TCSR_MUTEX_REG_n_MUTEX_BMSK                                          0xff
#define HWIO_TCSR_MUTEX_REG_n_MUTEX_SHFT                                           0x0

#endif /* __SMEM_HWIO_H__ */
