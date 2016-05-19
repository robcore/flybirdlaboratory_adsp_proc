#ifndef QURT_TRACE_H
#define QURT_TRACE_H
/**
  @file qurt_trace.h 
  @brief  Prototypes of system call tracing helpers API  

EXTERNAL FUNCTIONS
   None.

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

Copyright (c) 2013  by Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.

=============================================================================*/



/*=============================================================================
												GLOBAL VARIABLES
=============================================================================*/

/* ETM trace type */
#define QURT_ETM_TYPE_PC_ADDR                           (1<<0)
#define QURT_ETM_TYPE_MEMORY_ADDR                       (1<<1)
#define QURT_ETM_TYPE_TESTBUS                           (1<<2)
#define QURT_ETM_TYPE_CYCLE_ACCURATE                    (1<<3)
#define QURT_ETM_TYPE_CYCLE_COARSE                      (1<<4)
#define QURT_ETM_TYPE_PC_AND_MEMORY_ADDR                (QURT_ETM_TYPE_PC_ADDR|QURT_ETM_TYPE_MEMORY_ADDR)
#define QURT_ETM_TYPE_PC_ADDR_AND_TESTBUS               (QURT_ETM_TYPE_PC_ADDR|QURT_ETM_TYPE_TESTBUS)
#define QURT_ETM_TYPE_MEMORY_ADDR_AND_TESTBUS           (QURT_ETM_TYPE_MEMORY_ADDR|QURT_ETM_TYPE_TESTBUS)
#define QURT_ETM_TYPE_PC_AND_MEMORY_ADDR_AND_TESTBUS    (QURT_ETM_TYPE_PC_ADDR|QURT_ETM_TYPE_MEMORY_ADDR|QURT_ETM_TYPE_TESTBUS)

/* ETM Route */
#define QURT_ETM_ROUTE_TO_QDSS      0
#define QURT_ETM_ROUTE_TO_Q6ETB     1

/* ETM Filter */
#define QURT_ETM_TRACE_FILTER_ALL_DEFAULT   0
#define QURT_ETM_TRACE_FILTER_HNUM0         1     
#define QURT_ETM_TRACE_FILTER_HNUM1         2       
#define QURT_ETM_TRACE_FILTER_HNUM2         4       
#define QURT_ETM_TRACE_FILTER_HNUM3         8     
#define QURT_ETM_TRACE_FILTER_ALL           15

/* ETM Enable flags */
#define QURT_ETM_OFF                0
#define QURT_ETM_ON                 1

  
/*=============================================================================
												GLOBAL FUNCTIONS
=============================================================================*/


/**@ingroup func_qurt_trace_get_marker
  Gets the kernel trace marker.\n
  Returns the current value of the kernel trace marker.
  The marker consists of a hardware thread identifier and an index into the kernel trace
  buffer. The trace buffer records various kernel events.

  @note1hang This function is used with qurt_trace_changed() to
             determine whether certain kernel events occurred in a block of code.

  @return
  Integer -- Kernel trace marker.

  @dependencies
  None.
*/
unsigned int qurt_trace_get_marker(void);

/**@ingroup func_qurt_trace_changed
  Determines whether specific kernel events have occurred. \n
  Returns a value indicating whether the specified kernel events have been recorded in the
  kernel trace buffer since the specified kernel trace marker was obtained.

  The prev_trace_marker parameter specifies a kernel trace marker which was obtained by calling 
  qurt_trace_get_marker().
  For more information on the mask value refer to the description of the trace_mask element in
   @xhyperref{Q3,[Q3]}. \n

  @note1hang This function is used with qurt_trace_get_marker to determine whether
             certain kernel events occurred in a block of code.\n
  @note1cont This function cannot determine whether a specific kernel event type has
             occurred unless that event type has been enabled in the trace_mask element
             of the system configuration file. \n
  @note1cont QuRT supports the recording of interrupt and context switch events only (i.e.,
             a trace_mask value of 0x3).

  @param[in] prev_trace_marker Previous kernel trace marker.
  @param[in] trace_mask        Mask value indicating the kernel events to check for.

  @returns
  1 -- Kernel events of the specified type have occurred since the
       specified trace marker was obtained.\n
  0 -- No kernel events of the specified type have occurred since the
       specified trace marker was obtained.

  @dependencies
  None.
*/
int qurt_trace_changed(unsigned int prev_trace_marker, unsigned int trace_mask);

/*=============================================================================
												CONSTANTS AND MACROS
=============================================================================*/
/** @addtogroup function_tracing_macro
@{ */
#ifndef QURT_DEBUG
#define QURT_TRACE(str, ...) __VA_ARGS__
  /**< Function tracing is implemented with a debug macro (QURT_TRACE), that
       optionally generates printf statements both before and after every function call that is
       passed as a macro argument. 

       For example, the following macro call in the source code:
       @code
       QURT_TRACE(myfunc, my_func(33))
       
       @endcode
       generates the following debug output:
       @code
       myfile:nnn: my_func >>> calling my_func(33)
       myfile:nnn: my_func >>> returned my_func(33)
       @endcode
       The debug output includes the source file and line number of the function call, along with
       the text of the call itself.

       The debug output is generated using the library function qurt_printf.
       Generation of the debug output is controlled by the symbol QURT_DEBUG. If this symbol is
       not defined, function tracing is not generated.\n
       @note1hang The debug macro is accessed through the QuRT API header file. 
        */
#else
#define QURT_TRACE(str, ...) \
	do { \
		qurt_printf("%s:%d: %s: >>> calling %s\n",__FILE__,__LINE__,str,#__VA_ARGS__); \
		__VA_ARGS__; \
		qurt_printf("%s:%d: %s: <<< %s returned\n",__FILE__,__LINE__,str,#__VA_ARGS__); \
	} while (0);
#endif
/** @} */ /* end_addtogroup function_tracing_macro */


/**@ingroup func_qurt_etm_set_config
  Set up configuration for ETM.\n

   type:
      QURT_ETM_TYPE_PC_ADDR
      QURT_ETM_TYPE_MEMORY_ADDR
      QURT_ETM_TYPE_TESTBUS
      QURT_ETM_TYPE_CYCLE_ACCURATE
      QURT_ETM_TYPE_CYCLE_COARSE 
      

   route 
      QURT_ETM_ROUTE_TO_QDSS 
      QURT_ETM_ROUTE_TO_Q6ETB

   filter 
      QURT_ETM_TRACE_FILTER_ALL_DEFAULT
      QURT_ETM_TRACE_FILTER_HNUM0
      QURT_ETM_TRACE_FILTER_HNUM1
      QURT_ETM_TRACE_FILTER_HNUM2
      QURT_ETM_TRACE_FILTER_HNUM3
      QURT_ETM_TRACE_FILTER_ALL 

   This function has to be called before enabling ETM, or after stopping ETM. 

  @returns
  0 -- Set up configuration sucessfully.
  1 -- Failed at configuration setup.

  @dependencies
  None.
*/
unsigned int qurt_etm_set_config(unsigned int type, unsigned int route, unsigned int filter);


/**@ingroup func_qurt_etm_enable
  Enable or disable ETM trace.\n

  enable_flag:
      QURT_ETM_ON 
      QURT_ETM_OFF 

  The default ETM configuration after system bootup,
    type=QURT_ETM_TYPE_PC_ADDR, route=QURT_ETM_ROUTE_TO_QDSS,filter=QURT_ETM_TRACE_FILTER_ALL 
  And it is applied to qurt_etm_enable() when no qurt_etm_set_config() is called.
      
  @returns
  0 -- Success
  1 -- Failed 

  @dependencies
  None.
*/
unsigned int qurt_etm_enable(unsigned int enable_flag);

#endif /* QURT_TRACE_H */
