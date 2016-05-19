#ifndef PERF_H
#define PERF_H

#include "HAP_perf.h"

/**
 * initialize a perf counter. To add this module to your code add
 * PL_DEP(perf).  see platform_libs.h
 *
 * @param name, the name of the counter
 * @param pix, the counter index. Its enabled when (*pix) != 0
 * @retval, 0 on success
 */
int perf_init(char* name, int* pix);

/**
 * macro to test if the counter is enabled
 */
#define perf_enabled(ix) ((ix) != 0)

/**
 * add sim micorseconds to the couner
 */
int perf_add_usec(int ix, uint64 usec);

/**
 * macro for wrapping code with a perf counter
 * 
 * PERF(me->counter,
 *    if(something) {
 *       do_something();
 *    } else {
 *       do_something_else();
 *    }
 *    PERF_END);
 */  

#define PERF_END (void)0

#define PERF(cnt, ff) \
   do {\
      if(!perf_enabled((cnt))) {\
         ff ;\
      } else {\
         uint64 start = HAP_perf_get_time_us();\
         ff ;\
         (void)perf_add_usec((cnt), HAP_perf_get_time_us() - start);\
      }\
   } while(0)

#endif //PERF_H
