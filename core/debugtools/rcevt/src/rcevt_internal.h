#ifndef RCEVT_INTERNAL_H
#define RCEVT_INTERNAL_H
/**
@file rcevt_internal.h
@brief This file contains the API for the Run Control Event Notification, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2013 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcevt_internal.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stdlib.h"
#include "DALSys.h"
#include "rcecb.h"
#include "rcevt.h"

#include "err.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/////////////////////////////////////////////////////////////////////
// Tuneable Controls
/////////////////////////////////////////////////////////////////////

#define RCEVT_NODE_POOL_SIZ      64                                              // node_pool storage allocation (chunks)
#define RCEVT_NOTIFY_POOL_SIZ    (3*RCEVT_NODE_POOL_SIZ)                         // notify_pool storage allocation (chunks)
#define RCEVT_HASHTABLE_BUCKETS  63                                              // hashtable buckets storage allocation
#define RCEVT_SIGEX_MAXSIZ       2                                               // maximum size of the sigex.parm[] union/struct, pointers

/////////////////////////////////////////////////////////////////////
// Localized Manifest Constants
/////////////////////////////////////////////////////////////////////

#define RCE_NULL                 ((void*)0)
#define RCE_THRESHOLD_INIT       (0)
#define RCE_THRESHOLD_DEFAULT    (1)
#define RCE_NDE_COOKIE           (0xc00c1e00)                                    // cookie marker
#define RCE_NFY_COOKIE           (0xc00c1e11)                                    // cookie marker

/////////////////////////////////////////////////////////////////////
// Localized Type Declarations
/////////////////////////////////////////////////////////////////////

typedef struct
{
   DALSYSSyncHandle mutex;
   DALSYSSyncObj mutexObject;

} rce_mutex_t, * rce_mutex_p;

typedef unsigned long rce_hash_t;                                                // hash type
typedef unsigned long rce_cookie_t;

// RCE Internal Signaling Structure
/////////////////////////////////////////////////////////////////////

struct rce_nfy_s
{
   RCEVT_THRESHOLD threshold;                                                    // threshold value (RCEVT ONLY)

   RCEVT_SIGEX_TYPE sigex_type;                                                  // sigex type storage

   struct rce_nfy_sigex_s                                                        // sigex overlay storage based on type
   {
      void* parm[RCEVT_SIGEX_MAXSIZ];                                            // reflects maximum size (pointers)

   } sigex;                                                                      // this functions as a union

   struct rce_nfy_s* next;                                                       // next in notify queue
   rce_cookie_t nfy_cookie;                                                      // init cookie
};

typedef struct rce_nfy_s rce_nfy_t, * rce_nfy_p;

// RCE Internal Event Structure
/////////////////////////////////////////////////////////////////////

struct rce_nde_s
{
   RCEVT_NAME name;                                                              // name text
   RCEVT_THRESHOLD threshold;                                                    // threshold value (RCEVT ONLY)

   struct rce_nfy_s* notify_head;                                                // head notify queue
   struct rce_nde_s* next;                                                       // next node

   rce_mutex_t mutex;                                                            // mutex
   rce_cookie_t nde_cookie;                                                      // init cookie
};

typedef struct rce_nde_s rce_nde_t, * rce_nde_p;

// RCE Internal Signaling Structure Pool
/////////////////////////////////////////////////////////////////////

typedef struct rce_nfy_pool_s
{
   struct rce_nfy_s nfy_pool[RCEVT_NOTIFY_POOL_SIZ];
   struct rce_nfy_pool_s* next;                                                  // dynamic use; pointers to pool

} rce_nfy_pool_t, * rce_nfy_pool_p;                                              // storage type

// RCE Internal Event Structure Pool
/////////////////////////////////////////////////////////////////////

typedef struct rce_nde_pool_s
{
   struct rce_nde_s nde_pool[RCEVT_NODE_POOL_SIZ];
   struct rce_nde_pool_s* next;                                                  // dynamic use; pointers to pool

} rce_nde_pool_t, * rce_nde_pool_p;                                              // storage type

struct rce_internal_s
{
   rce_nde_pool_p nde_pool_head_p;                                               // dynamic storage tracking
   rce_nfy_pool_p nfy_pool_head_p;                                               // dynamic storage tracking

   rce_nfy_p nfy_pool_free_p;                                                    // next allocation head
   rce_nde_p nde_pool_free_p;                                                    // next allocation head

   rce_mutex_t mutex;                                                            // critical section mutex protects localized storage
   rce_mutex_t mutex_create;

   boolean dynamic_use;                                                          // allow dynamic pools expansion
   unsigned long init_flag;                                                      // service init

};

extern struct rce_internal_s rce_internal;                                       // rce internal instruments

extern rce_nfy_pool_t rce_nfy_pool_static;                                       // first pool static storage
extern rce_nde_pool_t rce_nde_pool_static;                                       // first pool static storage

extern rce_nde_p rce_hashtab[RCEVT_HASHTABLE_BUCKETS];                           // hashtable lookup buckets

/////////////////////////////////////////////////////////////////////
// Internal Forward Declarations
/////////////////////////////////////////////////////////////////////

#define rce_malloc(x)   (malloc(x))                                              // typecasts as accessor functions
#define nde2rcevt(x)    ((RCEVT_HANDLE)x)                                        // typecasts as accessor functions
#define nde2rcecb(x)    ((RCECB_HANDLE)x)                                        // typecasts as accessor functions
#define rcevt2nde(x)    ((rce_nde_p)x)                                           // typecasts as accessor functions
#define rcecb2nde(x)    ((rce_nde_p)x)                                           // typecasts as accessor functions

rce_nde_p rce_nde_hashtab_get(rce_hash_t hash);
void rce_nde_hashtab_put(rce_nde_p nde_p, rce_hash_t hash);
rce_hash_t rce_nmehash(RCEVT_NAME const name);
int rce_nmelen(RCEVT_NAME const name);
int rce_nmecmp(RCEVT_NAME const name_1, RCEVT_NAME const name_2, int len);
rce_nfy_p rce_nfy_pool_init(void);
rce_nfy_p rce_nfy_pool_alloc(void);
rce_nfy_p rce_nfy_pool_free(rce_nfy_p nfy_p);
rce_nde_p rce_nde_pool_init(void);
rce_nde_p rce_nde_pool_alloc(void);
rce_nde_p rce_nde_pool_free(rce_nde_p nde_p);
void rce_hashtab_init(void);
void rce_init(void);
void rce_term(void);

/////////////////////////////////////////////////////////////////////
// Internal Forward Declarations : DAL API (REQUIRED)
/////////////////////////////////////////////////////////////////////

void rce_mutex_init_dal(rce_mutex_p mutex_p);
void rce_mutex_lock_dal(rce_mutex_p mutex_p);
void rce_mutex_unlock_dal(rce_mutex_p mutex_p);

RCEVT_BOOL rce_nfy_eq_dal(rce_nfy_p nfy_p, RCEVT_SIGEX sigex);
void rce_nfy_init_dal(rce_nfy_p nfy_p, RCEVT_SIGEX sigex);
void rce_nfy_term_dal(rce_nfy_p nfy_p);
rce_nde_p rce_nfy_sig_dal(rce_nde_p nde_p, rce_nfy_p nfy_p);
rce_nde_p rce_nfy_wait_dal(rce_nde_p nde_p, rce_nfy_p nfy_p);

/////////////////////////////////////////////////////////////////////
// Internal Forward Declarations : POSIX API
/////////////////////////////////////////////////////////////////////

RCEVT_BOOL rce_nfy_eq_posix(rce_nfy_p nfy_p, RCEVT_SIGEX sigex);
void rce_nfy_init_posix(rce_nfy_p nfy_p, RCEVT_SIGEX sigex);
void rce_nfy_term_posix(rce_nfy_p nfy_p);
rce_nde_p rce_nfy_sig_posix(rce_nde_p nde_p, rce_nfy_p nfy_p);
rce_nde_p rce_nfy_wait_posix(rce_nde_p nde_p, rce_nfy_p nfy_p);

/////////////////////////////////////////////////////////////////////
// Internal Forward Declarations : QURT API
/////////////////////////////////////////////////////////////////////

RCEVT_BOOL rce_nfy_eq_qurt(rce_nfy_p nfy_p, RCEVT_SIGEX sigex);
void rce_nfy_init_qurt(rce_nfy_p nfy_p, RCEVT_SIGEX sigex);
void rce_nfy_term_qurt(rce_nfy_p nfy_p);
rce_nde_p rce_nfy_sig_qurt(rce_nde_p nde_p, rce_nfy_p nfy_p);
rce_nde_p rce_nfy_wait_qurt(rce_nde_p nde_p, rce_nfy_p nfy_p);

/////////////////////////////////////////////////////////////////////
// Internal Forward Declarations : REX API
/////////////////////////////////////////////////////////////////////

RCEVT_BOOL rce_nfy_eq_rex(rce_nfy_p nfy_p, RCEVT_SIGEX sigex);
void rce_nfy_init_rex(rce_nfy_p nfy_p, RCEVT_SIGEX sigex);
void rce_nfy_term_rex(rce_nfy_p nfy_p);
rce_nde_p rce_nfy_sig_rex(rce_nde_p nde_p, rce_nfy_p nfy_p);
rce_nde_p rce_nfy_wait_rex(rce_nde_p nde_p, rce_nfy_p nfy_p);

/////////////////////////////////////////////////////////////////////
// Internal Forward Declarations : Specialized
/////////////////////////////////////////////////////////////////////

RCECB_HANDLE rcecb_signal_handle_nolocks(RCECB_HANDLE handle);                   // specialized, no mutex protections, single thread only, *not for general use*
RCECB_HANDLE rcecb_signal_name_nolocks(RCECB_NAME name);                         // specialized, no mutex protections, single thread only, *not for general use*

#if defined(__cplusplus)
}
#endif

#endif
