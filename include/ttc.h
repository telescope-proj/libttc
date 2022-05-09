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
  #define EXPORT_C extern "C"
#else
  #define EXPORT_C
#endif

// ************************ Encode Functions *********************************

EXPORT_C void ttcEncodeDXT5( void* src, void* dst, uint32_t width,
                              uint32_t height, uint32_t format);

EXPORT_C void ttcEncodeDXT1( void* src, void* dst, uint32_t width,
                              uint32_t height, uint32_t format);

EXPORT_C void ttcEncodeETC2RGB( void *src, void* dst, uint32_t width,
                    uint32_t height, uint32_t format, bool heuristics);

EXPORT_C void ttcEncodeETC2RGBA( void *src, void* dst, uint32_t width,
                    uint32_t height, uint32_t format, bool heuristics);

EXPORT_C void ttcEncodeETC1RGB( void *src, void* dst, uint32_t width,
                    uint32_t height, uint32_t format);

// ************************ Decode Functions *********************************

EXPORT_C void ttcDecodeDXT5( void* src, void* dst, uint32_t width,
                              uint32_t height, uint32_t format);

EXPORT_C void ttcDecodeDXT1( void* src, void* dst, uint32_t width,
                              uint32_t height, uint32_t format);