#include "qurt_qdi.h"
#include "qurt_types.h"
#include "fastrpc_thread_queue.h"

#define QDI_FTQ_NAME                   "/dev/fastrpc-smd"
#define QDI_FTQ_BASE                   256
#define QDI_FTQ_PROCESS_INIT           (QDI_FTQ_BASE + 0)
#define QDI_FTQ_THREAD_INIT            (QDI_FTQ_BASE + 1)
#define QDI_FTQ_THREAD_EXIT            (QDI_FTQ_BASE + 2)
#define QDI_FTQ_INVOKE_RSP             (QDI_FTQ_BASE + 3)
#define QDI_FTQ_INVOKE_REQUEUE         (QDI_FTQ_BASE + 4)
#define QDI_FTQ_INVOKE_RSP_PENDING     (QDI_FTQ_BASE + 5)
#define QDI_FTQ_MEM_ADD                (QDI_FTQ_BASE + 6)

static __inline int ftq_qdi_open(void) {
   return qurt_qdi_open(QDI_FTQ_NAME);
}
static __inline int ftq_qdi_process_init(int handle, qurt_thread_t tidQ, char name[255], struct ftq_umsg** pmsg) {
   return qurt_qdi_handle_invoke(handle, QDI_FTQ_PROCESS_INIT, tidQ, name, pmsg);
}
static __inline int ftq_qdi_thread_init(int handle, qurt_thread_t tidQ, int tidA, struct ftq_umsg** pmsg) {
   return qurt_qdi_handle_invoke(handle, QDI_FTQ_THREAD_INIT, tidQ, tidA, pmsg);
}
static __inline int ftq_qdi_thread_exit(int handle, qurt_thread_t tidQ) {
   return qurt_qdi_handle_invoke(handle, QDI_FTQ_THREAD_EXIT, tidQ);
}
static __inline int ftq_qdi_invoke_rsp(int handle, qurt_thread_t tidQ, int ret) {
   return qurt_qdi_handle_invoke(handle, QDI_FTQ_INVOKE_RSP, tidQ, ret);
}
static __inline int ftq_qdi_invoke_requeue(int handle, qurt_thread_t tidQ) {
   return qurt_qdi_handle_invoke(handle, QDI_FTQ_INVOKE_REQUEUE, tidQ);
}
static __inline int ftq_qdi_invoke_rsp_pending(int handle, int tidA, int ret) {
   return qurt_qdi_handle_invoke(handle, QDI_FTQ_INVOKE_RSP_PENDING, tidA, ret);
}
static __inline int ftq_qdi_mem_add(int handle, qurt_addr_t addr, qurt_size_t size) {
   return qurt_qdi_handle_invoke(handle, QDI_FTQ_MEM_ADD, addr, size);
}

/**
 * kernel library functions
 */
int ftq_qdi_group_kcreateu(const char* name, int pidA, int asid, int client_handle);
void ftq_qdi_group_kdestroyu(int client_handle);
