
/*
  Copyright (C) 2009-2010 Qualcomm Technologies Incorporated.
  All rights reserved.
  QUALCOMM Proprietary/GTDR.

  $Header: //components/rel/avs.adsp/2.6.1/api/apr/apr_pack_end.h#3 $
  $Author: svutukur $
*/

#if defined( __GNUC__ )
  __attribute__((packed))
#elif defined( __arm__ )
#elif defined( _MSC_VER )
  #pragma pack( pop )
#else
  #error Unsupported compiler.
#endif /* __GNUC__ */

