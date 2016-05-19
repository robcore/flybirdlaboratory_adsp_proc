#ifndef FASTRPC_KPOWER_H
#define FASTRPC_KPOWER_H

#ifdef __cplusplus
extern "C" {
#endif

struct adsp_power {
  uint32 client;
};

int power_ctor(void* ctx, void* data);
void power_dtor(void* data);
int power_req(struct adsp_power* me, int clock, int bus, int latency);
int power_query(int* clock_max, int* bus_max);

#ifdef __cplusplus
}
#endif
#endif //FASTRPC_KPOWER_H

