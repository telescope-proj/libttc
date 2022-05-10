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

#include "etcpak/ProcessDxtc.hpp"
#include "etcpak/ProcessRGB.hpp"

#include "ttc_types.h"
#include <errno.h>

static inline int ttcPrivateRunRGBAtoDXT1(void * src, void * dst, 
                            uint64_t width, uint64_t height,
                            uint64_t flags)
{
    if (width % 4 || height % 4 || !src || !dst)
        return -EINVAL;

    if (flags & TTC_FLAG_DITHER)
    {
        CompressDxt1Dither((const uint32_t *) src, (uint64_t *) dst, 
                           width * height / 16, width);
    }
    else
    {
        CompressDxt1((const uint32_t *) src, (uint64_t *) dst, 
                     width * height / 16, width);
    }
    return 0;
}

static inline int ttcPrivateRunRGBAtoDXT5(void * src, void * dst, 
                                          uint64_t width, uint64_t height,
                                          uint64_t flags)
{
    if (width % 4 || height % 4 || !src || !dst)
        return -EINVAL;

    CompressDxt5((const uint32_t *) src, (uint64_t *) dst, 
                    width * height / 16, width);
    return 0;
}

static inline int ttcPrivateRunBGRAtoETC1(void * src, void * dst, 
                                          uint64_t width, uint64_t height,
                                          uint64_t flags)
{
    if (width % 4 || height % 4 || !src || !dst)
        return -EINVAL;

    if (flags & TTC_FLAG_DITHER)
    {
        CompressEtc1RgbDither((const uint32_t *) src, (uint64_t *) dst, 
                              width * height / 16, width);
    }
    else
    {
        CompressEtc1Rgb((const uint32_t *) src, (uint64_t *) dst, 
                        width * height / 16, width);
    }
    return 0;
}

static inline int ttcPrivateRunBGRAtoETC2(void * src, void * dst,
                                          uint64_t width, uint64_t height,
                                          uint64_t flags)
{
    if (width % 4 || height % 4 || !src || !dst)
        return -EINVAL;

    CompressEtc2Rgb((const uint32_t *) src, (uint64_t *) dst,
                    width * height / 16, width,
                    ((flags & TTC_FLAG_HEURISTICS) > 0));
    return 0;
}

static inline int ttcPrivateRunBGRAtoETC2EAC(void * src, void * dst,
                                             uint64_t width, uint64_t height,
                                             uint64_t flags)
{
    if (width % 4 || height % 4 || !src || !dst)
        return -EINVAL;

    CompressEtc2Rgba((const uint32_t *) src, (uint64_t *) dst,
                     width * height / 16, width, 
                     ((flags & TTC_FLAG_HEURISTICS) > 0));
    return 0;
}

int ttcPrivateDispatchRGBA(void * src, void * dst,
                           uint64_t width, uint64_t height,
                           TTCFormat dst_fmt, uint64_t flags);

int ttcPrivateDispatchBGRA(void * src, void * dst, 
                           uint64_t width, uint64_t height, 
                           TTCFormat dst_fmt, uint64_t flags);