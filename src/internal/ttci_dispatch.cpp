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

#ifdef __SSE4_1__
    #include <smmintrin.h>
#endif

#ifdef __AVX2__
    #include <immintrin.h>
#endif

#include <errno.h>

#include "ttc_types.h"

#include "ttc_base.h"
#include "internal/ttci_dispatch.hpp"

int ttcPrivateDispatchRGBA(void * src, void * dst,
                           uint64_t width, uint64_t height,
                           TTCFormat dst_fmt, uint64_t flags)
{
    size_t fsize = ttcGetSize(width, height, dst_fmt);
    switch (dst_fmt)
    {
        case TTC_FMT_RGBA:
            memcpy(dst, src, fsize);
            return 0;
        case TTC_FMT_BGRA:
            return ttcSwapCh_8_4(src, dst, fsize, 2, 1, 0, 3);
        case TTC_FMT_RGB:
            return ttcConvIn8_4Out8_3(src, dst, fsize, 0, 1, 2);
        case TTC_FMT_DXT1:
            return ttcPrivateRunRGBAtoDXT1(src, dst, width, height, flags);
        case TTC_FMT_DXT5:
            return ttcPrivateRunRGBAtoDXT5(src, dst, width, height, flags);
        case TTC_FMT_ETC1:
            return ttcPrivateRunRGBAtoETC1(src, dst, width, height, flags);
        case TTC_FMT_ETC2:
            return ttcPrivateRunRGBAtoETC2RGB(src, dst, width, height, flags);
        case TTC_FMT_ETC2_EAC:
            return ttcPrivateRunRGBAtoETC2RGBA(src, dst, width, height, flags);
        default:
            return -ENOSYS;
    }
}

int ttcPrivateDispatchBGRA(void * src, void * dst, 
                           uint64_t width, uint64_t height, 
                           TTCFormat dst_fmt, uint64_t flags)
{
    size_t fsize = ttcGetSize(width, height, dst_fmt);
    int ret;

    void * scratch;
    switch (dst_fmt)
    {
        case TTC_FMT_RGBA:
            return ttcPrivateSwapCh_8_4(src, dst, fsize, 2, 1, 0, 3);
        case TTC_FMT_RGB:
            return ttcConvIn8_4Out8_3(src, dst, fsize, 2, 1, 0);
        case TTC_FMT_DXT1:
        case TTC_FMT_DXT5:
        case TTC_FMT_ETC1:
        case TTC_FMT_ETC2:
        case TTC_FMT_ETC2_EAC:
            if (flags & TTC_FLAG_SRC_BUF_WRITABLE)
            {
                scratch = src;
            }
            else
            {
                scratch = malloc(ttcGetSize(width, height, TTC_FMT_RGBA));
                if (!scratch)
                    return -ENOMEM;
            }
            ret = ttcPrivateDispatchRGBA(scratch, dst, fsize, 2, 1, 0, 3);
            if (scratch != src)
            {
                free(scratch);
            }
            return ret;
        default:
            return -ENOSYS;
    }

    return ret;
}