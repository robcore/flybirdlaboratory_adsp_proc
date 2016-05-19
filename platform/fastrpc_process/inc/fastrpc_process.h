#ifndef FASTRPC_PROCESS_H
#define FASTRPC_PROCESS_H

#include "qurt_thread.h"

int fastrpc_thread_notify(qurt_thread_t tidQ);
int fastrpc_thread_wait(void);
int fastrpc_group_notify(void);

int fastrpc_kprocess_createk(void);
void fastrpc_kprocess_destroyk(void);
void fastrpc_uprocess_dispatchu(void);

#endif // FASTRPC_PROCESS_H
