#ifndef FASTRPC_PORT_H
#define FASTRPC_PORT_H

#include "fastrpc_internal.h"
struct fastrpc_port_msg {
   uint32 mode64;
   struct smq_msg msg;
};

void fastrpc_port_respond(struct fastrpc_port_msg* msg, int rsp);
int fastrpc_port_kinit(int (*enqueue)(void* ctx, struct fastrpc_port_msg* msg), 
                       void (*open)(void* ctx),
                       void (*close)(void* ctx),
                       void* ctx);

#endif // FASTRPC_PORT_H
