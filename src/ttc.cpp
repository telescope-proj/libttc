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

#include <cassert>
#include <inttypes.h>
#include <string.h>
#include <stdint.h>

#include <errno.h>

#include "ttc.h"
#include "ttc_base.h"
#include "internal/ttci_dispatch.hpp"

/**
 * @brief           Perform a transcode operation. The system will attempt to
 *                  transcode the texture data from src_fmt to dst_fmt.
 *
 *                  The requested transcoding operation must be supported.
 *
 * @param src       Source format
 *
 * @param dst       Destination format
 *
 * @param width     Image width
 *
 * @param height    Image height
 *
 * @param src_fmt   Source format
 *
 * @param dst_fmt   Requested output format
 * 
 * @param flags     Flags used to control the operation.
 *
 * @return          0 on success, -ENOSYS if the texture could not be
 *                  transcoded.
 */
int ttcTranscode(void * src, void * dst, 
                  uint64_t width, uint64_t height, 
                  TTCFormat src_fmt, TTCFormat dst_fmt,
                  uint64_t flags)
{
    // Fast path
    if (src_fmt == dst_fmt)
    {
        memcpy(dst, src, ttcGetSize(width, height, src_fmt));
        return 0;
    }

    switch (src_fmt)
    {
        case TTC_FMT_BGRA:
            return ttcPrivateDispatchBGRA(src, dst, width, height, dst_fmt, 
                                          flags);
        case TTC_FMT_RGBA:
            return ttcPrivateDispatchRGBA(src, dst, width, height, dst_fmt,
                                          flags);
        default:
            return -ENOTSUP;
    }
}