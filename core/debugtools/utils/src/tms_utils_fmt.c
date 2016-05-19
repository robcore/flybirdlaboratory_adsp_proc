/** vi: tw=128 ts=3 sw=3 et
@file tms_utils_fmt.c
@brief This file contains the API for the TMS Utilities, API 0.2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2014 QUALCOMM Technologies Incorporated.
All rights reserved.
QUALCOMM Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/utils/src/tms_utils_fmt.c#2 $
$DateTime: 2014/11/11 13:24:18 $
$Change: 6933707 $
$Author: pwbldsvc $
===============================================================================*/
/*=============================================================================
QPSI Reviewed; Review required for signifigant changes including feature addition.
===============================================================================*/

#if !defined(TMS_UTILS_EXCLUDE_MSG_SWEVT)
#include "msg.h"
#endif

#if !defined(TMS_UTILS_EXCLUDE_TRACER_SWEVT)
#include "tracer.h"
#include "tms_utils_tracer_swe.h"
#endif

// Function must remain reentrant and not utilize NHLOS or external library calls which
// are not reentrant or potentially cause any type of NHLOS blocking to occur.

#include "tms_utils.h"

typedef union { uint32_t ul; int32_t l; } fmt32_t;

#define ULONG_BITS      32          // maximum buffer required to hold numeric template output

#define FIELD_FLAG_NONE   0
#define FIELD_FLAG_ZERO   1         // flag, zero pad
#define FIELD_FLAG_LNEG   2         // flag, left negative
#define FIELD_FLAG_LONG   4         // flag, format template indicates long value
#define FIELD_FLAG_SIGN   8         // flag, include sign

#define ASCII_NIL       '\0'        // ASCII NULL
#define ASCII_ZERO      '0'         // ASCII ZERO
#define ASCII_9         '9'         // ASCII
#define ASCII_SPACE     ' '         // ASCII SPACE
#define ASCII_SIGN      '-'         // ASCII
#define ASCII_PERCENT   '%'         // ASCII

#define ASCII_CAP_B     'B'         // ASCII
#define ASCII_CAP_C     'C'         // ASCII
#define ASCII_CAP_D     'D'         // ASCII
#define ASCII_CAP_L     'L'         // ASCII
#define ASCII_CAP_O     'O'         // ASCII
#define ASCII_CAP_S     'S'         // ASCII
#define ASCII_CAP_U     'U'         // ASCII
#define ASCII_CAP_X     'X'         // ASCII

#define ASCII_A         'a'         // ASCII
#define ASCII_D         'd'         // ASCII
#define ASCII_L         'l'         // ASCII
#define ASCII_X         'x'         // ASCII

static tms_chr* tms_utils_fmt_put_chr(tms_chr* out_p, const size_t out_buf_sz, const tms_chr chr)
{
   size_t sz = out_buf_sz;

   if (out_p && sz)
   {
      *out_p = chr;

      sz--;

      out_p++;
   }

   return out_p;
}

static tms_chr* tms_utils_fmt_put_chr_buf(tms_chr* out_p, const size_t out_buf_sz, tms_chr const* in_p)
{
   size_t sz = out_buf_sz;

   if (out_p && sz && in_p)
   {
      while (sz && ASCII_NIL != *in_p)
      {
         out_p = tms_utils_fmt_put_chr(out_p, sz--, *in_p++);
      }
   }

   return out_p;
}

static int32_t tms_utils_fmt_put(tms_chr* out_buf_p, const size_t out_buf_sz, tms_chr const* fmt_str, va_list argv)
{
   tms_chr* out_p = out_buf_p;

   // validate inputs

   if (out_buf_p && out_buf_sz && fmt_str)
   {
      // loop while room in out_p

      do
      {
         tms_chr chr_num[ULONG_BITS + 1];
         tms_chr fmt_chr, fmt_code;
         fmt32_t fmt_pad, fmt_fill;
         fmt32_t field_radix, field_width, field_flag, field_arg;

         fmt_chr = *fmt_str++;

         // end of fmt_str check

         if (ASCII_NIL == fmt_chr)
         {
            break;
         }

         // fmt_chr check for field replacement

         if (ASCII_PERCENT != fmt_chr)
         {
            out_p = tms_utils_fmt_put_chr(out_p, out_buf_sz - (out_p - out_buf_p), fmt_chr);

            continue;
         }

         // fmt_chr check for field alignment flags

         field_flag.ul = FIELD_FLAG_NONE;

         fmt_chr = *fmt_str++;

         // fmt_chr check for field alignment, FIELD_FLAG_ZERO padding

         if (ASCII_ZERO == fmt_chr)
         {
            field_flag.ul |= FIELD_FLAG_ZERO;

            fmt_chr = *fmt_str++;
         }

         // fmt_chr check for field alignment, left hand negative

         else if (ASCII_SIGN == fmt_chr)
         {
            field_flag.ul |= FIELD_FLAG_LNEG;

            fmt_chr = *fmt_str++;
         }

         // fmt_chr check for field alignment, field width

         for (field_width.ul = 0; ASCII_ZERO <= fmt_chr && ASCII_9 >= fmt_chr; fmt_chr = *fmt_str++)
         {
            // multiply by 10, add next digit

            field_width.ul = field_width.ul * 10 + fmt_chr - ASCII_ZERO;
         }

         // fmt_chr check for field alignment, long value on stack (really a no-op)

         if (ASCII_L == fmt_chr || fmt_chr == ASCII_CAP_L)
         {
            field_flag.ul |= FIELD_FLAG_LONG;

            fmt_chr = *fmt_str++;
         }

         // end of fmt_str check, premature

         if (ASCII_NIL == fmt_chr) break;

         // normalize fmt_code from fmt_char field specifier

         fmt_code = fmt_chr;

         if (ASCII_A <= fmt_code)
         {
            fmt_code -= ASCII_SPACE;
         }

         switch (fmt_code)
         {
            default:                                                                   // next field is "whatever", copied directly
            {
               out_p = tms_utils_fmt_put_chr(out_p, out_buf_sz - (out_p - out_buf_p), fmt_chr);
               continue;
            }

            case ASCII_CAP_C:                                                          // next field is char, %c
            {
               out_p = tms_utils_fmt_put_chr(out_p, out_buf_sz - (out_p - out_buf_p), (tms_chr)va_arg(argv, int));
               continue;
            }

            case ASCII_CAP_S:                                                          // next field is template, %s
            {
               tms_chr *chrs_p = va_arg(argv, tms_chr*);

               // determine length of passed parameter template (bounds check up to remaining output space)
               // bounds check is to minimize memory read access as an optimization

               for (fmt_fill.ul = 0; fmt_fill.ul <= out_buf_sz - (out_p - out_buf_p) && chrs_p && ASCII_NIL != *(chrs_p + fmt_fill.ul); fmt_fill.ul++)
                  /*NULL*/ ;

               // fill output buffer for justification

               while (FIELD_FLAG_NONE == (field_flag.ul & FIELD_FLAG_LNEG) && fmt_fill.ul++ < field_width.ul)
               {
                  out_p = tms_utils_fmt_put_chr(out_p, out_buf_sz - (out_p - out_buf_p), ASCII_SPACE);
               }

               // fill output buffer with passed parameter template

               out_p = tms_utils_fmt_put_chr_buf(out_p, out_buf_sz - (out_p - out_buf_p), chrs_p);

               // fill output buffer for remaining justification

               while (fmt_fill.ul++ < field_width.ul)
               {
                  out_p = tms_utils_fmt_put_chr(out_p, out_buf_sz - (out_p - out_buf_p), ASCII_SPACE);
               }

               continue;
            }

            case ASCII_CAP_B:                                                          // next field is numeric, pickup the radix, binary, %b
               field_radix.ul = 2;
               break;

            case ASCII_CAP_O:                                                          // next field is numeric, pickup the radix, octal, %o
               field_radix.ul = 8;
               break;

            case ASCII_CAP_D:
            case ASCII_CAP_U:                                                          // next field is numeric, pickup the radix, decimal, %d
               field_radix.ul = 10;
               break;

            case ASCII_CAP_X:                                                          // next field is numeric, pickup the radix, hex, %x
               field_radix.ul = 16;
               break;
         }

         // pickup field_arg.ul from stack, size properly, and determine sign

         if (FIELD_FLAG_NONE != (field_flag.ul & FIELD_FLAG_LONG))
         {
            field_arg.ul = va_arg(argv, long);
         }

         else
         {
            if (ASCII_D == fmt_code || ASCII_CAP_D == fmt_code)
            {
               field_arg.ul = (int32_t)va_arg(argv, int); // typecast (signed int)
            }
            else
            {
               field_arg.ul = (int32_t)va_arg(argv, unsigned int); // typecast (unsigned int)
            }
         }

         // absolute value of negative number as required for %d, %ld; this is performed with 2's compliment subtraction and typecasting

         if ((ASCII_D == fmt_code || ASCII_CAP_D == fmt_code) && 0 > (int32_t)field_arg.ul)
         {
            field_flag.ul |= FIELD_FLAG_SIGN;

            field_arg.ul = 0 - (int32_t)field_arg.ul;                                            // 2's compliment obtains absolute value
         }

         // copy field_arg.ul to chr_num with appropriate padding and sign

         fmt_pad.ul = 0;

         do
         {
            // get the radix unit and radix remainder

            fmt_code = (tms_chr)(field_arg.ul % field_radix.ul);
            field_arg.ul /= field_radix.ul;

            if (9 < fmt_code) // base adjustment for hex into ascii domain
            {
               if (ASCII_X == fmt_chr)
               {
                  fmt_code += 0x27; /* ascii lowercase offset */
               }
               else
               {
                  fmt_code += 0x07; /* ascii uppercase_offset */
               }
            }

            // copy adjusted chr value into chr_num

            chr_num[fmt_pad.ul] = fmt_code + ASCII_ZERO;

            fmt_pad.ul++;

         } while (0 != field_arg.ul && sizeof(chr_num) > fmt_pad.ul);

         // sign handling

         if (FIELD_FLAG_NONE != (field_flag.ul & FIELD_FLAG_SIGN) && FIELD_FLAG_NONE == (field_flag.ul & FIELD_FLAG_ZERO) && sizeof(chr_num) > fmt_pad.ul)
         {
            chr_num[fmt_pad.ul] = ASCII_SIGN;

            fmt_pad.ul++;
         }

         // zero or space pad handling

         if (FIELD_FLAG_NONE != (field_flag.ul & FIELD_FLAG_ZERO))
         {
            fmt_code = ASCII_ZERO;
         }
         else
         {
            fmt_code = ASCII_SPACE;
         }

         // output gets leading sign when needed

         if (FIELD_FLAG_NONE != (field_flag.ul & FIELD_FLAG_ZERO) && FIELD_FLAG_NONE != (field_flag.ul & FIELD_FLAG_SIGN))
         {
            out_p = tms_utils_fmt_put_chr(out_p, out_buf_sz - (out_p - out_buf_p), ASCII_SIGN);

            field_width.ul--;
         }

         // output gets left hand pad of space or zero

         fmt_fill.ul = fmt_pad.ul;

         while (FIELD_FLAG_NONE == (field_flag.ul & FIELD_FLAG_LNEG) && fmt_fill.ul++ < field_width.ul)
         {
            out_p = tms_utils_fmt_put_chr(out_p, out_buf_sz - (out_p - out_buf_p), fmt_code);
         }

         // output gets numeric value

         if (sizeof(chr_num) > fmt_pad.ul)
         {
            do
            {
               fmt_pad.ul--;

               out_p = tms_utils_fmt_put_chr(out_p, out_buf_sz - (out_p - out_buf_p), chr_num[fmt_pad.ul]);

            } while (0 != fmt_pad.ul);
         }

         // output gets right hand pad of space

         while (fmt_fill.ul++ < field_width.ul)
         {
            out_p = tms_utils_fmt_put_chr(out_p, out_buf_sz - (out_p - out_buf_p), ASCII_SPACE);
         }

      } while (out_p < out_buf_p + out_buf_sz); // terminates when output is full

      // nil terminate the output area

      if (out_p < out_buf_p + out_buf_sz)
      {
         *out_p++ = ASCII_NIL;
      }

      else
      {
         *(out_buf_p + out_buf_sz - 1) = ASCII_NIL;
      }

      // return is the number of chars put to output area

      return out_p - out_buf_p;
   }

   // bad input buf_sz

   else
   {
      return 0;
   }
}

int32_t tms_utils_fmt(tms_chr* out_buf_p, const size_t out_buf_sz, tms_chr const* fmt_str, ...)
{
   int32_t rc = 0;

   if (out_buf_p && out_buf_sz && fmt_str)
   {
      va_list argv;
      va_start(argv, fmt_str);
      rc = tms_utils_fmt_put(out_buf_p, out_buf_sz, fmt_str, argv);
      va_end(argv);
   }

   return rc;
}
