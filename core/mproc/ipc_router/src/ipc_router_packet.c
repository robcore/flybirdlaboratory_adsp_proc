/*===========================================================================

                    I P C    R O U T E R   P A C K E T

        This file provides an abstraction to the packet buffer manager

  ---------------------------------------------------------------------------
  Copyright (c) 2012-2013 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/mproc/ipc_router/src/ipc_router_packet.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
==========================================================================*/

/*===========================================================================
                          INCLUDE FILES
===========================================================================*/
#include "ipc_router_os.h"
#include "ipc_router_packet.h"

/* Packets will be at least this big */
#define IPC_ROUTER_PACKET_DEFAULT_SIZE (128)

/* Allow enough room to hold the largest header */
#define IPC_ROUTER_PACKET_DEFAULT_HEADROOM (32)

/* Allow enough room to adjust the header from smallest to largest */
#define IPC_ROUTER_PACKET_MIN_HEADROOM (16)

/* Packets are always aligned so the sizes should be a multiple of 4 */
#define WORD_ALIGNED(size) (((size) + 3) & (~3UL))

#define IPC_ROUTER_MIN(a,b) ((a) < (b) ? (a) : (b))

#define IPC_ROUTER_PACKET_MAGIC_START 0xdeadbeef

/*===========================================================================
                  CONSTANT / MACRO DACLARATIONS
===========================================================================*/

/* Notes: Unless something changes in smd_lite, (ipc_router_packet_type *) 
 * can be cast as (smdl_iovec_type *) as the first three members are the
 * same. Obviously the other way around is not possible!
 */
struct ipc_router_packet_s
{
  ipc_router_packet_type *next;
  uint32                 used;
  void                   *data_ptr;
  void                   *base_ptr;
  size_t                 size;
  ipc_router_packet_free_cb free_cb;
  void                      *cookie;
  ipc_router_packet_type *pkt_next;
  uint32                 magic_start;
};

/*===========================================================================
                         MODULE GLOBALS
===========================================================================*/
static int ipc_router_packet_corruption_count = 0;

/*===========================================================================
                        LOCAL FUNCTIONS
===========================================================================*/

static ipc_router_packet_type *ipc_router_packet_alloc(uint32 headroom, uint32 size)
{
  ipc_router_packet_type *ret = NULL;

  size = WORD_ALIGNED(size + headroom);

  ret = ipc_router_os_malloc(sizeof(ipc_router_packet_type) + size);
  if(!ret)
    return NULL;
  ret->next = NULL;
  ret->free_cb = NULL;
  ret->used = 0;
  ret->size = size - headroom;
  ret->base_ptr = (uint8 *)ret + sizeof(ipc_router_packet_type);
  ret->data_ptr = (uint8 *)ret->base_ptr + headroom;
  ret->pkt_next = NULL;
  ret->magic_start = IPC_ROUTER_PACKET_MAGIC_START;
  return ret;
}

static void ipc_router_packet_release(ipc_router_packet_type *pkt)
{
  if(pkt)
  {
    if(pkt->magic_start != IPC_ROUTER_PACKET_MAGIC_START)
    {
      ipc_router_packet_corruption_count++;
    }
    if(pkt->free_cb)
    {
      pkt->free_cb(pkt->base_ptr, pkt->cookie);
    }
    ipc_router_os_free(pkt);
  }
}

/*===========================================================================
                        EXPORTED FUNCTIONS
===========================================================================*/

void ipc_router_packet_init(void)
{
  /* Nothing to be initialized */
}

ipc_router_packet_type *ipc_router_packet_new(void)
{
  return ipc_router_packet_alloc(IPC_ROUTER_PACKET_MIN_HEADROOM, IPC_ROUTER_PACKET_DEFAULT_SIZE);
}

void ipc_router_packet_free(ipc_router_packet_type **pkt)
{
  ipc_router_packet_type *p;
  if(!pkt)
  {
    return;
  }
  p = *pkt;
  while(p)
  {
    ipc_router_packet_type *to_free = p;
    p = p->next;
    ipc_router_packet_release(to_free);
  }
  *pkt =  NULL;
}

ipc_router_packet_type *ipc_router_packet_new_headroom(uint32 headroom)
{
  return ipc_router_packet_alloc(headroom, IPC_ROUTER_PACKET_DEFAULT_SIZE);
}

ipc_router_packet_type *ipc_router_packet_attach(void *buf, uint32 size, ipc_router_packet_free_cb free_cb, void *cookie)
{
  ipc_router_packet_type *ret;

  if(!buf || !size || !free_cb)
  {
    return NULL;
  }

  ret = ipc_router_packet_alloc(0,0);

  if(ret)
  {
    ret->base_ptr = ret->data_ptr = buf;
    ret->used = ret->size = size;
    ret->free_cb = free_cb;
    ret->cookie = cookie;
  }
  return ret;
}

/*===========================================================================
FUNCTION      ipc_router_packet_expand

DESCRIPTION   Expands a packet to the required size.
              (If the packet is already larger than the required bytes, then
              it wont be modified).

              pkt   - The packet to expand.
              bytes - The size of the expanded (final) packet.

RETURN VALUE  The total size of the returned packet.

SIDE EFFECTS  Input packet will be modified.
===========================================================================*/
uint32 ipc_router_packet_expand(ipc_router_packet_type **pkt, uint32 bytes)
{
  ipc_router_packet_type *in_pkt = NULL;

  if(!pkt)
  {
    return 0;
  }

  in_pkt = *pkt;
  if(in_pkt && in_pkt->size >= bytes)
  {
    ipc_router_packet_free(&in_pkt->next);
    in_pkt->used = bytes;
    return bytes;
  }
  in_pkt = ipc_router_packet_alloc(IPC_ROUTER_PACKET_MIN_HEADROOM, bytes);
  if(!in_pkt)
  {
    return 0;
  }
  in_pkt->used = bytes;
  ipc_router_packet_free(pkt);
  *pkt = in_pkt;
  return bytes;
}

uint32 ipc_router_packet_copy_header(ipc_router_packet_type **pkt, void *buf, uint32 len)
{
  ipc_router_packet_type *p;

  if(!pkt || !buf || !len)
  {
    return 0;
  }

  p = *pkt;
  if(p)
  {
    uint32 headroom = (uint8 *)p->data_ptr - (uint8 *)p->base_ptr;

    /* See if we can adjust the new data in the existing packet's headroom */
    if(headroom >= len)
    {
      p->data_ptr = (uint8 *)p->data_ptr - len;
      p->size += len;
      p->used += len;
      ipc_router_os_mem_copy(p->data_ptr, len, buf, len);
      return len;
    }
  }

  p = ipc_router_packet_alloc(0, len);
  if(!p)
  {
    return 0;
  }

  ipc_router_os_mem_copy(p->data_ptr, len, buf, len);
  p->used = len;
  p->next = *pkt;
  *pkt = p;

  return len;
}

uint32 ipc_router_packet_copy_payload(ipc_router_packet_type **pkt, void *_buf, uint32 len)
{
  uint8 *buf = (uint8 *)_buf;
  ipc_router_packet_type *p = NULL, *last;
  uint32 ret = len, avail_space = 0;

  if(!pkt || !buf || !len)
  {
    return 0;
  }
  last = *pkt;
  if(last)
  {
    while(last->next != NULL)
    {
      last = last->next;
    }
    avail_space = last->size - last->used;
  }
  /* Pre-allocate to avoid touching existing packet before failure */
  if(avail_space < len)
  {
    p = ipc_router_packet_alloc(0, len - avail_space);
    if(!p)
    {
      return 0;
    }
  }

  if(last)
  {
    uint32 to_put = IPC_ROUTER_MIN(avail_space, len);
    ipc_router_os_mem_copy((uint8 *)last->data_ptr + last->used, to_put, buf, to_put);
    len -= to_put;
    buf += to_put;
    last->used += to_put;
    last->next = p;
  }
  else
  {
    *pkt = p;
  }
  if(p)
  {
    ipc_router_os_mem_copy(p->data_ptr, len, buf, len);
    p->used = len;
  }

  return ret;
}

uint32 ipc_router_packet_length(ipc_router_packet_type *pkt)
{
  uint32 len = 0;
  while(pkt)
  {
    len += pkt->used;
    pkt = pkt->next;
  }
  return len;
}

void *ipc_router_packet_peek(ipc_router_packet_type *pkt, uint32 len)
{
  return pkt && pkt->used >= len ? pkt->data_ptr : NULL;
}

void ipc_router_packet_trim(ipc_router_packet_type **pkt, uint32 len)
{
  ipc_router_packet_type *p;
  uint32 cur_pkt_size = 0;

  if(!pkt)
  {
    return;
  }

  if(len == 0)
  {
    ipc_router_packet_free(pkt);
    return;
  }

  p = *pkt;
  while(p)
  {
    cur_pkt_size += p->used;
    if(cur_pkt_size >= len)
    {
      p->used -= (cur_pkt_size - len);
      ipc_router_packet_free(&p->next);
      break;
    }
    p = p->next;
  }
}

/* Read len bytes from head  into buf and free the read buffers */
uint32 ipc_router_packet_read(ipc_router_packet_type **pkt, void *_buf, uint32 len)
{
  uint32 read_bytes = 0;
  uint8 *buf = (uint8 *)_buf;
  ipc_router_packet_type *p;

  if(!pkt || !buf || !len)
  {
    return 0;
  }

  p = *pkt;

  while(p && read_bytes < len)
  {
    uint32 to_read = IPC_ROUTER_MIN(len - read_bytes, p->used);
    ipc_router_packet_type *to_free = p;
    ipc_router_os_mem_copy(buf, to_read, p->data_ptr, to_read);
    p->used -= to_read;
    p->data_ptr = (uint8 *)p->data_ptr + to_read;
    read_bytes += to_read;
    buf += to_read;

    p = p->next;

    /* If this packet is empty free it, and set the new head */
    if(to_free->used == 0)
    {
      ipc_router_packet_release(to_free);
      *pkt = p;
    }
  }
  return read_bytes;
}

ipc_router_packet_type *ipc_router_packet_dup(ipc_router_packet_type *src)
{
  ipc_router_packet_type *ret = NULL, *s = NULL;
  uint32 len;
  uint8 *buf;

  if(!src)
  {
    return NULL;
  }

  len = ipc_router_packet_length(src);
  ret = ipc_router_packet_alloc(IPC_ROUTER_PACKET_DEFAULT_HEADROOM, len);
  if(!ret)
  {
    return NULL;
  }
  
  s = src;
  buf = ret->data_ptr;
  while(s)
  {
    ipc_router_os_mem_copy(buf, len, s->data_ptr, s->used);
    len -= s->used;
    buf += s->used;
    s = s->next;
  }
  return ret;
}

void ipc_router_packet_queue_init(ipc_router_packet_queue_type *queue)
{
  ipc_router_os_sem_init(&queue->lock);
  queue->head = queue->tail = NULL;
  queue->cnt = 0;
}

void ipc_router_packet_queue_deinit(ipc_router_packet_queue_type *queue)
{
  ipc_router_packet_type *pkt;
  ipc_router_os_sem_lock(&queue->lock);
  pkt = queue->head;
  while(pkt)
  {
    ipc_router_packet_type *to_free = pkt;
    pkt = pkt->pkt_next;
    ipc_router_packet_free(&to_free);
  }
  queue->head = queue->tail = NULL;
  ipc_router_os_sem_unlock(&queue->lock);
  ipc_router_os_sem_deinit(&queue->lock);
}

void ipc_router_packet_queue_put(ipc_router_packet_queue_type *queue, ipc_router_packet_type *pkt)
{
  if(!queue || !pkt)
  {
    return;
  }
  ipc_router_os_sem_lock(&queue->lock);
  pkt->pkt_next = NULL;
  if(!queue->tail)
  {
    queue->head = queue->tail = pkt;
  }
  else
  {
    queue->tail->pkt_next = pkt;
    queue->tail = pkt;
  }
  queue->cnt++;
  ipc_router_os_sem_unlock(&queue->lock);
}

ipc_router_packet_type *ipc_router_packet_queue_get(ipc_router_packet_queue_type *queue)
{
  ipc_router_packet_type *ret = NULL;

  if(!queue)
  {
    return NULL;
  }

  ipc_router_os_sem_lock(&queue->lock);
  if(queue->head)
  {
    ret = queue->head;
    queue->head = queue->head->pkt_next;
    ret->pkt_next = NULL;
    queue->cnt--;
    if(queue->cnt == 0)
    {
      queue->tail = NULL;
    }
  }
  ipc_router_os_sem_unlock(&queue->lock);
  return ret;
}

