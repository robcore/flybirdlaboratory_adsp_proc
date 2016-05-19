#ifndef FASTRPC_LOADER_H
#define FASTRPC_LOADER_H

struct smq_phy_page; 
/**
 * spawn a new process
 * prorcess_init, this gets called when a asid and client ahndle are known, but before we actually spawn
 */
int fastrpc_spawn(int pidA, const char* appsname, const char* elffile, int elfsize, const struct smq_phy_page* pages, int numPages);
int fastrpc_kill(int pidA);

#endif // FASTRPC_LOADER_H
