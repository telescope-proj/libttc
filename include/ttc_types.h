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

typedef enum TTCFormat {
    TTC_FMT_INVALID,
    TTC_FMT_RGB,
    TTC_FMT_RGBA,
    TTC_FMT_BGRA,
    TTC_FMT_DXT1,
    TTC_FMT_DXT5,
    TTC_FMT_ETC1,
    TTC_FMT_ETC2,
    TTC_FMT_ETC2_EAC,
    TTC_FMT_MAX
} TTCFormat;

typedef enum TTCFlags {
    TTC_FLAG_SRC_BUF_WRITABLE   = (1 << 0),
    TTC_FLAG_DITHER             = (1 << 16),
    TTC_FLAG_HEURISTICS         = (1 << 17),
    TTC_PRIVATE_FORCE_UINT64    = UINT64_MAX
} TTCFlags;