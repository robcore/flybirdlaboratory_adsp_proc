#ifndef SBUF_H
#define SBUF_H

#include "AEEStdDef.h"
#include "AEEstd.h"
#include <string.h>

/**
 * lightweight serialize/deserialize buffer.

   For example

   struct sbuf;
   //initialize empty buffer;
   sbuf_init(&sbuf, 0, 0, 0);

   //fill it with data
   sbuf_align(&sbuf, 8);
   sbuf_write(&sbuf, ptr1, 10);
   sbuf_align(&sbuf, 8);
   sbuf_write(&sbuf, ptr2, 20);

   //allocate the memory needed
   mem = malloc(sbuf_needed(&sbuf));

   //initialize with the data
   sbuf_init(&sbuf, 0, mem, sbuf_needed(&sbuf));

   //fill it with data, since it has memory, it will actually copy
   sbuf_align(&sbuf, 8);
   sbuf_write(&sbuf, ptr1, 10);
   sbuf_align(&sbuf, 8);
   sbuf_write(&sbuf, ptr2, 20);

   See sbuf_q.h for more examples
 */


struct sbuf {
   uint8* buf;      //start of valid memory
   uint8* bufEnd;   //end of valid memory
   uint8* bufStart; //start with optinal offset from valid mem
   uint8* bufCur;   //current buffer, could be outside of valid range (greater then bufEnd)
};

static __inline void sbuf_init(struct sbuf* buf, int offset, uint8* data, int dataLen) {
   buf->buf = data;
   buf->bufStart = buf->bufCur = data - offset;
   buf->bufEnd = data + dataLen;
}

static __inline void sbuf_advance(struct sbuf* buf, int len) {
   buf->bufCur += len;
}

//needed for everything from the start (with the offset) to the end (past the current valid memory end)
static __inline int sbuf_needed(struct sbuf* buf) {
   return buf->bufCur - buf->bufStart;
}

//space left in buffer, a negative value indicates overflow
//a positive value includes the offset
static __inline int sbuf_left(struct sbuf* buf) {
   return buf->bufEnd - buf->bufCur;
}

static __inline uint8* sbuf_head(struct sbuf* buf) {
   return buf->bufCur;
}


//advances the head pointer so the "needed" is aligned to the align value
#define _SBUF_ALIGN(x, y) (((x) + ((y)-1)) & ~((y)-1))
static __inline void sbuf_align(struct sbuf* buf, uint32 align) {
   sbuf_advance(buf, _SBUF_ALIGN(sbuf_needed(buf), align) - sbuf_needed(buf));
}


static __inline void sbuf_write(struct sbuf* buf, uint8* src, int srcLen) {
   if(buf->bufCur + srcLen > buf->buf) {
      int writeLen;
      if(buf->bufCur < buf->buf) {
         int len = buf->buf - buf->bufCur;
         srcLen -= len;
         src += len;
         sbuf_advance(buf, len);
      }
      writeLen = STD_MIN(srcLen, sbuf_left(buf));
      if(writeLen > 0) {
         std_memsmove(buf->bufCur, buf->bufEnd - buf->bufCur, src, writeLen);
      }
   }
   sbuf_advance(buf, srcLen);
}

static __inline void sbuf_read(struct sbuf* buf, uint8* dst, int dstLen) {
   if(buf->bufCur + dstLen > buf->buf) {
      int readLen;
      if(buf->bufCur < buf->buf) {
         int len = buf->buf - buf->bufCur;
         dstLen -= len;
         dst += len;
         sbuf_advance(buf, len);
      }
      readLen = STD_MIN(dstLen, sbuf_left(buf));
      if(readLen > 0) {
         std_memsmove(dst, dstLen, buf->bufCur, readLen);
      }
   }
   sbuf_advance(buf, dstLen);
}

#endif
