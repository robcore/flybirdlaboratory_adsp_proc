/*============================================================================

FILE:      DalHWIOLogMsg.c

DESCRIPTION:
  This file implements the HWIO access message logging portion of the
  HWIO DAL.

PUBLIC CLASSES:
  __inp_extern
  __inpw_extern
  __inpdw_extern
  __outp_extern
  __outpw_extern
  __outpdw_extern

============================================================================
        Copyright (c) 2009 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
============================================================================
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/hwio/src/DalHWIOLogMsg.c#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $
============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/


#include "comdef.h"
#include "msg.h"



/*=========================================================================
      Implementation
==========================================================================*/


/*==========================================================================

  FUNCTION      __inp_extern

  DESCRIPTION   See HALhwio.h

==========================================================================*/

uint8 __inp_extern
(
  uint32 nAddr
)
{
  MSG_HIGH("HWIO IN BYTE: 0x%08x", nAddr, 0, 0);

  return (*((volatile uint8 *)(nAddr)));

} /* END __inp_extern */


/*==========================================================================

  FUNCTION      __inpw_extern

  DESCRIPTION   See HALhwio.h

==========================================================================*/

uint16 __inpw_extern
(
  uint32 nAddr
)
{
  MSG_HIGH("HWIO IN WORD: 0x%08x", nAddr, 0, 0);

  return (*((volatile uint16 *)(nAddr)));

} /* END __inpw_extern */


/*==========================================================================

  FUNCTION      __inpdw_extern

  DESCRIPTION   See HALhwio.h

==========================================================================*/

uint32 __inpdw_extern
(
  uint32 nAddr
)
{
  MSG_HIGH("HWIO IN DWORD: 0x%08x", nAddr, 0, 0);

  return (*((volatile uint32 *)(nAddr)));

} /* END __inpdw_extern */


/*==========================================================================

  FUNCTION      __outp_extern

  DESCRIPTION   See HALhwio.h

==========================================================================*/

void __outp_extern
(
  uint32 nAddr,
  uint8  nData
)
{
  MSG_HIGH("HWIO OUT BYTE: 0x%08x = %d", nAddr, nData, 0);

  *((volatile uint8 *)(nAddr)) = nData;

} /* END __outp_extern */


/*==========================================================================

  FUNCTION      __outpw_extern

  DESCRIPTION   See HALhwio.h

==========================================================================*/

void __outpw_extern
(
  uint32 nAddr,
  uint16 nData
)
{
  MSG_HIGH("HWIO OUT WORD: 0x%08x = %d", nAddr, nData, 0);

  *((volatile uint16 *)(nAddr)) = nData;

} /* END __outpw_extern */


/*==========================================================================

  FUNCTION      __outpdw_extern

  DESCRIPTION   See HALhwio.h

==========================================================================*/

void __outpdw_extern
(
  uint32 nAddr,
  uint32 nData
)
{
  MSG_HIGH("HWIO OUT DWORD: 0x%08x = %d", nAddr, nData, 0);

  *((volatile uint32 *)(nAddr)) = nData;

} /* END __outpdw_extern */




