/*============================================================================
  @file circular_buffer.c

  Circular buffer utility source file 

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
============================================================================*/

#include "circular_buffer.h"
#include "fixed_point.h"


/* round up to the nearest power of 2 */
/* we need at least one empty spot in the buffer */
static int32_t buffer_size(int32_t window_size)
{
  window_size |= window_size >> 1;
  window_size |= window_size >> 2;
  window_size |= window_size >> 4;
  window_size |= window_size >> 8;
  window_size |= window_size >> 16;
  window_size++;

  return window_size;
}

int32_t buffer_mem_req(int32_t window_size, int32_t cols)
{
  return matrix_mem_req(buffer_size(window_size), cols);
}

void buffer_reset(buffer_type *buffer, int32_t window_size, int32_t cols, void *mem)
{
  int32_t rows = buffer_size(window_size);

  matrix_reset(&buffer->data, rows, cols, mem);

  buffer->window_size = window_size;
  buffer->end   = 0;
  buffer->count = 0;
  matrix_zero(&buffer->data);
}

