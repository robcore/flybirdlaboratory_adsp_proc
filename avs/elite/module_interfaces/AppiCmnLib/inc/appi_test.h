#ifndef __APPI_TEST_H
#define __APPI_TEST_H
/*===========================================================================

                  A P P I   T E S T   U T I L I T I E S

  Common definitions, types and functions for APPI Examples

  Copyright (C) 2011 by Qualcomm Technologies, Incorporated. All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/avs.adsp/2.6.1/elite/module_interfaces/AppiCmnLib/inc/appi_test.h#3 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
2011/05/19 ss      Created file
===========================================================================*/

#include "appi_util.h"
#include "Elite_APPI.h"

#define MAX_CHANNELS 8
const uint32_t wordSize = 30;

typedef struct _args_t
{
   char *input_filename;
   char *output_filename;
   char *config_filename;
}
args_t;

typedef struct _module_info_t
{
   appi_t*    module_ptr;
   uint32_t   is_enabled;
   uint32_t   alg_delay;
   bool_t     is_in_place;
   uint32_t   in_buffer_len;
   uint32_t   out_buffer_len;
   uint32_t   num_in_channels;
   uint32_t   num_out_channels;
   uint32_t   in_sampling_rate;
   uint32_t   out_sampling_rate;
   uint32_t   in_bits_per_sample;
   uint32_t   out_bits_per_sample;
   bool_t     is_interleaved;
   bool_t     is_compressed;
   uint32_t   compressed_format_id;
   FILE*      finp;
   FILE*      fout;
   FILE*      fCfg;
} module_info_t;

struct testCommand
{
    char opCode[wordSize];
    ADSPResult(*pFunction)(module_info_t * module);
};

ADSPResult RunTest(module_info_t* module, const testCommand *pExtendedCmdSet = NULL, const uint32_t extendedCmdSetSize = 0);

ADSPResult GetWord(FILE* fCfg, char word[]);
ADSPResult GetUIntParameter(FILE* fCfg, const char parameterName[], uint32_t *pValues);
ADSPResult GetIntParameter(FILE* fCfg, const char parameterName[], int32_t *pValue);
ADSPResult ReadBufferContents(FILE *fCfg, const uint32_t payloadSize, uint8_t *pPayload);
uint32_t appi_tst_get_num_mallocs();
uint32_t appi_tst_get_num_frees();
void appi_tst_set_malloc_failure(int num_mallocs_to_skip);
void appi_tst_clear_malloc_failure(void);

void usage(FILE * fp, char *prog_name);

void get_eargs(
      int32_t argc,
      char *argv[],
      args_t* input_args
      );

#endif // __APPI_TEST_H

