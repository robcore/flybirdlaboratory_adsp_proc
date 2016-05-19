#ifndef QMI_SAP_TARGET_EXT_H
#define QMI_SAP_TARGET_EXT_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define QSAP_MALLOC(size)      malloc(size)
#define QSAP_CALLOC(num, size) calloc(num, size)
#define QSAP_FREE(ptr)         free(ptr)
#define QSAP_REALLOC(ptr,size) realloc(ptr, size)

#endif /* QMI_SAP_TARGET_EXT_H */
