#include <stdlib.h>
#include <string.h>
#include "uimage_rpm_smd.h"
#include "uimage_rpm_assert.h"
#include "uimage_rpm_log.h"
#include "HALsleep_hwio.h"
#include "HALhwio.h"
#include "qurt_atomic_ops.h"
#include "DalDevice.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"
#include "DDIHWIO.h"


#define SMD_PACKET_HEADER_SIZE      (5)
#define SMD_PACKET_HEADER_BYTE_SIZE (5 * sizeof(uint32))

#define ACTIVE_SET   0

#define MSG_KEY  0x2367736d /* "msg#" */
#define ERR_KEY  0x00727265 /* "err" */
#define REQ_KEY  0x00716572 /* "req" */


typedef enum
{
    SMD_SIG_ID_TX_DSR        = 0,   /* transmit side */
    SMD_SIG_ID_RX_DTR        = 0,   /* receive side */
    SMD_SIG_ID_TX_CTS        = 1,   /* transmit side */
    SMD_SIG_ID_RX_RTS        = 1,   /* receive side */
    SMD_SIG_ID_CD            = 2,
    SMD_SIG_ID_RI            = 3,
    SMD_SIG_ID_DATA_WRITTEN  = 4,
    SMD_SIG_ID_DATA_READ     = 5,
    SMD_SIG_ID_STATE_UPDATED = 6,

    SMD_NUM_IF_SIGS          = 8,   /* Must be multiple of 4 for alignment */
} smd_if_sig_ids_t;

/* New SMD channel structure created with all elements word aligned */
typedef struct
{
    uint32 stream_state;
    uint32 if_sigs[SMD_NUM_IF_SIGS];
    uint32 read_index;
    uint32 write_index;
} uImage_smd_shared_stream_info_algn_t;

typedef struct
{
    /*
     * The following data comes from SMD about the channel
     * Must be virtual address; otherwise, it causes a TLB exception
     */
    volatile uImage_smd_shared_stream_info_algn_t *tx_shared_info_ptr_algn;
    volatile uImage_smd_shared_stream_info_algn_t *rx_shared_info_ptr_algn;
    const uint32 fifo_sz;
    volatile uint32 *tx_shared_fifo;
    volatile uint32 *rx_shared_fifo;
} uImage_smd_shared_info_t;

/* 
 * Internal bits for messaging
 */
typedef struct
{
    uint32 service;
    uint32 len_with_header;
    uint32 msg_id;
    uint32 set;
    uint32 resource_type;
    uint32 resource_id;
    uint32 data_len;
    uint32 key;
    uint32 value_len;
    uint32 value;
} uImage_rpm_request_t;

typedef struct
{
    uint32 service;
    uint32 len_with_header;
    uint32 msg_id_key;
    uint32 msg_id_len;
    uint32 msg_id;
} uImage_rpm_ack_t;


static uImage_smd_shared_info_t uImage_rpm_smd_info =
{
    .fifo_sz = 1024,
};

/*
 * used for receiving ACK message from RPM
 */
static uImage_rpm_ack_t uImage_rpm_ack_msg;

/*
 * used for sending request message to RPM
 */
static uImage_rpm_request_t uImage_rpm_req_msg =
{
    .service         = REQ_KEY,
    .len_with_header = 32,
    .set             = ACTIVE_SET,
    .data_len        = 12,
    .value_len       = 4,
};

/*******************************************************************************
 *
 * uImage_rpm_smd_init
 *
 * This function is used to initialize SMD shared info.
 *
 */
void uImage_rpm_smd_init(void)
{
    DalDeviceHandle* handle = NULL;
    uint8 *msg_ram_base     = NULL;
    DALResult result;

    result = DAL_DeviceAttach(DALDEVICEID_HWIO, &handle);

    UIMAGE_RPM_ASSERT((result == DAL_SUCCESS) && (handle != NULL), "failed to get DAL device handle");

    /*
     * Get the virtual address of MSG RAM base, which is mapped to 0xFC428000
     */
    result = DalHWIO_MapRegion(handle, "RPM_SS_MSG_RAM_START_ADDRESS", &msg_ram_base);

    UIMAGE_RPM_ASSERT(result == DAL_SUCCESS, "failed to get MSG RAM vaddr");

    /*
     * Calculate the virtual addresses mapped to
     *
     *   0xFC429400 (0xFC428000 + 0x1400)
     *   0xFC42942C (0xFC428000 + 0x142C)
     *   0xFC429600 (0xFC428000 + 0x1600)
     *   0xFC429A00 (0xFC428000 + 0x1A00)
     */
    uImage_rpm_smd_info.tx_shared_info_ptr_algn = (uImage_smd_shared_stream_info_algn_t *)(msg_ram_base + 0x1400);
    uImage_rpm_smd_info.rx_shared_info_ptr_algn = (uImage_smd_shared_stream_info_algn_t *)(msg_ram_base + 0x142C);
    uImage_rpm_smd_info.tx_shared_fifo          = (uint32 *)(msg_ram_base + 0x1600);
    uImage_rpm_smd_info.rx_shared_fifo          = (uint32 *)(msg_ram_base + 0x1A00);

    UIMAGE_RPM_LOG(0, "smd_init_done", NULL);
}

/*******************************************************************************
 *
 * uImage_smd_4B_aligned_copy
 *
 * This function is used to access to Message RAM.
 * Message RAM only allows 4-byte aligned access.
 *
 */
static void uImage_smd_4B_aligned_copy(void *dest, const void *src, unsigned int size)
{
    volatile uint32 *src_word = (uint32 *)src;
    volatile uint32 *dst_word = (uint32 *)dest;

    /* When accessing RPM MSG RAM, ensure that both src and dest are 
     * word-aligned (4 bytes), and the size is a multiple of words.
     */
    UIMAGE_RPM_ASSERT(((uint32)src & 0x3) == 0, "not word-aligned");
    UIMAGE_RPM_ASSERT(((uint32)dest & 0x3) == 0, "not word-aligned");
    UIMAGE_RPM_ASSERT((size & 0x3) == 0, "not word-aligned");

    while(size > 0)
    {
        *dst_word = *src_word;
        dst_word++;
        src_word++;
        size -= 4;
    }
}

/*******************************************************************************
 *
 * circular_write_memcpy
 *
 * This function is used to write into msg RAM (FIFO) from specified
 * index. This is used to transmit both the packet header as well as 
 * the message.
 *
 *   write_idx:  Indicates where in the FIFO to start writing (offset)
 *   src:        Location to be read from
 *   count:      Message length
 *
 */
static uint32 circular_write_memcpy(uint32 write_idx, const uint8 *src, uint32 count)
{
    uint8 *tx_fifo = (uint8 *)uImage_rpm_smd_info.tx_shared_fifo;
    const uint32 fifo_sz = uImage_rpm_smd_info.fifo_sz;

    if(write_idx + count > fifo_sz)
    {
        /* must split write of count - write bytes to end of tx_fifo first */
        uint32 bytes = fifo_sz - write_idx;

        uImage_smd_4B_aligned_copy(tx_fifo + write_idx, src, bytes);

        src   += bytes;
        count -= bytes;
        write_idx = 0;
    }

    uImage_smd_4B_aligned_copy(tx_fifo + write_idx, src, count);

    write_idx += count;

    return (write_idx == fifo_sz) ? 0 : write_idx;
}

/*******************************************************************************
 *
 * circular_read_memcpy
 *
 * This function is used to read from msg RAM (FIFO) from specified index
 *
 *   dst:        Address to write into
 *   count:      Message length
 *   read_idx:   Indicates where in the FIFO to start reading (offset)
 *
 */
static uint32 circular_read_memcpy(uint8 *dst, uint32 count, uint32 read_idx)
{
    uint8 *rx_fifo = (uint8 *)uImage_rpm_smd_info.rx_shared_fifo;
    const uint32 fifo_sz = uImage_rpm_smd_info.fifo_sz;

    if(read_idx + count > fifo_sz)
    {
        /* must split read of count - read bytes from end of rx_fifo first */
        uint32 bytes = fifo_sz - read_idx;

        uImage_smd_4B_aligned_copy(dst, rx_fifo + read_idx, bytes);

        dst   += bytes;
        count -= bytes;
        read_idx = 0;
    }

    uImage_smd_4B_aligned_copy(dst, rx_fifo + read_idx, count);

    read_idx += count;

    return (read_idx == fifo_sz) ? 0 : read_idx;
}

/******************************************************************************
 *
 * wait_for_room
 *
 * This function is used to wait for room in SMD TX FIFO
 *
 *   bytes_required:  required room in bytes
 *
 */
static uint32 wait_for_room(uint32 bytes_required)
{
    uint32 byte_count, write_index, read_index;
    volatile uImage_smd_shared_stream_info_algn_t *tx_info;

    tx_info = uImage_rpm_smd_info.tx_shared_info_ptr_algn;

    do
    {
        write_index = tx_info->write_index;
        UIMAGE_RPM_ASSERT(write_index < uImage_rpm_smd_info.fifo_sz, "index out of TX FIFO");

        read_index = tx_info->read_index;
        UIMAGE_RPM_ASSERT(read_index < uImage_rpm_smd_info.fifo_sz, "index out of TX FIFO");

        /*
         * compute bytes used in buffer
         */
        byte_count = read_index - write_index - 4;

        if(read_index <= write_index)
        {
            byte_count += uImage_rpm_smd_info.fifo_sz;
        }
    }
    while(byte_count < bytes_required);

    return byte_count;
}

/*******************************************************************************
 *
 * wait_for_data
 *
 * This function is used to wait until data is available
 *
 *   bytes_expected:      expected data in bytes
 *   exit_with_no_data:   a flag to exit immidiately when no data is available
 *
 */
static uint32 wait_for_data(uint32 bytes_expected, DALBOOL exit_with_no_data)
{
    uint32 byte_count, write_index, read_index;
    volatile uImage_smd_shared_stream_info_algn_t *rx_info;

    rx_info = uImage_rpm_smd_info.rx_shared_info_ptr_algn;

    do
    {
        read_index = rx_info->read_index;
        UIMAGE_RPM_ASSERT(read_index < uImage_rpm_smd_info.fifo_sz, "index out of RX FIFO");

        write_index = rx_info->write_index;
        UIMAGE_RPM_ASSERT(write_index < uImage_rpm_smd_info.fifo_sz, "index out of RX FIFO");

        byte_count = write_index - read_index;

        if(write_index < read_index)
        {
            /*
             * FIFO wrapped
             */
            byte_count += uImage_rpm_smd_info.fifo_sz;
        }
        else if((exit_with_no_data) && (0 == byte_count))
        {
            break;
        }
    }
    while(byte_count < bytes_expected);

    return byte_count;
}

/*******************************************************************************
 *
 * uImage_rpm_sendMessage
 *
 * This function is essentially a very hacked up smdl_write().
 *  - For any clarification, please see that function.
 */
void uImage_rpm_sendMessage(uint32 msg_id, const uImage_rpm_resource_info_t *resource_info)
{
    uint32 packet_header[SMD_PACKET_HEADER_SIZE] = {0};
    volatile uImage_smd_shared_stream_info_algn_t *tx_info;
    volatile uint32 tmp;

    uImage_rpm_req_msg.msg_id        = msg_id;
    uImage_rpm_req_msg.resource_type = resource_info->resource_type;
    uImage_rpm_req_msg.resource_id   = resource_info->resource_id;
    uImage_rpm_req_msg.key           = resource_info->resource_key;
    uImage_rpm_req_msg.value         = resource_info->resource_value;

    UIMAGE_RPM_LOG(4, "send_msg (msg_id:%d) (type:0x%08X) (id:%d) (value:%d)",
                   uImage_rpm_req_msg.msg_id,
                   uImage_rpm_req_msg.resource_type,
                   uImage_rpm_req_msg.resource_id,
                   uImage_rpm_req_msg.value);

    packet_header[0] = sizeof(uImage_rpm_request_t);

    tx_info = uImage_rpm_smd_info.tx_shared_info_ptr_algn;

    /*
     * Using the SMD packet mode protocol
     * - wait for room to write our data.
     */
    wait_for_room(sizeof(uImage_rpm_request_t) + sizeof(packet_header));

    tmp = tx_info->write_index;
    tmp = circular_write_memcpy(tmp, (uint8 *)packet_header, sizeof(packet_header));
    tmp = circular_write_memcpy(tmp, (uint8 *)&uImage_rpm_req_msg, sizeof(uImage_rpm_request_t));

    tx_info->write_index = tmp;
    tx_info->if_sigs[SMD_SIG_ID_DATA_WRITTEN] = 1;

    /*
     * Read back the Data to "guarantee" flush
     */
    tmp = tx_info->if_sigs[SMD_SIG_ID_DATA_READ];
    tmp = tx_info->if_sigs[SMD_SIG_ID_DATA_WRITTEN];
    tmp = tx_info->if_sigs[SMD_SIG_ID_STATE_UPDATED];

    qurt_atomic_barrier();

    /*
     * Signal LPASS SMD IRQ to RPM
     *
     * Interrupt Name |   Subsystem Port   |Destination Port  |Polarity|Trigger|   Source
     * ---------------|--------------------|------------------|--------|-------|-----------
     * q6ss_irq_out[0]|lpass_irq_out_rpm[0]|rpm_interrupts[20]|  High  |  Edge |qdsp6ss_csr
     */
    HWIO_OUT(LPASS_QDSP6SS_IPC, 0x1);

    UIMAGE_RPM_LOG(0, "send_msg_done", NULL);
}

/*******************************************************************************
 *
 * uImage_rpm_readAck
 *
 * This function is essentially a *very* hacked up smdl_read()
 *  - For any clarification, please see that function.
 */
DALBOOL uImage_rpm_readAck(uint32 msg_id, DALBOOL clear_nas)
{
    DALBOOL ret = TRUE;

    /*
     * First wait until we have data
     */
    if(0 == wait_for_data(4, clear_nas))
    {
        /*
         * If there is nothing to read, we should be clearing out NAS Acks
         * and be done
         */
        ret = FALSE;
    }
    else
    {
        volatile uImage_smd_shared_stream_info_algn_t *rx_info;
        uint32 byte_count, read_index, packet_len;

        rx_info = uImage_rpm_smd_info.rx_shared_info_ptr_algn;

        /*
         * Next, decode the packet length and wait for the whole packet
         * to be written.
         */
        packet_len = *((uImage_rpm_smd_info.rx_shared_fifo) + (rx_info->read_index/4));
        UIMAGE_RPM_ASSERT(packet_len == sizeof(uImage_rpm_ack_t), "invalid packet");

        byte_count = wait_for_data(SMD_PACKET_HEADER_BYTE_SIZE + packet_len, FALSE);
        UIMAGE_RPM_ASSERT(byte_count >= packet_len, "invalid packet");

        /*
         * Finally, skip the header and continue with the packet parsing.
         */
        read_index = rx_info->read_index;
        read_index += SMD_PACKET_HEADER_BYTE_SIZE;
        if(read_index >= uImage_rpm_smd_info.fifo_sz)
        {
            read_index -= uImage_rpm_smd_info.fifo_sz;
        }

        /*
         * Pull the message out of message RAM.
         */
        read_index = circular_read_memcpy((uint8 *)&uImage_rpm_ack_msg, packet_len, read_index);

        /* Complete the SMD read handshaking. */
        rx_info->read_index = read_index;

        qurt_atomic_barrier();

        /*
         * Signal LPASS SMD IRQ to RPM
         *
         * Interrupt Name |   Subsystem Port   |Destination Port  |Polarity|Trigger|   Source
         * ---------------|--------------------|------------------|--------|-------|-----------
         * q6ss_irq_out[0]|lpass_irq_out_rpm[0]|rpm_interrupts[20]|  High  |  Edge |qdsp6ss_csr
         */
        HWIO_OUT(LPASS_QDSP6SS_IPC, 0x1);

        /*
         * Make sure this read isn't for clearing NAS Acks
         */
        if(FALSE == clear_nas)
        {
            /*
             * Now ensure the contents of the ack were as expected.
             */
            UIMAGE_RPM_ASSERT(uImage_rpm_ack_msg.service    == REQ_KEY, "unexpected ack");
            UIMAGE_RPM_ASSERT(uImage_rpm_ack_msg.msg_id_key == MSG_KEY, "unexpected ack");
            UIMAGE_RPM_ASSERT(uImage_rpm_ack_msg.msg_id_len == sizeof(uint32), "unexpected ack");

            if(uImage_rpm_ack_msg.msg_id == msg_id)
            {
                UIMAGE_RPM_LOG(1, "got_ack (msg_id:%d)", uImage_rpm_ack_msg.msg_id);
            }
            else
            {
                /*
                 * Return FALSE rather than abort when the msg ID is not the one we are waiting for.
                 *
                 * During bringup, we fixed an issue of matching wrong ACKs by using different message IDs
                 * for DDR-ON/DDR-OFF requests.
                 * But we observed the case that ADSP received DDR-OFF ACKs just after sending DDR-ON requests,
                 * causing message ID mismatch and making ADSP aborted.
                 * To resolve the race condition, allow ACKs with unexpected msg ID and return FALSE
                 * so that we can robustly receive the ACK with the expected one.
                 */
                ret = FALSE;
            }
        }
    }

    return ret;
}

