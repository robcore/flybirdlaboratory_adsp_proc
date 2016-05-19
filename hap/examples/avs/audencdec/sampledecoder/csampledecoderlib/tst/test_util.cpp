/*===========================================================================

                  C A P I   T E S T   U T I L I T I E S

  Common definitions, types and functions for CAPI Examples

  Copyright (C) 2012 by QUALCOMM Technologies, Incorporated. All Rights Reserved.
===========================================================================*/

#include <stdio.h>
#include "test_util.h"

#define DFLT_OPEXT        ".raw"
static unsigned int num_mallocs = 0;
static unsigned int num_frees = 0;

static inline void capi_tst_atomic_add(unsigned int *target, unsigned int v)
{
    unsigned int result;

    __asm__ __volatile__(
        "1:     %0 = memw_locked(%2)\n"
        "       %0 = add(%0, %3)\n"
        "       memw_locked(%2, p0) = %0\n"
        "       if !p0 jump 1b\n"
        : "=&r" (result),"+m" (*target)
        : "r" (target), "r" (v)
        : "p0");
}



void usage(char *programName)  /* print syntax & exit */
{
   fprintf(stderr,"usage: %s  \n", programName);
   fprintf(stderr,"%s inputBS [outPCM]\n", programName);
   fprintf(stderr,"where\n");
   fprintf(stderr," inputBS  input bit stream of encoded audio\n");
   fprintf(stderr," outPCM   output PCM sound file (dflt inName+%s)\n",DFLT_OPEXT);
   exit(1);
}

void get_eargs(int argc, char **argv, Arg_t *args)
{
    char *programName = argv[0];

	printf("Number of args = %d\n", argc);
    if( 5 == argc )
    {
        // interpret Command Line arguments
        int i=0;
        int16_t input_option;
        args->in_fileName = NULL;
        args->out_fileName = NULL;

			  while ((input_option = getopt(argc, argv, "i:o")) != EOF)
			  {
				 switch (input_option)
				 {
					case 'i':
						args->in_fileName = argv[optind - 1];
					   break;

					case 'o':
						args->out_fileName = argv[optind];
					   break;
				 }
			  }
    }
    else
    {
        // invalid number of command line arguments
        usage( programName );
    } //

    // report results of dialog/command line
    printf("Input file = '%s'  output file = '%s'\n",
           args->in_fileName, args->out_fileName);
}


/*------------------------------------------------------------------------
  Function name: qurt_elite_memory_malloc
  Description- Mimics qurt elite memory malloc utility (also checks for
  memory corruption, if any standalone algorithms are doing so)
 * -----------------------------------------------------------------------*/
void* qurt_elite_memory_malloc(uint32_t unBytes, QURT_ELITE_HEAP_ID heapId)
{
   int* ptr;

   // round up to multiple of 4, and add space for guard words (8 bytes) and size (4 bytes)
   unBytes = (unBytes + 8 + 4 + 3) & 0xFFFFFFFCL;

   // Add space for guard words and size
   ptr = (int*)malloc(unBytes);
   if (!ptr)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Malloc failed!! Out of memory!!");
      return NULL;
   }

   // end guard word
   *(ptr + (unBytes >> 2) - 1) = 0xb4b4b4b4L;

   // beginning guard word
   *ptr++ = 0xa3a3a3a3L;

   // size of allocation
   *ptr++ = unBytes;

   capi_tst_atomic_add(&num_mallocs, 1);

   MSG_2(MSG_SSID_QDSP6, DBG_LOW_PRIO, "QURT_ELITE_MALLOC_FREE_TRACER: Mallocs %ld bytes, gets ptr 0x%p",unBytes, ptr);

   return ptr;

}

/*------------------------------------------------------------------------
  Function name: qurt_elite_memory_free
  Description- Mimics qurt elite memory free utility 
 * -----------------------------------------------------------------------*/
void qurt_elite_memory_free(void *ptr)
{
   // check for NULL.
   if (!ptr)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Trying to free null pointer!"); 
      return;
   }

   int* pPtr = (int*) ptr;

   // verify the health of the magic words and clear them
   if (*(pPtr - 2) != (int)0xa3a3a3a3L)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Heap corruption!! begining guard word before ptr 0x%p", pPtr);
   }

   // clear the magic word
   else *(pPtr - 2) = 0;

   uint32_t unBytes = *(pPtr - 1);
   if (*(pPtr + (unBytes >> 2) - 3) != (int)0xb4b4b4b4L)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Heap corruption!! end guard word after ptr 0x%p", pPtr);
   }

   // clear the magic word
   else *(pPtr + (unBytes >> 2) - 3) = 0;

   capi_tst_atomic_add(&num_frees, 1);

   MSG_2(MSG_SSID_QDSP6, DBG_LOW_PRIO, "QURT_ELITE_MALLOC_FREE_TRACER: frees %ld bytes, from ptr 0x%p",unBytes, pPtr);

   free(ptr);
}

