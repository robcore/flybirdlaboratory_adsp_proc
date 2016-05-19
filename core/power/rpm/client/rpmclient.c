/*===========================================================================

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#ifdef _MSC_VER
    // enable memory leak detection under msvc
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
#endif

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "inmap.h"
#include "npa_resource.h"

#include "rpmclient.h"
#include "rpm_mq.h"
#include "rpm_resource.h"
#include "rpm_wire.h"

#include "DALSys.h"
#include "smd_lite.h"
#include "err.h"
#include "ULogFront.h"
#include "CoreVerify.h"

typedef struct
{
    inmap_link_t         link;
    unsigned             service_id;
    rpmclient_service_cb cb;
    void                *context;
} rpmclient_service_t;

static struct rpm_s
{
    unsigned          rpmclient_initialized;
    rpm_mq_t         *rpm_mq;

    unsigned          num_resources;
    rpm_resource_t   *resources;

    inmap_t          *services;

    smdl_handle_type  smd_port;
    kvp_t            *rx_kvp;
    unsigned          num_resources_dirty[RPM_NUM_SETS];
} rpm;

DALSYSSyncHandle rpm_lock;
ULogHandle       rpm_log;

static const char *rpm_set_names[RPM_NUM_SETS] =
{
  "active",
  "sleep",
  "next active"
};

void (*rpm_fifo_full_handler)(rpm_mq_t *, unsigned);

rpm_resource_t *rpm_find_resource(rpm_resource_type resource, unsigned id)
{
    uint64_t resource_id = (((uint64_t)resource) << 32) | id;
    unsigned low = 0, high = rpm.num_resources - 1;

    if(!rpm.num_resources)
        return NULL;

    while(high < rpm.num_resources && high >= low)
    {
        unsigned mid = (low + high) / 2;
        uint64_t current_id = rpm.resources[mid].resource_identifier;

        if(current_id < resource_id)
            low = mid + 1;
        else if(current_id > resource_id)
            high = mid - 1;
        else
            return &rpm.resources[mid];
    }

    return NULL;
}

rpm_resource_t *rpm_add_resource(rpm_resource_type resource, unsigned id)
{
    unsigned i, old_num_resources;
    uint64_t resource_id = (((uint64_t)resource) << 32) | id;

    old_num_resources = rpm.num_resources;
    rpm.num_resources++;
    rpm.resources = realloc(rpm.resources, rpm.num_resources * sizeof(rpm_resource_t));
    CORE_VERIFY(rpm.resources);

    for(i = 0; i < old_num_resources; ++i)
    {
        if(rpm.resources[i].resource_identifier > resource_id)
        {
            // Found entries that belong after us.  Move them and insert here.
            memmove(&rpm.resources[i+1], &rpm.resources[i], (old_num_resources - i) * sizeof(rpm_resource_t));

            break;
        }
    }

    // Must be largest in the list; insert at the end.
    rpm_resource_init(&rpm.resources[i], resource, id);

    // Refactor the queues to update any resource pointers in pending messages
    rpm_mq_update_resource_pointers(rpm.rpm_mq);

    return &rpm.resources[i];
}

unsigned rpm_get_request_size(rpm_set_type set, rpm_resource_type resource, unsigned id)
{
    rpm_resource_t *resource_data = rpm_find_resource(resource, id);
    if(!resource_data)
        return 0;

    return rpm_resource_get_request_size(set, resource_data);
}

unsigned rpm_post_request(rpm_set_type set, rpm_resource_type resource, unsigned id, kvp_t *kvps)
{
    rpm_resource_t *resource_data;
    unsigned        msg_id = 0;

    if(set >= RPM_NUM_SETS)
        return 0;

    DALSYS_SyncEnter(rpm_lock);

    ULOG_RT_PRINTF_3(rpm_log, "rpm_post_request (resource: 0x%08x) (id: 0x%08x) (set: \"%s\")", resource, id, rpm_set_names[set]);

    resource_data = rpm_find_resource(resource, id);
    if(!resource_data)
        resource_data = rpm_add_resource(resource, id);

    rpm_resource_update(resource_data, set, kvps);

    if((RPM_ACTIVE_SET == set) && resource_data->dirty[set])
    {
        msg_id = rpm_mq_put(rpm.rpm_mq, set, resource, id, resource_data);
        ULOG_RT_PRINTF_3(rpm_log, "\trpm_posted (resource: 0x%08x) (id: 0x%08x) (msg_id: 0x%08x)", resource, id, msg_id);
    }

    DALSYS_SyncLeave(rpm_lock);

    return msg_id;
}

void rpm_barrier(unsigned message_id)
{
    DALSYS_SyncEnter(rpm_lock);

    ULOG_RT_PRINTF_1(rpm_log, "rpm_barrier (msg_id: 0x%08x)", message_id);
    rpm_mq_wait(rpm.rpm_mq, message_id);
    ULOG_RT_PRINTF_1(rpm_log, "\trpm_barrier_return (msg_id: 0x%08x)", message_id);

    DALSYS_SyncLeave(rpm_lock);
}

unsigned rpm_force_sync(rpm_set_type set)
{
    unsigned last_msg_id = 0;

    if(set >= RPM_NUM_SETS)
        return 0;

    DALSYS_SyncEnter(rpm_lock);

    ULOG_RT_PRINTF_4(rpm_log, "rpm_force_sync (set: %d) (dirty: %d,%d,%d)", set, rpm.num_resources_dirty[0], rpm.num_resources_dirty[1], rpm.num_resources_dirty[2]);

    // if the set has been dirty, do sync
    if(rpm.num_resources_dirty[set])
    {
        unsigned i;
        rpm_resource_t *resource = rpm.resources;

        for(i = 0; i < rpm.num_resources; ++resource, ++i)
        {
            if(resource->dirty[set])
            {
                rpm_resource_type type = (rpm_resource_type)(resource->resource_identifier >> 32);
                unsigned          id   = resource->resource_identifier & 0xFFFFFFFFU;
                unsigned          msg_id;

                ULOG_RT_PRINTF_2(rpm_log, "\trpm_flushing (resource: 0x%08x) (id: 0x%08x)", type, id);
                msg_id = rpm_mq_put(rpm.rpm_mq, set, type, id, resource);
                if(msg_id)
                    last_msg_id = msg_id;
            }
        }
    }

    CORE_VERIFY(!(rpm.num_resources_dirty[set]));

    ULOG_RT_PRINTF_2(rpm_log, "rpm_flushed (set: %d) (msg_id: 0x%08x)", set, last_msg_id);

    DALSYS_SyncLeave(rpm_lock);

    return last_msg_id;
}

void rpmclient_register_handler(rpm_service_type service, rpmclient_service_cb cb, void *context)
{
    rpmclient_service_t *service_obj;

    DALSYS_SyncEnter(rpm_lock);

    service_obj = (rpmclient_service_t *)malloc(sizeof(rpmclient_service_t));
    CORE_VERIFY_PTR(service_obj);

    service_obj->service_id = service;
    service_obj->cb         = cb;
    service_obj->context    = context;
    inmap_insert(rpm.services, service_obj);

    DALSYS_SyncLeave(rpm_lock);
}

void rpmclient_put(rpm_service_type service, smdl_iovec_type *data)
{
    unsigned        header_data[2];
    smdl_iovec_type header;

    header.next = data;
    header.length = sizeof(header_data);
    header.buffer = header_data;

    DALSYS_SyncEnter(rpm_lock);

    header_data[0] = service;

    header_data[1] = 0;
    while(data)
    {
        header_data[1] += data->length;
        data = data->next;
    }

    while(smdl_tx_peek(rpm.smd_port) < (header_data[1] + sizeof(header_data)))
    {
        rpm_fifo_full_handler(rpm.rpm_mq, header_data[1] + sizeof(header_data));
    }

    smdl_writev(rpm.smd_port,
                &header,
                SMDL_WRITE_FLAGS_NONE);

    DALSYS_SyncLeave(rpm_lock);
}

void rpmclient_smdl_isr(smdl_handle_type port, smdl_event_type event, void *unused)
{
    char          rx_buffer[64];
    const char   *msg;
    int           to_read, read;
    unsigned      service_id, length;
    rpmclient_service_t *service;

    if(port != rpm.smd_port || SMDL_EVENT_READ != event)
        return;

    DALSYS_SyncEnter(rpm_lock);

    while((to_read = smdl_rx_peek(rpm.smd_port)) != 0)
    {
        if(to_read > sizeof(rx_buffer))
            ERR_FATAL("Need larger RPM rx buffer.", to_read, sizeof(rx_buffer), 0);

        read = smdl_read(rpm.smd_port,
                         sizeof(rx_buffer),
                         rx_buffer,
                         SMDL_READ_FLAGS_NONE);
        if(read < 0)
        {
            ERR_FATAL("smdl_read failed", to_read, read, sizeof(rx_buffer));
        }

        kvp_swapbuffer(rpm.rx_kvp, rx_buffer, to_read);
        if(!kvp_get(rpm.rx_kvp, &service_id, &length, &msg))
            ERR_FATAL("Malformed RPM message.", 0, 0, 0); // FIXME: just log/drop

        service = inmap_search(rpm.services, service_id);
        if(!service)
            ERR_FATAL("RPM message to unknown service.", 0, 0, 0); // FIXME: just log/drop

        kvp_swapbuffer(rpm.rx_kvp, msg, length);
        service->cb(rpm.rx_kvp, service->context);
    }

    DALSYS_SyncLeave(rpm_lock);
}

void rpm_churn_queue(unsigned message_id)
{
    DALSYS_SyncEnter(rpm_lock);

    ULOG_RT_PRINTF_1(rpm_log, "rpm_churn_queue (msg_id: 0x%08x)", message_id);

    while(rpm_mq_is_in_flight(rpm.rpm_mq, message_id))
    {
        ULOG_RT_PRINTF_1(rpm_log, "\tchurning (msg_id: 0x%08x)", message_id);
        rpmclient_smdl_isr(rpm.smd_port, SMDL_EVENT_READ, 0);
    }

    ULOG_RT_PRINTF_1(rpm_log, "rpm_churning_complete (msg_id: 0x%08x)", message_id);

    DALSYS_SyncLeave(rpm_lock);
}

void rpmclient_init(void)
{
    static const unsigned REQ_KEY  = 0x00716572;

    if(rpm.rpmclient_initialized)
        return;
    rpm.rpmclient_initialized = 1;
    rpm_fifo_full_handler = &rpm_mq_force_churn_cb;


    if(DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_RPM_SYNC_TYPE, &rpm_lock, 0))
        ERR_FATAL("Couldn't create RPM lock.", 0, 0, 0);

    CORE_DAL_VERIFY(ULogFront_RealTimeInit(&rpm_log,
                                           "RPMMasterLog",
                                           8192,
                                           ULOG_MEMORY_LOCAL,
                                           ULOG_RPM_LOCK_TYPE));

    rpm.rpm_mq = rpm_mq_create();

    rpm.services = inmap_create(offsetof(rpmclient_service_t, link), offsetof(rpmclient_service_t, service_id));
    rpmclient_register_handler((rpm_service_type)REQ_KEY, (rpmclient_service_cb)rpm_wire_recv, rpm.rpm_mq);

    rpm.rx_kvp = kvp_create(0);

    if(!is_standalone())
    {
        //make sure RPM has opened the port
        while(!smd_is_port_open("rpm_requests", RPM_EDGE_TYPE));
    }

    rpm.smd_port = smdl_open("rpm_requests",
                             RPM_EDGE_TYPE,
                             SMDL_OPEN_FLAGS_MODE_PACKET | SMDL_OPEN_FLAGS_PRIORITY_HIGH,
                             1024,
                             rpmclient_smdl_isr,
                             NULL);

    if(!rpm.smd_port)
        ERR_FATAL("Failed to establish communication with RPM.", (int)rpm.smd_port, 0, 0);
    else
        ULOG_RT_PRINTF_0(rpm_log, "rpm_smd_up");

    npa_define_marker("/init/rpm");
}

bool rpm_is_up(void)
{
    return (smdl_sig_get(rpm.smd_port, SMDL_SIG_CD) > 0);
}

bool rpm_is_mq_empty(void)
{
    return rpm_mq_check_empty(rpm.rpm_mq);
}

void rpm_signal_aborted_sleep(unsigned asserted)
{
    smdl_sig_set(rpm.smd_port, SMDL_SIG_RI, asserted);
}

void rpm_preallocate_resource_kvp(rpm_resource_type resource, unsigned id, unsigned key, unsigned expected_length)
{
    rpm_resource_t *resource_data = rpm_find_resource(resource, id);
    if(!resource_data)
        resource_data = rpm_add_resource(resource, id);

    rpm_resource_preallocate(resource_data, key, expected_length);
}

void rpm_clear_pending_acks(void)
{
    rpm_mq_retire_acks(rpm.rpm_mq);
}

void rpm_update_num_dirty(rpm_set_type set, bool pre_dirty, bool post_dirty)
{
    if(pre_dirty != post_dirty)
    {
       if(!post_dirty)
       {
           CORE_VERIFY(rpm.num_resources_dirty[set] > 0);
       }
       rpm.num_resources_dirty[set] += (post_dirty) ? 1 : -1; 
    }
}

#if 0 // used for testing on new targets
void rpm_test_task(unsigned long int unused_param)
{
  unsigned msg_id, data;
  kvp_t   *test_data = kvp_create(0);

  data = 0xf005ba11;
  kvp_put(test_data, 0x0ddba11, 4, (char *)&data);

  data = 0xfeeb1e;
  kvp_put(test_data, 0xfab1e5, 4, (char *)&data);

  msg_id = rpm_post_request(RPM_ACTIVE_SET, RPM_TEST_REQ, 0, test_data);
  rpm_barrier(msg_id);

  //while(1);
  // Call this when I'm started, I guess.  For now I'm going to ignore this
  // part since I just need to do some one-off testing.
  //rcinit_handshake_startup();
}
#endif

