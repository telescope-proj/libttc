/*
  Telescope Project
  Unified Texture Conversion & Compression Library

  Copyright (c) 2022 Telescope Project Developers
  SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only

  This software is available to you under a choice of one of two licenses. You
  may choose to be licensed under the terms of the the New BSD License or the
  GNU General Public License (GPL) Version 2.

  See the file LICENSE for details.
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __SSE4_1__

#include "internal/ttci.h"

/*
    See ttcConvIn8_4Out8_3() for parameter documentation.
    Size must be a multiple of 64.
*/
static inline void ttcPrivateConvIn8_4Out8_3_SSE(void * src, void * dst,
                                                 uint64_t size,
                                                 char p0, char p1, char p2)
{
    // Explicit CSE

    const char p2_4    = p2 + 4;
    const char p2_8    = p2 + 8;
    const char p2_12   = p2 + 12;

    const char p1_4    = p1 + 4;
    const char p1_8    = p1 + 8;
    const char p1_12   = p1 + 12;

    const char p0_4    = p0 + 4;
    const char p0_8    = p0 + 8;
    const char p0_12   = p0 + 12;

    // Transcode control masks

    __m128i in0_out0 = _mm_set_epi8(
                        -128, 
        -128,  -128,  -128, 
        p2_12, p1_12, p0_12,
        p2_8,  p1_8,  p0_8,
        p2_4,  p1_4,  p0_4,
        p2,    p1,    p0
    );

    __m128i in1_out0 = _mm_set_epi8(
                        p0_4,
        p2,    p1,    p0,
        -128,  -128,  -128, 
        -128,  -128,  -128,
        -128,  -128,  -128, 
        -128,  -128,  -128
    );

    __m128i in1_out1 = _mm_set_epi8(
                -128,  -128, 
        -128,  -128,  -128, 
        -128,  -128,  -128,
        p2_12, p1_12, p0_12,
        p2_8,  p1_8,  p0_8, 
        p2_4,  p1_4
    );

    __m128i in2_out1 = _mm_set_epi8(
               p1_8,  p0_8,
        p2_4,  p1_4,  p0_4,
        p2,    p1,    p0,
        -128,  -128,  -128,
        -128,  -128,  -128,
        -128,  -128
    );

    __m128i in2_out2 = _mm_set_epi8(
        -128,  -128,  -128, 
        -128,  -128,  -128, 
        -128,  -128,  -128, 
        -128,  -128,  -128,
        p2_12, p1_12, p0_12,
        p2_8
    );

    __m128i in3_out2 = _mm_set_epi8(
        p2_12, p1_12, p0_12,
        p2_8,  p1_8,  p0_8,
        p2_4,  p1_4,  p0_4,
        p2,    p1,    p0,
        -128,  -128,  -128, 
        -128
    );

    __m128i * inp = (__m128i *) src;
    __m128i * out = (__m128i *) dst;
    uint8_t * end = (uint8_t *) src + size;

    if ((uintptr_t) src % 16 || (uintptr_t) dst % 16)
    {
        while (inp < (__m128i *) end)
        {
            __m128i pix0 = _mm_loadu_si128(inp);
            __m128i pix1 = _mm_loadu_si128(inp + 1);
            __m128i pix2 = _mm_loadu_si128(inp + 2);
            __m128i pix3 = _mm_loadu_si128(inp + 3);

            __m128i out0_p1   = _mm_shuffle_epi8(pix0, in0_out0);
            __m128i out0_p2   = _mm_shuffle_epi8(pix1, in1_out0);

            __m128i out1_p1   = _mm_shuffle_epi8(pix1, in1_out1);
            __m128i out1_p2   = _mm_shuffle_epi8(pix2, in2_out1);

            __m128i out2_p1   = _mm_shuffle_epi8(pix2, in2_out2);
            __m128i out2_p2   = _mm_shuffle_epi8(pix3, in3_out2);

            _mm_storeu_si128(out, _mm_or_si128(out0_p1, out0_p2));
            _mm_storeu_si128(out + 1, _mm_or_si128(out1_p1, out1_p2));
            _mm_storeu_si128(out + 2, _mm_or_si128(out2_p1, out2_p2));

            inp += 4;
            out += 3;
        }
    }
    else
    {
        while (inp < (__m128i *) end)
        {
            __m128i pix0 = _mm_load_si128(inp);
            __m128i pix1 = _mm_load_si128(inp + 1);
            __m128i pix2 = _mm_load_si128(inp + 2);
            __m128i pix3 = _mm_load_si128(inp + 3);

            __m128i out0_p1   = _mm_shuffle_epi8(pix0, in0_out0);
            __m128i out0_p2   = _mm_shuffle_epi8(pix1, in1_out0);

            __m128i out1_p1   = _mm_shuffle_epi8(pix1, in1_out1);
            __m128i out1_p2   = _mm_shuffle_epi8(pix2, in2_out1);

            __m128i out2_p1   = _mm_shuffle_epi8(pix2, in2_out2);
            __m128i out2_p2   = _mm_shuffle_epi8(pix3, in3_out2);

            _mm_store_si128(out, _mm_or_si128(out0_p1, out0_p2));
            _mm_store_si128(out + 1, _mm_or_si128(out1_p1, out1_p2));
            _mm_store_si128(out + 2, _mm_or_si128(out2_p1, out2_p2));

            inp += 4;
            out += 3;
        }
    }
}

/*
    See ttcSwapCh_8_4 for parameter documentation.
    Size must be a multiple of 64.
*/
static inline void ttcPrivateSwapCh_8_4_SSE(void * src, void * dst, uint64_t size, 
                                            char p0, char p1, char p2, char p3)
{
    __m128i * inp = (__m128i *) src;
    __m128i * out = (__m128i *) dst;
    uint8_t * end = (uint8_t *) src + size;

    __m128i mask = _mm_set_epi8(
        p3 + 12, p2 + 12, p1 + 12, p0 + 12,
        p3 + 8,  p2 + 8,  p1 + 8,  p0 + 8,
        p3 + 4,  p2 + 4,  p1 + 4,  p0 + 4,
        p3,      p2,      p1,      p0
    );

    while (inp < (__m128i *) end)
    {
        __m128i res0 = _mm_shuffle_epi8(_mm_load_si128(inp), mask);
        __m128i res1 = _mm_shuffle_epi8(_mm_load_si128(inp + 1), mask);
        __m128i res2 = _mm_shuffle_epi8(_mm_load_si128(inp + 2), mask);
        __m128i res3 = _mm_shuffle_epi8(_mm_load_si128(inp + 3), mask);

        _mm_store_si128(out, res0);
        _mm_store_si128(out + 1, res1);
        _mm_store_si128(out + 2, res2);
        _mm_store_si128(out + 3, res3);

        inp += 4;
        out += 4;
    }
}


#endif

#ifdef __cplusplus
}
#endif