#ifndef RCINIT_INTERNAL_H
#define RCINIT_INTERNAL_H
/** vi: tw=128 ts=3 sw=3 et
@file rcinit_internal.h
@brief This file contains the API for the Run Control Framework, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2014 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcinit/src/rcinit_internal.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stdlib.h"

#include "rcinit_dal.h"
#include "rcevt_internal.h"
#include "rcxh.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/////////////////////////////////////////////////////////////////////
// Tuneable Controls
/////////////////////////////////////////////////////////////////////

#define rcinit_internal_malloc(x)   malloc(x)                                    // internal allocator implementation wrapper
#define rcinit_internal_free(x)     free(x)                                      // internal allocator implementation wrapper

/////////////////////////////////////////////////////////////////////
// Localized Manifest Constants
/////////////////////////////////////////////////////////////////////

#define SIG_ACK                                       0x00010000
#define SIG_TMO                                       0x00020000
#define SIG_BAIL                                      0x00040000

#define RCINIT_NAME_MAX                               16    // Tracks QURT_THREAD_ATTR_NAME_MAXLEN or (REX_TASK_NAME_LEN+1)
#define RCINIT_TASK_MAX                               200   // maximum number of tasks tracked for compile time sized tables

#define RCINIT_STACK_NULL                             ((rcinit_stack_p)0)
#define RCINIT_STACK_NONE                             ((rcinit_stack_p)-1)
#define RCINIT_STACK_INIT                             (0xa5)

#define RCINIT_ENTRY_NULL                             ((rcinit_entry_p)0)
#define RCINIT_ENTRY_NONE                             ((rcinit_entry_p)-1)

// REX API use on NONHLOS (Tech Areas must use REX_SINGLE_CPU_AFFINITY_MASK or REX_ANY_CPU_AFFINITY_MASK)

#define RCINIT_AFFINITY_NONE                          (0)   // QURT EQUIVILENT IS RCINIT_AFFINITY_ALL, INTERNAL RCINIT USE ONLY
#define RCINIT_AFFINITY_SINGLE                        (1)
#define RCINIT_AFFINITY_ALL                           (255) // QURT EQUIVILENT IS (-1)

#if defined(FEATURE_QURT)
#define RCINIT_MAP_REX_DEF_TASK(a, b, c, d, e, f, g, h, i, j) rex_def_task_ext5(a, b, c, d, e, f, g, h, i, j)
#undef  REX_ANY_SMT_MASK
#define REX_ANY_SMT_MASK               RCINIT_AFFINITY_ALL
#undef  REX_ANY_CPU_AFFINITY_MASK
#define REX_ANY_CPU_AFFINITY_MASK      RCINIT_AFFINITY_ALL // ADSP_PROC HACK: NO REX.H, QURT.H == QURT_THREAD_ATTR_AFFINITY_DEFAULT
#else // defined(FEATURE_L4) || defined(FEATURE_REX)
#define RCINIT_MAP_REX_DEF_TASK(a, b, c, d, e, f, g, h, i, j) rex_def_task_ext2(b, c, d, e, f, g, h, i, j)
#ifndef REX_SINGLE_CPU_AFFINITY_MASK
#define REX_SINGLE_CPU_AFFINITY_MASK   RCINIT_AFFINITY_NONE
#undef  REX_COMMON_SMT_MASK
#define REX_COMMON_SMT_MASK            RCINIT_AFFINITY_NONE
#endif
#ifndef REX_ANY_CPU_AFFINITY_MASK
#define REX_ANY_CPU_AFFINITY_MASK      RCINIT_AFFINITY_NONE
#undef  REX_ANY_SMT_MASK
#define REX_ANY_SMT_MASK               RCINIT_AFFINITY_NONE
#endif
#endif

// MAP Different NONHLOS Interfaces to RCINIT Priority Concept
// RCINIT priority database is 0 = low, 255 = high

#define RCINIT_MAP_PRIO_DAL(x)                        (x)
#define RCINIT_MAP_PRIO_POSIX(x)                      (x)
#define RCINIT_MAP_PRIO_QURT(x)                       ((((int)255-(int)(x))>=0)?((int)255-(int)(x)):255) // literals used here because they reflect QURT_PRI
#define RCINIT_MAP_PRIO_REX(x)                        (x)

// Logic Used to Determine if RCINIT Database Entry is INITFN
// Internal Macro : IS_INITFN, entry, no handle, no priority, no stack size, no stack pointer, not rcinit

#define IS_INITFN(rcinit_p) \
    RCINIT_NULL != rcinit_p && \
    RCINIT_NULL != rcinit_p->entry && \
    RCINIT_TASK_INITFN == rcinit_p->type && \
    RCINIT_PRIO_INITFN == rcinit_p->prio && \
    RCINIT_STKSZ_ZERO == rcinit_p->stksz && \
    RCINIT_NULL == rcinit_p->handle && \
    rcinit_lookup("rcinit") != rcinit_p

// Logic Used to Determine if RCINIT Database Entry is TASK
// Internal Macro : IS_TASK, entry, handle, priority, stack size, stack pointer, not rcinit

#define IS_TASK(rcinit_p) \
    RCINIT_NULL != rcinit_p && \
    RCINIT_NULL != rcinit_p->entry && \
    (RCINIT_TASK_DALTASK == rcinit_p->type || RCINIT_TASK_POSIX == rcinit_p->type || RCINIT_TASK_QURTTASK == rcinit_p->type || RCINIT_TASK_REXTASK == rcinit_p->type) && \
    RCINIT_PRIO_INITFN != rcinit_p->prio && \
    RCINIT_STKSZ_ZERO != rcinit_p->stksz && \
    RCINIT_NULL != rcinit_p->handle && \
    rcinit_lookup("rcinit") != rcinit_p

// internally managed events (no observers, these are policy based with ack)

#define RCINIT_RCEVT_INTERNAL_PREFIX         "rci:"

#define RCINIT_RCEVT_DEFINE                  RCINIT_RCEVT_INTERNAL_PREFIX "define"
#define RCINIT_RCEVT_DEFINEACK               RCINIT_RCEVT_INTERNAL_PREFIX "defack"
#define RCINIT_RCEVT_INITFN                  RCINIT_RCEVT_INTERNAL_PREFIX "initfn"
#define RCINIT_RCEVT_TERMACK                 RCINIT_RCEVT_INTERNAL_PREFIX "trmack"
#define RCINIT_RCEVT_TERM_BARRIER            RCINIT_RCEVT_INTERNAL_PREFIX "trmbar"

#define RCINIT_RCECB_INIT_GROUP_0            RCINIT_RCEVT_INTERNAL_PREFIX "ifcb:0"
#define RCINIT_RCECB_INIT_GROUP_1            RCINIT_RCEVT_INTERNAL_PREFIX "ifcb:1"
#define RCINIT_RCECB_INIT_GROUP_2            RCINIT_RCEVT_INTERNAL_PREFIX "ifcb:2"
#define RCINIT_RCECB_INIT_GROUP_3            RCINIT_RCEVT_INTERNAL_PREFIX "ifcb:3"
#define RCINIT_RCECB_INIT_GROUP_4            RCINIT_RCEVT_INTERNAL_PREFIX "ifcb:4"
#define RCINIT_RCECB_INIT_GROUP_5            RCINIT_RCEVT_INTERNAL_PREFIX "ifcb:5"
#define RCINIT_RCECB_INIT_GROUP_6            RCINIT_RCEVT_INTERNAL_PREFIX "ifcb:6"
#define RCINIT_RCECB_INIT_GROUP_7            RCINIT_RCEVT_INTERNAL_PREFIX "ifcb:7"

#define RCINIT_RCEVT_INIT_GROUP_0            RCINIT_RCEVT_INTERNAL_PREFIX "init:0"
#define RCINIT_RCEVT_INIT_GROUP_1            RCINIT_RCEVT_INTERNAL_PREFIX "init:1"
#define RCINIT_RCEVT_INIT_GROUP_2            RCINIT_RCEVT_INTERNAL_PREFIX "init:2"
#define RCINIT_RCEVT_INIT_GROUP_3            RCINIT_RCEVT_INTERNAL_PREFIX "init:3"
#define RCINIT_RCEVT_INIT_GROUP_4            RCINIT_RCEVT_INTERNAL_PREFIX "init:4"
#define RCINIT_RCEVT_INIT_GROUP_5            RCINIT_RCEVT_INTERNAL_PREFIX "init:5"
#define RCINIT_RCEVT_INIT_GROUP_6            RCINIT_RCEVT_INTERNAL_PREFIX "init:6"
#define RCINIT_RCEVT_INIT_GROUP_7            RCINIT_RCEVT_INTERNAL_PREFIX "init:7"

#define RCINIT_RCECB_TERM_GROUP_0            RCINIT_RCEVT_INTERNAL_PREFIX "tfcb:0"
#define RCINIT_RCECB_TERM_GROUP_1            RCINIT_RCEVT_INTERNAL_PREFIX "tfcb:1"
#define RCINIT_RCECB_TERM_GROUP_2            RCINIT_RCEVT_INTERNAL_PREFIX "tfcb:2"
#define RCINIT_RCECB_TERM_GROUP_3            RCINIT_RCEVT_INTERNAL_PREFIX "tfcb:3"
#define RCINIT_RCECB_TERM_GROUP_4            RCINIT_RCEVT_INTERNAL_PREFIX "tfcb:4"
#define RCINIT_RCECB_TERM_GROUP_5            RCINIT_RCEVT_INTERNAL_PREFIX "tfcb:5"
#define RCINIT_RCECB_TERM_GROUP_6            RCINIT_RCEVT_INTERNAL_PREFIX "tfcb:6"
#define RCINIT_RCECB_TERM_GROUP_7            RCINIT_RCEVT_INTERNAL_PREFIX "tfcb:7"

#define RCINIT_RCEVT_TERM_GROUP_0            RCINIT_RCEVT_INTERNAL_PREFIX "term:0"
#define RCINIT_RCEVT_TERM_GROUP_1            RCINIT_RCEVT_INTERNAL_PREFIX "term:1"
#define RCINIT_RCEVT_TERM_GROUP_2            RCINIT_RCEVT_INTERNAL_PREFIX "term:2"
#define RCINIT_RCEVT_TERM_GROUP_3            RCINIT_RCEVT_INTERNAL_PREFIX "term:3"
#define RCINIT_RCEVT_TERM_GROUP_4            RCINIT_RCEVT_INTERNAL_PREFIX "term:4"
#define RCINIT_RCEVT_TERM_GROUP_5            RCINIT_RCEVT_INTERNAL_PREFIX "term:5"
#define RCINIT_RCEVT_TERM_GROUP_6            RCINIT_RCEVT_INTERNAL_PREFIX "term:6"
#define RCINIT_RCEVT_TERM_GROUP_7            RCINIT_RCEVT_INTERNAL_PREFIX "term:7"

// Type Mapping to Internal State

typedef enum
{
   // rcinit task processing state

   rcinit_process_none = 0x000000ff,                                             // rcinit specific
   rcinit_process_init = 0x00000001,                                             // rcinit initialize
   rcinit_process_group_policy_fn = 0x00000002,                                  // rcinit processes policyfn (per group)
   rcinit_process_group_sizing = 0x00000003,                                     // rcinit processes statics sizing (per group)
   rcinit_process_group_allocation = 0x00000004,                                 // rcinit processes allocations (per group)
   rcinit_process_group_assignment = 0x00000005,                                 // rcinit processes statics assignment (per group)
   rcinit_process_group_init_fn = 0x00000006,                                    // rcinit processes initfn (per group)
   rcinit_process_group_init_task = 0x00000007,                                  // rcinit processes tasks (per group)
   rcinit_process_group_init_blocking = 0x00000008,                              // rcinit blocking for task handshakes (per group)
   rcinit_process_group_run = 0x00000009,                                        // rcinit releases group to run (per group)
   rcinit_process_blocking = 0x0000000a,                                         // rcinit blocking
   rcinit_process_running = 0x0000000b,                                          // rcinit running
   rcinit_process_group_term_task = 0x0000000c,                                  // rcinit processes tasks (per group)
   rcinit_process_group_term_blocking = 0x0000000d,                              // rcinit processes tasks (per group)
   rcinit_process_group_term_fn = 0x0000000e,                                    // rcinit processes termfn (per group)
   rcinit_process_term = 0x000000fe,                                             // rcinit done
   rcinit_process_mask = rcinit_process_none,

   rcinit_context_none = 0x0000ff00,                                             // context specific, not active (set by rcinit)
   rcinit_context_mask = rcinit_context_none,

   // internal use

   rcinit_state_unknown = 0x00000000,
   rcinit_state_max = 0x7fffffff

} rcinit_state_t;

// Type Mapping to NONHLOS

typedef void* rcinit_tid_p;
typedef unsigned long rcinit_stack_t, * rcinit_stack_p;                          // native stack
typedef void* rcinit_entry_p;

// volatile memory structure associated to tasks, inits NULL

typedef struct rcinit_handle_s                                                   // Implementation Details of Database
{
   rcinit_tid_p tid_p;                                                           // tid pointer
   rcinit_stack_p stack;                                                         // stack pointer
   rcinit_entry_p entry;                                                         // entry address
   void* unused;

} rcinit_handle, * rcinit_handle_p;

#define RCINIT_CONTEXT_STATE(y, x) do { if (RCINIT_NULL != (y) && RCINIT_NULL != (y)->handle) { (y)->handle->context_state = (x); } } while(0)

// rcinit task information database

typedef struct rcinit_info_s                                                     // Implementation Details of Database
{
   RCINIT_NAME name;
   RCINIT_HASH hash;
   RCINIT_TASK type;                                                             // private
   RCINIT_ENTRY entry;                                                           // entry point of task or init_function
   RCINIT_PRIO prio;                                                             // priority of task
   RCINIT_STKSZ stksz;                                                           // stack size
   RCINIT_AFFINITY cpu_affinity;                                                 // processor affinity
   rcinit_handle_p handle;                                                       // handle volatile memory for tasks

} rcinit_info, rcinit_info_t, * rcinit_info_p;

// rcinit task information database map name to data

typedef struct rcinit_internal_policy_map_s
{
   RCINIT_NAME name;
   int index;

} rcinit_internal_policy_map_t;

// rcinit task provisioning

typedef struct rcinit_internal_name_map_s                                        // Implementation Details of Database
{
   RCINIT_NAME name;                                                             // string identifier
   const rcinit_info_t* info_p;                                                  // internal pointer to rcinit_info structure associated with identifier

} rcinit_internal_name_map_t;

typedef struct rcinit_internal_hs
{
   RCINIT_GROUP group;
   char task_name[RCINIT_NAME_MAX];
   unsigned long hs;                                                             // the first and only acceptable single handshake per group
   unsigned long hs_dup;                                                         // duplicates, same group
   unsigned long hs_oob;                                                         // out of band, different group
   void* tid;

} rcinit_internal_hs_t, * rcinit_internal_hs_p;

// rcinit instrumentation state progression

extern const int rcinit_internal_name_map_size;
extern const rcinit_internal_name_map_t rcinit_internal_name_map[];              // provisioning info name map
extern const int rcinit_internal_policy_map_size;
extern const rcinit_internal_policy_map_t rcinit_internal_policy_map[];          // policy name map
extern const rcinit_info_t*** rcinit_internal_groups[];                          // top of database tree
extern const RCINIT_NAME rcinit_internal_policy_list[];                          // null terminated list of policy names

// processing state
// trace32: v.v rcinit_internal

struct rcinit_internal_s
{
   rcinit_state_t process_state;                                                 // current group processing state

   RCINIT_POLICY policy_curr;                                                    // current policy (numeric, range 0 .. rcinit_internal_policy_map_size)
   const rcinit_info_t*** policy_base;                                           // base pointer loaded from index

   RCINIT_GROUP group_curr;                                                      // current group (numeric, range 0 .. RCINIT_GROUP_MAX)
   const rcinit_info_t** group_base;                                             // base pointer loaded from index

   // the following instruments are used for indepth manual debugging

   rce_nde_p define;                                                             // internal event, rcinit_task <- client context created and blocks
   rce_nde_p defineack;                                                          // internal event, rcinit_task -> client contexts released to run

   struct
   {
      RCEVT_THRESHOLD curr;                                                      // tasks defined this group
      RCEVT_THRESHOLD prev;                                                      // tasks defined previous group

   } def;

   // internal worker

   const rcinit_info_t** worker_argv;                                            // worker argv (coordinated by rcevt initfn)
   DALSYSEventHandle hEventWorkLoop;                                             // worker event
   DALSYSEventHandle hEventWorkLoopAck;                                          // worker event
   DALSYSWorkLoopHandle hWorkLoop;                                               // worker loop
   DALSYSEventHandle hEventInitFnSpawn;                                          // worker event

   // internal rcinit

   unsigned long stacks_size;                                                    // total stacks allotment (set after process_stacks) in KB
   unsigned char* allocs[RCINIT_GROUP_MAX];                                      // base to block of stacks allotment
   rcinit_stack_p stacks[RCINIT_GROUP_MAX];                                      // base to block of stacks allotment

   int tls_key;

   RCINIT_GROUP group_curr_idx;                                                  // current group index (used in loops)

   void (*initfn_curr)(void);                                                    // rcworker current initfn

   // internal instruments

   struct
   {
      rce_nde_p init_event[RCINIT_GROUP_MAX];                                    // event notification init
      rce_nde_p term_event[RCINIT_GROUP_MAX];                                    // event notification term

   } rcevt_handle;                                                               // event notification handles

   rcinit_internal_hs_t hs_init[RCINIT_TASK_MAX];                                // term, registered tasks, per group, handshakes ignored
   rcinit_internal_hs_t hs_term[RCINIT_TASK_MAX];                                // term, registered tasks, per group, handshakes ignored
};

extern const RCECB_NAME rcinit_init_rcecb[RCINIT_GROUP_MAX];                     // internal
extern const RCECB_NAME rcinit_term_rcecb[RCINIT_GROUP_MAX];                     // internal

extern const RCEVT_NAME rcinit_init_rcevt[RCINIT_GROUP_MAX];                     // internal
extern const RCEVT_NAME rcinit_term_rcevt[RCINIT_GROUP_MAX];                     // internal

extern const RCINIT_NAME rcinit_swe_name_init[RCINIT_GROUP_MAX];                 // internal
extern const RCINIT_NAME rcinit_swe_name_term[RCINIT_GROUP_MAX];                 // internal

extern unsigned long rcinit_term_tmo[RCINIT_GROUP_MAX];                          // internal

extern long rcinit_term_err_fatal;                                               // internal
extern long rcinit_term_timeout;                                                 // internal
extern long rcinit_term_latency_enable;                                          // internal

extern struct rcinit_internal_s rcinit_internal;                                 // internal, TRACE32 v.v rcinit_internal

RCXH_EXT(RCXH_RCINIT_TASK_END);
RCXH_EXT(RCXH_RCINIT_TASK_RESTART);

/////////////////////////////////////////////////////////////////////
// Internal Function Prototypes
/////////////////////////////////////////////////////////////////////

extern DALSYSEventHandle hEventCoreStarted;                                      // direct access, bootstrap only

DALResult rcinit_task_dal(DALSYSEventHandle hEvent, void* arg_p);                // direct access, bootstrap only
void rcinit_task_rex(unsigned long);                                             // direct access, bootstrap only

void rcinit_init(void);
void rcinit_internal_process_groups(void);

void rcinit_term(void);
void rcinit_internal_unprocess_groups(void);

// Internal Handshake Instruments

unsigned long rcinit_internal_nmehash(RCINIT_NAME const name);
unsigned long rcinit_internal_task_name(char* task_name, int buflen);

void rcinit_internal_hs_list_init(void);
unsigned long rcinit_internal_hs_list_add(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name);
unsigned long rcinit_internal_hs_list_del(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name);
unsigned long rcinit_internal_hs_list_query(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name);
unsigned long rcinit_internal_hs_list_query_hs(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name);
unsigned long rcinit_internal_hs_list_query_bl(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name);
unsigned long rcinit_internal_hs_list_hs(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name);
unsigned long rcinit_internal_hs_list_bl(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name);

void rcinit_internal_devcfg_check_load(void);

unsigned long rcinit_term_err_fatal_set(unsigned long val);
unsigned long rcinit_term_latency_enable_set(unsigned long val);
unsigned long rcinit_term_timeout_group_get(RCINIT_GROUP group);
unsigned long rcinit_term_timeout_group_set(RCINIT_GROUP group, unsigned long timeout_ms);
unsigned long rcinit_term_timeout_get(void);
unsigned long rcinit_term_timeout_set(unsigned long timeout_ms);

void rcinit_internal_start_daltask(const rcinit_info_t* rcinit_p, void* entry);
void rcinit_internal_start_posix(const rcinit_info_t* rcinit_p, void* entry);
void rcinit_internal_start_qurttask(const rcinit_info_t* rcinit_p, void* entry);
void rcinit_internal_start_rextask(const rcinit_info_t* rcinit_p, void* entry);

RCINIT_GROUP rcinit_lookup_group_current(void);

// TLS Binding to NONHLOS (INTERNAL)

int rcinit_internal_tls_create_key(int*, void (*)(void*));
int rcinit_internal_tls_set_specific(int, void*);
void* rcinit_internal_tls_get_specific(int);

// Internal Unit Test Functions

void rcinit_ut_blacklist(unsigned long list_count, RCINIT_NAME list[]);
void rcinit_ut_whitelist(unsigned long list_count, RCINIT_NAME list[]);

#if defined(__cplusplus)
}
#endif

#endif
