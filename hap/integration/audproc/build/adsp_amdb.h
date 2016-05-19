#ifndef _ADSP_AMDB_H
#define _ADSP_AMDB_H
#include "AEEStdDef.h"
#ifndef __QAIC_HEADER
#define __QAIC_HEADER(ff) ff
#endif //__QAIC_HEADER

#ifndef __QAIC_HEADER_EXPORT
#define __QAIC_HEADER_EXPORT
#endif // __QAIC_HEADER_EXPORT

#ifndef __QAIC_HEADER_ATTRIBUTE
#define __QAIC_HEADER_ATTRIBUTE
#endif // __QAIC_HEADER_ATTRIBUTE

#ifndef __QAIC_IMPL
#define __QAIC_IMPL(ff) ff
#endif //__QAIC_IMPL

#ifndef __QAIC_IMPL_EXPORT
#define __QAIC_IMPL_EXPORT
#endif // __QAIC_IMPL_EXPORT

#ifndef __QAIC_IMPL_ATTRIBUTE
#define __QAIC_IMPL_ATTRIBUTE
#endif // __QAIC_IMPL_ATTRIBUTE
#ifdef __cplusplus
extern "C" {
#endif
#if !defined(__QAIC_STRING1_OBJECT_DEFINED__) && !defined(__STRING1_OBJECT__)
#define __QAIC_STRING1_OBJECT_DEFINED__
#define __STRING1_OBJECT__
typedef struct _cstring1_s {
   char* data;
   int dataLen;
} _cstring1_t;

#endif /* __QAIC_STRING1_OBJECT_DEFINED__ */
/// @file adsp_amdb_mgr.idl
///
/***************************************************************************** 
    Add a dynamic CAPI module to the database
   
    id - module id
    preload - true if the shared object should be loaded during the add process
              false if the shared object should be loaded only when a module
              is queried that requires it
    filename_str - name of the shared object file (absolute path)
    getsize_str - name of the module's getsize()
    ctor_str - name of the module's ctor() function
  *****************************************************************************/
__QAIC_HEADER_EXPORT int __QAIC_HEADER(adsp_amdb_add_capi)(int id, boolean preload, const char* filename_str, const char* getsize_str, const char* ctor_str) __QAIC_HEADER_ATTRIBUTE;
/***************************************************************************** 
    Add a dynamic APPI module to the database
 
    id - module id
    preload - true if the shared object should be loaded during the add process
              false if the shared object should be loaded only when a module
              is queried that requires it
    filename_str - name of the shared object file (absolute path)
    getsize_str - name of the module's getsize()
    init_str - name of the module's init() function
  *****************************************************************************/
__QAIC_HEADER_EXPORT int __QAIC_HEADER(adsp_amdb_add_appi)(int id, boolean preload, const char* filename_str, const char* getsize_str, const char* init_str) __QAIC_HEADER_ATTRIBUTE;
/***************************************************************************** 
    Remove an APPI or CAPI module from the database based on module ID.  if
    filename_str is an empty string ("") then the module matching the id will
    be removed.  Otherwise all the APPI or CAPI associated with the shared
    object listed in filename_str will be removed.

    id - module id
    filename_str - name of the shared object, must not be NULL
  *****************************************************************************/
__QAIC_HEADER_EXPORT int __QAIC_HEADER(adsp_amdb_remove_capi)(int id, const char* filename_str) __QAIC_HEADER_ATTRIBUTE;
__QAIC_HEADER_EXPORT int __QAIC_HEADER(adsp_amdb_remove_appi)(int id, const char* filename_str) __QAIC_HEADER_ATTRIBUTE;
/***************************************************************************** 
    Remove all CAPI or APPI modules from the database
  *****************************************************************************/
__QAIC_HEADER_EXPORT int __QAIC_HEADER(adsp_amdb_remove_all_capi)(void) __QAIC_HEADER_ATTRIBUTE;
__QAIC_HEADER_EXPORT int __QAIC_HEADER(adsp_amdb_remove_all_appi)(void) __QAIC_HEADER_ATTRIBUTE;
#ifdef __cplusplus
}
#endif
#endif //_ADSP_AMDB_H
