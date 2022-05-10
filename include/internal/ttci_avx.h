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

#ifdef __AVX2__

#include "internal/ttci.h"

/*
    See ttcConvIn8_4Out8_3() for parameter documentation.
    Size must be a multiple of 128.
*/
static inline void ttcPrivateSwapCh_8_4_AVX(void * src, void * dst, 
                                            uint64_t size, 
                                            char p0, char p1, char p2, char p3)
{
    __m256i * inp = (__m256i *) src;
    __m256i * out = (__m256i *) dst;
    uint8_t * end = (uint8_t *) src + size;

    __m256i mask = _mm256_set_epi8(
        p3 + 28, p2 + 28, p1 + 28, p0 + 28,
        p3 + 24, p2 + 24, p1 + 24, p0 + 24,
        p3 + 20, p2 + 20, p1 + 20, p0 + 20,
        p3 + 16, p2 + 16, p1 + 16, p0 + 16,
        p3 + 12, p2 + 12, p1 + 12, p0 + 12,
        p3 + 8,  p2 + 8,  p1 + 8,  p0 + 8,
        p3 + 4,  p2 + 4,  p1 + 4,  p0 + 4,
        p3,      p2,      p1,      p0
    );

    if ((uintptr_t) src % 16 || (uintptr_t) dst % 16)
    {
        while (inp < (__m256i *) end)
        {
            __m256i res0 = _mm256_shuffle_epi8(_mm256_loadu_si256(inp), mask);
            __m256i res1 = _mm256_shuffle_epi8(_mm256_loadu_si256(inp + 1), mask);
            __m256i res2 = _mm256_shuffle_epi8(_mm256_loadu_si256(inp + 2), mask);
            __m256i res3 = _mm256_shuffle_epi8(_mm256_loadu_si256(inp + 3), mask);

            _mm256_storeu_si256(out, res0);
            _mm256_storeu_si256(out + 1, res1);
            _mm256_storeu_si256(out + 2, res2);
            _mm256_storeu_si256(out + 3, res3);

            inp += 4;
            out += 4;
        }
    }
    else
    {
        while (inp < (__m256i *) end)
        {
            __m256i res0 = _mm256_shuffle_epi8(_mm256_load_si256(inp), mask);
            __m256i res1 = _mm256_shuffle_epi8(_mm256_load_si256(inp + 1), mask);
            __m256i res2 = _mm256_shuffle_epi8(_mm256_load_si256(inp + 2), mask);
            __m256i res3 = _mm256_shuffle_epi8(_mm256_load_si256(inp + 3), mask);

            _mm256_store_si256(out, res0);
            _mm256_store_si256(out + 1, res1);
            _mm256_store_si256(out + 2, res2);
            _mm256_store_si256(out + 3, res3);

            inp += 4;
            out += 4;
        }
    }
}

#endif

#ifdef __cplusplus
}
#endif

/*
    See ttcSwapCh_8_4 for parameter documentation.
    Size must be a multiple of 128.
*/
// static inline void ttcPrivateConvIn8_4Out8_3_AVX(void * src, void * dst,
//                                                  uint64_t size,
//                                                  char p0, char p1, char p2)
// {
//     __m256i * inp = (__m256i *) src;
//     __m256i * out = (__m256i *) dst;

//     __m256i in0_out0 = _mm256_set_epi8(
//         -128, -128, -128, -128, -128, -128, -128, -128,
//         p2 + 28, p1 + 28, p0 + 28,
//         p2 + 24, p1 + 24, p0 + 24,
//         p2 + 20, p1 + 20, p0 + 20,
//         p2 + 16, p1 + 16, p2 + 16,
//         p2 + 12, p1 + 12, p0 + 12,
//         p2 + 8,  p1 + 8,  p0 + 8,
//         p2 + 4,  p1 + 4,  p0 + 4,
//         p2,      p1,      p0
//     );

//     __m256i in1_out0 = _mm256_set_epi8(
//                  p1 + 8,  p0 + 8,
//         p2 + 4,  p1 + 4,  p0 + 4,
//         p2,      p1,      p0,
//         -128, -128, -128, -128, -128, -128, -128, -128, 
//         -128, -128, -128, -128, -128, -128, -128, -128, 
//         -128, -128, -128, -128, -128, -128, -128, -128
//     );

//     __m256i in1_out1 = _mm256_set_epi8(
//         -128, -128, -128, -128, -128, -128, -128, -128, 
//         -128, -128, -128, -128, -128, -128, -128, -128, 
//         p2 + 28, p1 + 28, p0 + 28,
//         p2 + 24, p1 + 24, p0 + 24,
//         p2 + 20, p1 + 20, p0 + 20,
//         p2 + 16, p1 + 16, p0 + 16,
//         p2 + 12, p1 + 12, p0 + 12,
//         p2 + 8,
//     );

// }