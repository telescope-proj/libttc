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

#include <stdint.h>

#if defined(__SSE4_1__)
    #include <tmmintrin.h>
#endif

#if defined(__AVX2__)
    #include <immintrin.h>
#endif

#ifdef __cplusplus
}
#endif