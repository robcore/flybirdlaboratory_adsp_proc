/*============================================================================

FILE:      DalChipInfoLocal.c

DESCRIPTION:
  This file implements the portion of the ChipInfo DAL that reads information
  from the hardware.

PUBLIC CLASSES:
  ChipInfo_DriverInit
  ChipInfo_DriverDeInit

============================================================================
        Copyright (c) 2010 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
============================================================================
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/chipinfo/src/DalChipInfoLocal.c#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $
 
when       who     what, where, why
--------   ---     --------------------------------------------------------
07/11/11   pbi     Fixed warnings.
============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "DALDeviceId.h"
#include "DalChipInfo.h"
#include "DDIHWIO.h"
#include <stringl/stringl.h>


/*=========================================================================
      Type Definitions
==========================================================================*/


/*
 * DalChipInfoDataLUTType
 *
 * Static per-chip data definitions.
 *
 * szChipId:  String representing the MSM name.
 * nFamily:   Chip Family enum.
 * nModem:    Bitmask of supported modems on this MSM.
 */
typedef struct
{
  const char          *szChipId;
  DalChipInfoFamilyType nFamily;
  DalChipInfoModemType nModem;
} DalChipInfoDataLUTType;


/*
 * Define some modem combination shortcuts.
 */
#define DALCHIPINFO_MODEM_1XEVDO       (DALCHIPINFO_MODEM_1X | DALCHIPINFO_MODEM_EVDO)
#define DALCHIPINFO_MODEM_1XEVDO_REVA  (DALCHIPINFO_MODEM_1XEVDO | DALCHIPINFO_MODEM_EVDO_REVA)
#define DALCHIPINFO_MODEM_1XEVDO_REVB  (DALCHIPINFO_MODEM_1XEVDO_REVA | DALCHIPINFO_MODEM_EVDO_REVB)
#define DALCHIPINFO_MODEM_WWAN         (DALCHIPINFO_MODEM_1XEVDO_REVB | DALCHIPINFO_MODEM_GSM | DALCHIPINFO_MODEM_UMTS)


/*=========================================================================
      Data Definitions
==========================================================================*/

/*
 * DALCHIPINFO_MFGNUM_*
 *
 * Manufacturer IDs
 */
#define DALCHIPINFO_MFGNUM_QUALCOMM 0x170

/*
 * DALCHIPINFO_PARTNUM_*
 *
 * Definitions of part number fields.
 */

#define DALCHIPINFO_PARTNUM_MSM8974        0x7B0
#define DALCHIPINFO_PARTNUM_MSM8674        0x7B1
#define DALCHIPINFO_PARTNUM_MSM8274        0x7B2
#define DALCHIPINFO_PARTNUM_APQ8074        0x7B3

#define DALCHIPINFO_PARTNUM_MSM8974_PRO    0x7B4
#define DALCHIPINFO_PARTNUM_APQ8074_AA	   0x7BF	
#define DALCHIPINFO_PARTNUM_APQ8074_AB	   0x7BB	
#define DALCHIPINFO_PARTNUM_APQ8074_PRO	   0x7B7	
#define DALCHIPINFO_PARTNUM_MSM8274_AA	   0x7BE	
#define DALCHIPINFO_PARTNUM_MSM8274_AB	   0x7BA	
#define DALCHIPINFO_PARTNUM_MSM8274_PRO	   0x7B6	
#define DALCHIPINFO_PARTNUM_MSM8674_AA	   0x7BD	
#define DALCHIPINFO_PARTNUM_MSM8674_AB	   0x7B9	
#define DALCHIPINFO_PARTNUM_MSM8674_PRO	   0x7B5	
#define DALCHIPINFO_PARTNUM_MSM8974_AA	   0x7BC	
#define DALCHIPINFO_PARTNUM_MSM8974_AB	   0x7B8

#define DALCHIPINFO_PARTNUM_MDM8225        0x7F0
#define DALCHIPINFO_PARTNUM_MDM9225        0x7F1
#define DALCHIPINFO_PARTNUM_MDM9225M       0x7F2
#define DALCHIPINFO_PARTNUM_MDM8225M       0x7F3
#define DALCHIPINFO_PARTNUM_MDM9625        0x7F4
#define DALCHIPINFO_PARTNUM_MDM9625M       0x7F5
#define DALCHIPINFO_PARTNUM_MDM9320        0x7F7
#define DALCHIPINFO_PARTNUM_MDM9225_1      0x7F1
#define DALCHIPINFO_PARTNUM_MDM9225M_1     0x7F2

#define DALCHIPINFO_PARTNUM_MSM8226        0x800
#define DALCHIPINFO_PARTNUM_MSM8626        0x801
#define DALCHIPINFO_PARTNUM_MSM8526        0x802
#define DALCHIPINFO_PARTNUM_MSM8126        0x803
#define DALCHIPINFO_PARTNUM_APQ8026        0x804
#define DALCHIPINFO_PARTNUM_APQ8028        0x913
#define DALCHIPINFO_PARTNUM_MSM8128        0x914
#define DALCHIPINFO_PARTNUM_MSM8228        0x915
#define DALCHIPINFO_PARTNUM_MSM8528        0x916
#define DALCHIPINFO_PARTNUM_MSM8628        0x917

#define DALCHIPINFO_PARTNUM_MSM8110        0x810
#define DALCHIPINFO_PARTNUM_MSM8210        0x811
#define DALCHIPINFO_PARTNUM_MSM8610        0x812
#define DALCHIPINFO_PARTNUM_MSM8810        0x813
#define DALCHIPINFO_PARTNUM_MSM8212        0x814
#define DALCHIPINFO_PARTNUM_MSM8612        0x815
#define DALCHIPINFO_PARTNUM_MSM8112        0x816
#define DALCHIPINFO_PARTNUM_MSM8510        0x817
#define DALCHIPINFO_PARTNUM_MSM8512        0x818

#define DALCHIPINFO_PARTNUM_APQ8084_0      0x900
#define DALCHIPINFO_PARTNUM_APQ8084_1      0x901

#define DALCHIPINFO_PARTNUM_FSM9900        0x80F
#define DALCHIPINFO_PARTNUM_FSM9965        0x80A
#define DALCHIPINFO_PARTNUM_FSM9955        0x80B
#define DALCHIPINFO_PARTNUM_FSM9950        0x80C
#define DALCHIPINFO_PARTNUM_FSM9915        0x80D
#define DALCHIPINFO_PARTNUM_FSM9910        0x80E

#define DALCHIPINFO_PARTNUM_MDM9630        0x920
#define DALCHIPINFO_PARTNUM_MDM9635M       0x921
#define DALCHIPINFO_PARTNUM_MDM9230        0x922
#define DALCHIPINFO_PARTNUM_MDM9235M       0x923
#define DALCHIPINFO_PARTNUM_MDM8630        0x924
#define DALCHIPINFO_PARTNUM_MDM9330        0x925

#define DALCHIPINFO_PARTNUM_MSM8962        0x910
#define DALCHIPINFO_PARTNUM_MSM8262        0x911
#define DALCHIPINFO_PARTNUM_APQ8062        0x912

#define DALCHIPINFO_PARTNUM_MSM8926        0x805
#define DALCHIPINFO_PARTNUM_MSM8326        0x806
#define DALCHIPINFO_PARTNUM_MSM8928        0x918

#define DALCHIPINFO_PARTNUM_MSM8916        0x705

#define DALCHIPINFO_PARTNUM_MSM8994        0x940
#define DALCHIPINFO_PARTNUM_APQ8094        0x941

#define DALCHIPINFO_PARTNUM_MPQ8092        0x930
#define DALCHIPINFO_PARTNUM_MPQ8091        0x931

#define DALCHIPINFO_PARTNUM_MSM8996        0x947

#define DALCHIPINFO_PARTNUM_MSM8992        0x964
#define DALCHIPINFO_PARTNUM_APQ8092        0x963


/*
 * amPartMap
 *
 * Map of part numbers to logical parts.
 */
DalChipInfoPartMapType amPartMap[] =
{
  { DALCHIPINFO_PARTNUM_MSM8974,    DALCHIPINFO_ID_MSM8974   },
  { DALCHIPINFO_PARTNUM_MDM8225,    DALCHIPINFO_ID_MDM8225   },
  { DALCHIPINFO_PARTNUM_MDM9225,    DALCHIPINFO_ID_MDM9225   },
  { DALCHIPINFO_PARTNUM_MDM9225M,   DALCHIPINFO_ID_MDM9225M  },
  { DALCHIPINFO_PARTNUM_MDM8225M,   DALCHIPINFO_ID_MDM8225M  },
  { DALCHIPINFO_PARTNUM_MDM9625,    DALCHIPINFO_ID_MDM9625   },
  { DALCHIPINFO_PARTNUM_MDM9625M,   DALCHIPINFO_ID_MDM9625M  },
  { DALCHIPINFO_PARTNUM_MSM8226,    DALCHIPINFO_ID_MSM8226   },
  { DALCHIPINFO_PARTNUM_MSM8626,    DALCHIPINFO_ID_MSM8626   },
  { DALCHIPINFO_PARTNUM_MSM8526,    DALCHIPINFO_ID_MSM8526   },
  { DALCHIPINFO_PARTNUM_MSM8110,    DALCHIPINFO_ID_MSM8110   },
  { DALCHIPINFO_PARTNUM_MSM8210,    DALCHIPINFO_ID_MSM8210   },
  { DALCHIPINFO_PARTNUM_MSM8610,    DALCHIPINFO_ID_MSM8610   },
  { DALCHIPINFO_PARTNUM_MSM8810,    DALCHIPINFO_ID_MSM8810   },
  { DALCHIPINFO_PARTNUM_MSM8212,    DALCHIPINFO_ID_MSM8212   },
  { DALCHIPINFO_PARTNUM_MSM8612,    DALCHIPINFO_ID_MSM8612   },
  { DALCHIPINFO_PARTNUM_MSM8112,    DALCHIPINFO_ID_MSM8112   },
  { DALCHIPINFO_PARTNUM_MDM9320,    DALCHIPINFO_ID_MDM9320   },
  { DALCHIPINFO_PARTNUM_MDM9225_1,  DALCHIPINFO_ID_MDM9225_1 },
  { DALCHIPINFO_PARTNUM_MDM9225M_1, DALCHIPINFO_ID_MDM9225M_1},
  { DALCHIPINFO_PARTNUM_MSM8674,    DALCHIPINFO_ID_MSM8674   },
  { DALCHIPINFO_PARTNUM_MSM8274,    DALCHIPINFO_ID_MSM8274   },
  { DALCHIPINFO_PARTNUM_APQ8074,    DALCHIPINFO_ID_APQ8074   },
  { DALCHIPINFO_PARTNUM_APQ8084_0,  DALCHIPINFO_ID_APQ8084   },
  { DALCHIPINFO_PARTNUM_APQ8084_1,  DALCHIPINFO_ID_APQ8084   },
  { DALCHIPINFO_PARTNUM_MDM9630,    DALCHIPINFO_ID_MDM9630   },
  { DALCHIPINFO_PARTNUM_MDM9635M,   DALCHIPINFO_ID_MDM9635M  },
  { DALCHIPINFO_PARTNUM_MDM9230,    DALCHIPINFO_ID_MDM9230   },
  { DALCHIPINFO_PARTNUM_MDM9235M,   DALCHIPINFO_ID_MDM9235M  },
  { DALCHIPINFO_PARTNUM_MDM8630,    DALCHIPINFO_ID_MDM8630   },
  { DALCHIPINFO_PARTNUM_MDM9330,    DALCHIPINFO_ID_MDM9330   },
  { DALCHIPINFO_PARTNUM_FSM9900,    DALCHIPINFO_ID_FSM9900   },
  { DALCHIPINFO_PARTNUM_FSM9965,    DALCHIPINFO_ID_FSM9965   },
  { DALCHIPINFO_PARTNUM_FSM9955,    DALCHIPINFO_ID_FSM9955   },
  { DALCHIPINFO_PARTNUM_FSM9950,    DALCHIPINFO_ID_FSM9950   },
  { DALCHIPINFO_PARTNUM_FSM9915,    DALCHIPINFO_ID_FSM9915   },
  { DALCHIPINFO_PARTNUM_FSM9910,    DALCHIPINFO_ID_FSM9910   },
  { DALCHIPINFO_PARTNUM_MSM8974_PRO,DALCHIPINFO_ID_MSM8974_PRO   },
  { DALCHIPINFO_PARTNUM_MSM8126,    DALCHIPINFO_ID_MSM8126   },
  { DALCHIPINFO_PARTNUM_APQ8026,    DALCHIPINFO_ID_APQ8026   },
  { DALCHIPINFO_PARTNUM_MSM8926,    DALCHIPINFO_ID_MSM8926   },
  { DALCHIPINFO_PARTNUM_MSM8962,    DALCHIPINFO_ID_MSM8962   },
  { DALCHIPINFO_PARTNUM_MSM8262,    DALCHIPINFO_ID_MSM8262   },
  { DALCHIPINFO_PARTNUM_APQ8062,    DALCHIPINFO_ID_APQ8062   },
  { DALCHIPINFO_PARTNUM_MSM8326,    DALCHIPINFO_ID_MSM8326   },
  { DALCHIPINFO_PARTNUM_MSM8916,    DALCHIPINFO_ID_MSM8916   },
  { DALCHIPINFO_PARTNUM_MSM8994,    DALCHIPINFO_ID_MSM8994   },
  { DALCHIPINFO_PARTNUM_APQ8074_AA, DALCHIPINFO_ID_APQ8074_AA  },
  { DALCHIPINFO_PARTNUM_APQ8074_AB, DALCHIPINFO_ID_APQ8074_AB  },
  { DALCHIPINFO_PARTNUM_APQ8074_PRO,DALCHIPINFO_ID_APQ8074_PRO },
  { DALCHIPINFO_PARTNUM_MSM8274_AA, DALCHIPINFO_ID_MSM8274_AA  },
  { DALCHIPINFO_PARTNUM_MSM8274_AB, DALCHIPINFO_ID_MSM8274_AB  },
  { DALCHIPINFO_PARTNUM_MSM8274_PRO,DALCHIPINFO_ID_MSM8274_PRO },
  { DALCHIPINFO_PARTNUM_MSM8674_AA, DALCHIPINFO_ID_MSM8674_AA  },
  { DALCHIPINFO_PARTNUM_MSM8674_AB, DALCHIPINFO_ID_MSM8674_AB  },
  { DALCHIPINFO_PARTNUM_MSM8674_PRO,DALCHIPINFO_ID_MSM8674_PRO },
  { DALCHIPINFO_PARTNUM_MSM8974_AA, DALCHIPINFO_ID_MSM8974_AA  },
  { DALCHIPINFO_PARTNUM_MSM8974_AB, DALCHIPINFO_ID_MSM8974_AB  },
  { DALCHIPINFO_PARTNUM_APQ8028,    DALCHIPINFO_ID_APQ8028   },
  { DALCHIPINFO_PARTNUM_MSM8128,    DALCHIPINFO_ID_MSM8128   },
  { DALCHIPINFO_PARTNUM_MSM8228,    DALCHIPINFO_ID_MSM8228   },
  { DALCHIPINFO_PARTNUM_MSM8528,    DALCHIPINFO_ID_MSM8528   },
  { DALCHIPINFO_PARTNUM_MSM8628,    DALCHIPINFO_ID_MSM8628   },
  { DALCHIPINFO_PARTNUM_MSM8928,    DALCHIPINFO_ID_MSM8928   },
  { DALCHIPINFO_PARTNUM_MSM8510,    DALCHIPINFO_ID_MSM8510   },
  { DALCHIPINFO_PARTNUM_MSM8512,    DALCHIPINFO_ID_MSM8512   },
  { DALCHIPINFO_PARTNUM_MPQ8092,    DALCHIPINFO_ID_MPQ8092   },
  { DALCHIPINFO_PARTNUM_MPQ8091,    DALCHIPINFO_ID_MPQ8091   },
  { DALCHIPINFO_PARTNUM_MSM8996,    DALCHIPINFO_ID_MSM8996   },
  { DALCHIPINFO_PARTNUM_APQ8094,    DALCHIPINFO_ID_APQ8094   },
  { DALCHIPINFO_PARTNUM_MSM8992,    DALCHIPINFO_ID_MSM8992   },
  { DALCHIPINFO_PARTNUM_APQ8092,    DALCHIPINFO_ID_APQ8092   },  

};

/*
 * chipIdMap
 *
 * Map of logical parts to DalChipInfoDataLUT indexes.
 */
DalChipInfoIdMapType chipIdMap[] =
{
  { DALCHIPINFO_ID_UNKNOWN,  0   },
  { DALCHIPINFO_ID_MSM8974,  1   },
  { DALCHIPINFO_ID_MDM8225,  2   },
  { DALCHIPINFO_ID_MDM9225,  3   },
  { DALCHIPINFO_ID_MDM9225M, 4   },
  { DALCHIPINFO_ID_MDM8225M, 5   },
  { DALCHIPINFO_ID_MDM9625,  6   },
  { DALCHIPINFO_ID_MDM9625M, 7   },
  { DALCHIPINFO_ID_MSM8226,  8   },
  { DALCHIPINFO_ID_MSM8626,  9   },
  { DALCHIPINFO_ID_MSM8526,  10   },
  { DALCHIPINFO_ID_MPQ8092,  11   },
  { DALCHIPINFO_ID_MSM8610,  12   },
  { DALCHIPINFO_ID_MSM8110,  13   },
  { DALCHIPINFO_ID_MSM8210,  14   },
  { DALCHIPINFO_ID_MSM8810,  15   },
  { DALCHIPINFO_ID_MSM8212,  16   },
  { DALCHIPINFO_ID_MSM8612,  17   },
  { DALCHIPINFO_ID_MSM8112,  18   },
  { DALCHIPINFO_ID_MDM9320,  19   },
  { DALCHIPINFO_ID_MDM9225_1,20   },
  { DALCHIPINFO_ID_MDM9225M_1,21  },
  { DALCHIPINFO_ID_MSM8674,   22  },
  { DALCHIPINFO_ID_MSM8274,   23  },
  { DALCHIPINFO_ID_APQ8074,   24  },
  { DALCHIPINFO_ID_APQ8084,   25  },
  { DALCHIPINFO_ID_MDM9635,   26  },
  { DALCHIPINFO_ID_FSM9900,   27  },
  { DALCHIPINFO_ID_FSM9965,   28  },
  { DALCHIPINFO_ID_FSM9955,   29  },
  { DALCHIPINFO_ID_FSM9950,   30  },
  { DALCHIPINFO_ID_FSM9915,   31  },
  { DALCHIPINFO_ID_FSM9910,   32  },
  { DALCHIPINFO_ID_MSM8974_PRO, 33  },
  { DALCHIPINFO_ID_MSM8126,   34  },
  { DALCHIPINFO_ID_APQ8026,   35  },
  { DALCHIPINFO_ID_MSM8926,   36  },
  { DALCHIPINFO_ID_MSM8962,   37  },
  { DALCHIPINFO_ID_MSM8262,   38  },
  { DALCHIPINFO_ID_APQ8062,   39  },
  { DALCHIPINFO_ID_MSM8326,   40  },
  { DALCHIPINFO_ID_MSM8916,   41  },
  { DALCHIPINFO_ID_MSM8994,   42  },
  { DALCHIPINFO_ID_APQ8074_AA, 43  },
  { DALCHIPINFO_ID_APQ8074_AB, 44  },
  { DALCHIPINFO_ID_APQ8074_PRO,45  },
  { DALCHIPINFO_ID_MSM8274_AA, 46  },
  { DALCHIPINFO_ID_MSM8274_AB, 47  },
  { DALCHIPINFO_ID_MSM8274_PRO,48  },
  { DALCHIPINFO_ID_MSM8674_AA, 49  },
  { DALCHIPINFO_ID_MSM8674_AB, 50  },
  { DALCHIPINFO_ID_MSM8674_PRO,51  },
  { DALCHIPINFO_ID_MSM8974_AA, 52  },
  { DALCHIPINFO_ID_MSM8974_AB, 53  },
  { DALCHIPINFO_ID_APQ8028, 54  },
  { DALCHIPINFO_ID_MSM8128, 55  },
  { DALCHIPINFO_ID_MSM8228, 56  },
  { DALCHIPINFO_ID_MSM8528, 57  },
  { DALCHIPINFO_ID_MSM8628, 58  },
  { DALCHIPINFO_ID_MSM8928, 59  },
  { DALCHIPINFO_ID_MSM8510, 60  },
  { DALCHIPINFO_ID_MSM8512, 61  },
  { DALCHIPINFO_ID_MDM9630, 62  },
  { DALCHIPINFO_ID_MDM9230, 63  },
  { DALCHIPINFO_ID_MDM9235M, 64  },
  { DALCHIPINFO_ID_MDM8630, 65  },
  { DALCHIPINFO_ID_MDM9330, 66  },
  { DALCHIPINFO_ID_MPQ8091, 67  },
  { DALCHIPINFO_ID_MSM8996, 68  },
  { DALCHIPINFO_ID_APQ8094, 69  },
  { DALCHIPINFO_ID_MSM8992, 70  },
  { DALCHIPINFO_ID_APQ8092, 71  },
};

#define DALCHIPINFO_ID_MAP_SIZE (sizeof(amPartMap) / sizeof(amPartMap[0]))
#define DALCHIPINFO_CHIPID_MAP_SIZE (sizeof(chipIdMap) / sizeof(chipIdMap[0]))
/*
 * DalChipInfoDataLUT
 *
 * Array of chip id strings, families and modem support indexed by MSM ID.
 */
static const DalChipInfoDataLUTType DalChipInfoDataLUT[DALCHIPINFO_CHIPID_MAP_SIZE] =
{
  { "UNKNOWN",     DALCHIPINFO_FAMILY_UNKNOWN,  0 },
  { "MSM8974",     DALCHIPINFO_FAMILY_MSM8974,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM8225",     DALCHIPINFO_FAMILY_MDM9x25,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9225",     DALCHIPINFO_FAMILY_MDM9x25,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9225M",    DALCHIPINFO_FAMILY_MDM9x25,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM8225M",    DALCHIPINFO_FAMILY_MDM9x25,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9625",     DALCHIPINFO_FAMILY_MDM9x25,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9625M",    DALCHIPINFO_FAMILY_MDM9x25,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8226",     DALCHIPINFO_FAMILY_MSM8x26,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8626",     DALCHIPINFO_FAMILY_MSM8x26,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8526",     DALCHIPINFO_FAMILY_MSM8x26,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MPQ8092",     DALCHIPINFO_FAMILY_MPQ8092,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8610",     DALCHIPINFO_FAMILY_MSM8x10,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8110",     DALCHIPINFO_FAMILY_MSM8x10,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8210",     DALCHIPINFO_FAMILY_MSM8x10,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8810",     DALCHIPINFO_FAMILY_MSM8x10,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8212",     DALCHIPINFO_FAMILY_MSM8x10,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8612",     DALCHIPINFO_FAMILY_MSM8x10,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8112",     DALCHIPINFO_FAMILY_MSM8x10,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9320",     DALCHIPINFO_FAMILY_MDM9x25,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9225_1",   DALCHIPINFO_FAMILY_MDM9x25,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9225M_1",  DALCHIPINFO_FAMILY_MDM9x25,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8674",     DALCHIPINFO_FAMILY_MSM8974,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8274",     DALCHIPINFO_FAMILY_MSM8974,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "APQ8074",     DALCHIPINFO_FAMILY_MSM8974,  0 },
  { "APQ8084",     DALCHIPINFO_FAMILY_APQ8x94,  0 },
  { "MDM9635M",    DALCHIPINFO_FAMILY_MDM9x35,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "FSM9900",     DALCHIPINFO_FAMILY_FSM9900,  0 },
  { "FSM9965",     DALCHIPINFO_FAMILY_FSM9900,  0 },
  { "FSM9955",     DALCHIPINFO_FAMILY_FSM9900,  0 },
  { "FSM9950",     DALCHIPINFO_FAMILY_FSM9900,  0 },
  { "FSM9915",     DALCHIPINFO_FAMILY_FSM9900,  0 },
  { "FSM9910",     DALCHIPINFO_FAMILY_FSM9900,  0 },
  { "MSM8974PRO",  DALCHIPINFO_FAMILY_MSM8974_PRO,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8126",     DALCHIPINFO_FAMILY_MSM8x26,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "APQ8026",     DALCHIPINFO_FAMILY_MSM8x26,  0 },
  { "MSM8926",     DALCHIPINFO_FAMILY_MSM8926,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8962",     DALCHIPINFO_FAMILY_MSM8x62,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8262",     DALCHIPINFO_FAMILY_MSM8x62,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "APQ8062",     DALCHIPINFO_FAMILY_MSM8x62,  0 },
  { "MSM8326",     DALCHIPINFO_FAMILY_MSM8926,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8916",     DALCHIPINFO_FAMILY_MSM8916,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8994",     DALCHIPINFO_FAMILY_MSM8994,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "APQ8074_AA",  DALCHIPINFO_FAMILY_MSM8974_PRO,  0 },
  { "APQ8074_AB",  DALCHIPINFO_FAMILY_MSM8974_PRO,  0 },
  { "APQ8074_PRO", DALCHIPINFO_FAMILY_MSM8974_PRO,  0 },
  { "MSM8274_AA",  DALCHIPINFO_FAMILY_MSM8974_PRO,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8274_AB",  DALCHIPINFO_FAMILY_MSM8974_PRO,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8274_PRO", DALCHIPINFO_FAMILY_MSM8974_PRO,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8674_AA",  DALCHIPINFO_FAMILY_MSM8974_PRO,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8674_AB",  DALCHIPINFO_FAMILY_MSM8974_PRO,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8674_PRO", DALCHIPINFO_FAMILY_MSM8974_PRO,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8974_AA",  DALCHIPINFO_FAMILY_MSM8974_PRO,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8974_AB",  DALCHIPINFO_FAMILY_MSM8974_PRO,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "APQ8028",     DALCHIPINFO_FAMILY_MSM8x26,  0 },
  { "MSM8128",     DALCHIPINFO_FAMILY_MSM8x26,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8228",     DALCHIPINFO_FAMILY_MSM8x26,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8528",     DALCHIPINFO_FAMILY_MSM8x26,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8628",     DALCHIPINFO_FAMILY_MSM8x26,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8928",     DALCHIPINFO_FAMILY_MSM8926,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8510",     DALCHIPINFO_FAMILY_MSM8x10,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS },
  { "MSM8512",     DALCHIPINFO_FAMILY_MSM8x10,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS },
  { "MDM9630",     DALCHIPINFO_FAMILY_MDM9x35,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9230",     DALCHIPINFO_FAMILY_MDM9x35,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9235M",    DALCHIPINFO_FAMILY_MDM9x35,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM8630",     DALCHIPINFO_FAMILY_MDM9x35,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9330",     DALCHIPINFO_FAMILY_MDM9x35,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MPQ8091",     DALCHIPINFO_FAMILY_MPQ8092,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8996",     DALCHIPINFO_FAMILY_MSM8996,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "APQ8094",     DALCHIPINFO_FAMILY_MSM8994,  0 }, 
  { "MSM8992",     DALCHIPINFO_FAMILY_MSM8992,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS },
  { "APQ8092",     DALCHIPINFO_FAMILY_MSM8992,  0 },  
};

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

/* ===========================================================================
**  ChipInfo_GetFamily
**
** ======================================================================== */

void ChipInfo_GetFamily
(
  ChipInfoDrvCtxt       *pCtxt,
  DalChipInfoFamilyType *peFamily,
  uint32                nHWRevNum
)
{
  DalChipInfoIdType ePart;
  uint32             nPart=0,n;

  /*
   * Read part number from hardware.
   */
  ChipInfo_GetPart(pCtxt, &ePart, nHWRevNum);

  /*
   * Look up family.
   */
  if (ePart < DALCHIPINFO_NUM_IDS)
  {
    /*
     * Look up using the table.
     */
    for (n = 0; n < DALCHIPINFO_CHIPID_MAP_SIZE; n++)
    {
      if (ePart == chipIdMap[n].ePart)
      {
        nPart = chipIdMap[n].nPart;
        break;
      }
    }
  
    if (n == DALCHIPINFO_CHIPID_MAP_SIZE)
    {
      nPart = 0;
    }
    *peFamily = DalChipInfoDataLUT[nPart].nFamily;
  }
  else
  {
    *peFamily = DALCHIPINFO_FAMILY_UNKNOWN;
  }

} /* END ChipInfo_GetFamily */


/* ===========================================================================
**  ChipInfo_GetFamilyByPart
**
** ======================================================================== */

void ChipInfo_GetFamilyByPart
(
  DalChipInfoIdType    ePart,
  DalChipInfoFamilyType *peFamily
)
{
  uint32             nPart=0,n;

  /*
   * Look up family.
   */
  if (ePart < DALCHIPINFO_NUM_IDS)
  {
    /*
     * Look up using the table.
     */
    for (n = 0; n < DALCHIPINFO_CHIPID_MAP_SIZE; n++)
    {
      if (ePart == chipIdMap[n].ePart)
      {
        nPart = chipIdMap[n].nPart;
        break;
      }
    }
  
    if (n == DALCHIPINFO_CHIPID_MAP_SIZE)
    {
      nPart = 0;
    }
    *peFamily = DalChipInfoDataLUT[nPart].nFamily;
  }
  else
  {
    *peFamily = DALCHIPINFO_FAMILY_UNKNOWN;
  }

} /* END ChipInfo_GetFamilyByPart */


/* ===========================================================================
**  ChipInfo_GetPart
**
** ======================================================================== */

void ChipInfo_GetPart
(
  ChipInfoDrvCtxt     *pCtxt,
  DalChipInfoIdType   *pePart,
  uint32              nHWRevNum
)
{
  uint32 nPart, n;

  /*
   * Read the part number.
   */
  ChipInfo_GetRawPart(pCtxt, &nPart, nHWRevNum);

  /*
   * Look up using the table.
   */
  for (n = 0; n < DALCHIPINFO_ID_MAP_SIZE; n++)
  {
    if (nPart == amPartMap[n].nPart)
    {
      *pePart = amPartMap[n].ePart;
      break;
    }
  }

  if (n == DALCHIPINFO_ID_MAP_SIZE)
  {
    *pePart = DALCHIPINFO_ID_UNKNOWN;
  }

} /* END ChipInfo_GetPart */


/* ===========================================================================
**  ChipInfo_GetVersion
**
** ======================================================================== */

void ChipInfo_GetVersion
(
  ChipInfoDrvCtxt        *pCtxt,
  DalChipInfoVersionType *pnVersion,
  uint32                 nSOCHWVersion
)
{
  uint32 majNumBmsk, majNumShft, minNumBmsk, minNumShft, majorNum;
  DALSYSPropertyVar PropVar;

 
  DALSYS_GetPropertyValue(pCtxt->hProps,"MAJOR_VERSION_BMSK",0,&PropVar);
  majNumBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"MAJOR_VERSION_SHFT",0,&PropVar);
  majNumShft = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"MINOR_VERSION_BMSK",0,&PropVar);
  minNumBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"MINOR_VERSION_SHFT",0,&PropVar);
  minNumShft = PropVar.Val.dwVal;

  /* If MAJOR VERSION is 0x0 we treat it as 0x1 to provide correct versioninfo on Dino*/
  majorNum = (nSOCHWVersion & majNumBmsk) >> majNumShft;
  if( majorNum == 0x0)
  {
    majorNum = 0x1;
  }
  *pnVersion = DALCHIPINFO_VERSION(
     (majorNum),
      ((nSOCHWVersion & minNumBmsk) >> minNumShft));

} /* END ChipInfo_GetVersion */


/* ===========================================================================
**  ChipInfo_GetManufacturer
**
** ======================================================================== */

void ChipInfo_GetManufacturer
(
  ChipInfoDrvCtxt             *pCtxt,
  DalChipInfoManufacturerType *peManufacturer,
  uint32                      nHWRevNum
)
{
  uint32 pnRawManufacturer;

  ChipInfo_GetRawManufacturer(pCtxt, &pnRawManufacturer, nHWRevNum);
  switch(pnRawManufacturer)
    {
    case DALCHIPINFO_MFGNUM_QUALCOMM:
    {
      *peManufacturer = DALCHIPINFO_MFG_QUALCOMM;
      break;
    }

    default:
    {
      *peManufacturer = DALCHIPINFO_MFG_UNKNOWN;
      break;
    }
  }

} /* END ChipInfo_GetManufacturer */


/* ===========================================================================
**  ChipInfo_GetRawManufacturer
**
** ======================================================================== */

void ChipInfo_GetRawManufacturer
(
  ChipInfoDrvCtxt     *pCtxt,
  uint32 *pnRawManufacturer,
  uint32 nHWRevNum
)
{

  uint32 mfgIdBmsk, mfgIdShft;
  DALSYSPropertyVar PropVar;


  DALSYS_GetPropertyValue(pCtxt->hProps,"QUALCOMM_MFG_ID_BMSK",0,&PropVar);
  mfgIdBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"QUALCOMM_MFG_ID_SHFT",0,&PropVar);
  mfgIdShft = PropVar.Val.dwVal;

  *pnRawManufacturer = (nHWRevNum & mfgIdBmsk) >> mfgIdShft;

} /* END ChipInfo_GetRawManufacturer */


/* ===========================================================================
**  ChipInfo_GetRawPart
**
** ======================================================================== */

void ChipInfo_GetRawPart
(
  ChipInfoDrvCtxt     *pCtxt,
  uint32 *pnRawPart,
  uint32 nHWRevNum
)
{

  uint32 partNumBmsk, partNumShft;
  DALSYSPropertyVar PropVar;

  DALSYS_GetPropertyValue(pCtxt->hProps,"PARTNUM_BMSK",0,&PropVar);
  partNumBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"PARTNUM_SHFT",0,&PropVar);
  partNumShft = PropVar.Val.dwVal;

  *pnRawPart = (nHWRevNum & partNumBmsk) >> partNumShft;

} /* END ChipInfo_GetRawPart */


/* ===========================================================================
**  ChipInfo_GetRawVersion
**
** ======================================================================== */

void ChipInfo_GetRawVersion
(
  ChipInfoDrvCtxt     *pCtxt,
  uint32 *pnRawVersion,
  uint32 nHWRevNum
)
{
  uint32 versionIdBmsk, versionIdShft;
  DALSYSPropertyVar PropVar;

  DALSYS_GetPropertyValue(pCtxt->hProps,"VERSION_ID_BMSK",0,&PropVar);
  versionIdBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"VERSION_ID_SHFT",0,&PropVar);
  versionIdShft = PropVar.Val.dwVal;

  *pnRawVersion = (nHWRevNum & versionIdBmsk) >> versionIdShft;

} /* END ChipInfo_GetRawVersion */



/*=========================================================================
      Implementation
==========================================================================*/


/*==========================================================================

  FUNCTION      ChipInfo_DriverInit

  DESCRIPTION   See DDIChip.h

==========================================================================*/

DALResult ChipInfo_DriverInit
(
  ChipInfoDrvCtxt     *pCtxt
)
{
  DALResult eResult = DAL_SUCCESS;
  DALSYSPropertyVar PropVar;
  uint32 nHWIORegAddr = 0, nSOCHWVerRegAddr = 0;
  uint32 nHWRevNum, nSOCHWVerNum;
  uint32 nHWRevNumPhysAddress, nSOCHWVerPhysAddress;
  uint32 n,nPart=0;
    
  /* Get the property handle */
  DALSYS_GetDALPropertyHandle(DALDEVICEID_CHIPINFO,pCtxt->hProps);

  DALSYS_GetPropertyValue(pCtxt->hProps,"HWREVNUM_PHYS_ADDR",0,&PropVar);
  nHWRevNumPhysAddress = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"SOC_HW_VERSION_PHYS_ADDR",0,&PropVar);
  nSOCHWVerPhysAddress = PropVar.Val.dwVal;

  /*-----------------------------------------------------------------------*/
  /* Attach to the HWIO DAL.                                               */
  /*-----------------------------------------------------------------------*/
  eResult = DAL_DeviceAttach(DALDEVICEID_HWIO, &pCtxt->phDalHWIO);
  if (eResult == DAL_SUCCESS)
  {
     eResult = DalHWIO_MapRegionByAddress(pCtxt->phDalHWIO, (uint8*)nHWRevNumPhysAddress,(uint8 **)&nHWIORegAddr);
     eResult |= DalHWIO_MapRegionByAddress(pCtxt->phDalHWIO, (uint8*)nSOCHWVerPhysAddress,(uint8 **)&nSOCHWVerRegAddr);
  }
  else
  {
    nHWIORegAddr = nHWRevNumPhysAddress;
    nSOCHWVerRegAddr = nSOCHWVerPhysAddress;
  }
  DALSYS_GetPropertyValue(pCtxt->hProps,"HWREVNUM_OFFSET",0,&PropVar);
  nHWIORegAddr = PropVar.Val.dwVal  + nHWIORegAddr;
  DALSYS_GetPropertyValue(pCtxt->hProps,"SOC_HW_VERSION_OFFSET",0,&PropVar);
  nSOCHWVerRegAddr = PropVar.Val.dwVal  + nSOCHWVerRegAddr;

  nHWRevNum = *(uint32*)nHWIORegAddr;
  nSOCHWVerNum = *(uint32*)nSOCHWVerRegAddr;

  /*-----------------------------------------------------------------------*/
  /* Read chip information from HW.                                        */
  /*-----------------------------------------------------------------------*/

  ChipInfo_GetVersion(pCtxt,(DalChipInfoVersionType *)&pCtxt->nChipVersion, nSOCHWVerNum);
  ChipInfo_GetPart(pCtxt,(DalChipInfoIdType *)&pCtxt->eChipId, nHWRevNum);
  ChipInfo_GetRawVersion(pCtxt,&pCtxt->nRawChipVersion, nHWRevNum);
  ChipInfo_GetRawPart(pCtxt,&pCtxt->nRawChipId, nHWRevNum);
  ChipInfo_GetFamily(pCtxt,(DalChipInfoFamilyType *)&pCtxt->eChipFamily, nHWRevNum);

  /*-----------------------------------------------------------------------*/
  /* Check for override of the ChipId from the properties.                 */
  /*-----------------------------------------------------------------------*/

  if (pCtxt->eChipId == DALCHIPINFO_ID_UNKNOWN)
  {
    eResult = DALSYS_GetPropertyValue(pCtxt->hProps, "ChipIdOverride", 0, &PropVar);

    if (eResult == DAL_SUCCESS)
    {
      pCtxt->eChipId = (DalChipInfoIdType)PropVar.Val.dwVal;

      ChipInfo_GetFamilyByPart(
        (DalChipInfoIdType)pCtxt->eChipId,
        (DalChipInfoFamilyType *)&pCtxt->eChipFamily);

      pCtxt->nChipVersion = 0x00010000;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Fill in derived information.                                          */
  /*-----------------------------------------------------------------------*/

  /*
   * Look up using the table.
   */
  for (n = 0; n < DALCHIPINFO_CHIPID_MAP_SIZE; n++)
  {
    if (pCtxt->eChipId == chipIdMap[n].ePart)
    {
      nPart = chipIdMap[n].nPart;
      break;
    }
  }

  if (n == DALCHIPINFO_CHIPID_MAP_SIZE)
  {
    nPart = 0;
  }
  pCtxt->nModemSupport = DalChipInfoDataLUT[nPart].nModem;
  strlcpy(
    pCtxt->szChipIdString, DalChipInfoDataLUT[nPart].szChipId,
    DALCHIPINFO_MAX_ID_LENGTH);


  /*-----------------------------------------------------------------------*/
  /* Success.                                                              */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END ChipInfo_DriverInit */


/*==========================================================================

  FUNCTION      ChipInfo_DriverDeInit

  DESCRIPTION   See DDIChip.h

==========================================================================*/

DALResult ChipInfo_DriverDeInit
(
  ChipInfoDrvCtxt *pCtxt
)
{
  if (pCtxt->phDalHWIO != NULL)
  {
    DalDevice_Close(pCtxt->phDalHWIO);
  }

  /*-----------------------------------------------------------------------*/
  /* Success.                                                              */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END ChipInfo_DriverDeInit */


