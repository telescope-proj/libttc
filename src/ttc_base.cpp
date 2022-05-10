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

#include "internal/ttci.h"
#include "internal/ttci_sse.h"
#include "internal/ttci_avx.h"
#include "internal/ttci_dispatch.hpp"

#include "etcpak/ProcessDxtc.hpp"

#include "ttc_types.h"

#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

int64_t ttcGetSize(size_t width, size_t height, TTCFormat fmt)
{
    if (!width || !height || fmt <= TTC_FMT_INVALID || fmt >= TTC_FMT_MAX)
        return -EINVAL;

    switch (fmt)
    {
        case TTC_FMT_RGB:
            return width * height * 3;
        case TTC_FMT_RGBA:
        case TTC_FMT_BGRA:
            return width * height * 4;
        case TTC_FMT_DXT1:
        case TTC_FMT_ETC1:
        case TTC_FMT_ETC2:
            if (width % 4 || height % 4)
                return -ENOSYS;
            return width * height / 2;
        case TTC_FMT_DXT5:
        case TTC_FMT_ETC2_EAC:
            if (width % 4 || height % 4)
                return -ENOSYS;
            return width * height;
        default:
            return -EINVAL;
    }
}


void ttcConvIn8_4Out8_3(void * src, void * dst,
                       uint64_t size,
                       char p0, char p1, char p2)
{
    #if defined(__SSE4_1__)
        int align = 64;
        ttcPrivateConvIn8_4Out8_3_SSE(src, dst, size - (size % align), 
                                      p0, p1, p2);
    #else
        int align = 1;
    #endif
    
    // Slow fallback if no SSE support or end of data unaligned
    
    if (size % align)
    {
        src = (uint8_t *) src + size - (size % align);
        dst = (uint8_t *) dst + size - (size % align);
        size = size % align;
    }

    uint8_t * end = (uint8_t *) src + size;

    while (src < end)
    {
        uint32_t tmp = * (uint32_t *) src;
        ((uint8_t *) dst)[0] = ((uint8_t *) &tmp)[(unsigned char) p0];
        ((uint8_t *) dst)[1] = ((uint8_t *) &tmp)[(unsigned char) p1];
        ((uint8_t *) dst)[2] = ((uint8_t *) &tmp)[(unsigned char) p2];
        src = (uint8_t *) src + 4;
        dst = (uint8_t *) dst + 3;
    }
}


void ttcSwapCh_8_4(void * src, void * dst, uint64_t size,
                   char p0, char p1, char p2, char p3)
{
    #if defined(__SSE4_1__)
        int align = 64;
        ttcPrivateSwapCh_8_4_SSE(src, dst, size - (size % align),
                                 p0, p1, p2, p3);
    #else
        int align = 1;
    #endif

    // Slow fallback if no SSE support or end of data unaligned

    if (size % align)
    {
        src = (uint8_t *) src + size - (size % align);
        dst = (uint8_t *) dst + size - (size % align);
        size = size % align;
    }
    
    uint8_t * end = (uint8_t *) src + size;

    while (src < end)
    {
        uint32_t tmp = * (uint32_t *) src;
        ((uint8_t *) dst)[0] = ((uint8_t *) &tmp)[(unsigned char) p0];
        ((uint8_t *) dst)[1] = ((uint8_t *) &tmp)[(unsigned char) p1];
        ((uint8_t *) dst)[2] = ((uint8_t *) &tmp)[(unsigned char) p2];
        ((uint8_t *) dst)[3] = ((uint8_t *) &tmp)[(unsigned char) p3];
        src = (uint8_t *) src + 4;
        dst = (uint8_t *) dst + 4;
    }
}


#ifdef __cplusplus
}
#endif