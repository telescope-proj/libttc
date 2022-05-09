/*
  etcpak, an extremely fast ETC compression utility
  (https://github.com/wolfpld/etcpak)

  Copyright (c) 2013-2021, Bartosz Taudul <wolf@nereid.pl> 
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer. 

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution. 

  * Neither the name of the <organization> nor the names of its contributors may
    be used to endorse or promote products derived from this software without
    specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __TABLES_HPP__
#define __TABLES_HPP__

#include <stdint.h>

#ifdef __AVX2__
#  include <immintrin.h>
#endif
#ifdef __SSE4_1__
#  include <smmintrin.h>
#endif
#ifdef __ARM_NEON
#  include <arm_neon.h>
#endif

extern const int32_t g_table[8][4];
extern const int64_t g_table256[8][4];

extern const uint32_t g_id[4][16];

extern const uint32_t g_avg2[16];

extern const uint32_t g_flags[64];

extern const int32_t g_alpha[16][8];
extern const int32_t g_alphaRange[16];

#ifdef __SSE4_1__
extern const __m128i g_table_SIMD[2];
extern const __m128i g_table128_SIMD[2];
extern const __m128i g_table256_SIMD[4];

extern const __m128i g_alpha_SIMD[16];
extern const __m128i g_alphaRange_SIMD;
#endif

#ifdef __AVX2__
extern const __m256i g_alpha_AVX[8];
extern const __m256i g_alphaRange_AVX;
#endif

#ifdef __ARM_NEON
extern const int16x8_t g_table128_NEON[2];
extern const int32x4_t g_table256_NEON[4];
extern const int16x8_t g_alpha_NEON[16];
extern const int16x8_t g_alphaRange_NEON;
#endif

#endif
