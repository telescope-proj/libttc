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

#include "internal/ttci.h"
#include "ttc_types.h"
#include <errno.h>

/**
 * @brief Base conversion functions.
 *
 * These functions directly convert texture formats, without performing any
 * intermediate conversions or checks on the input data. It is the
 * responsibility of the user to validate the input data before using these
 * functions, otherwise, you should use the ttcTranscode() function.
 */

/**
 * @brief           Return the number of bytes needed to store the texture with
 *                  the specified parameters.
 *
 * @param width     Width in pixels
 * 
 * @param height    Height in pixels
 * 
 * @param fmt       Texture format
 * 
 * @return          Number of bytes needed to store the texture, negative error
 *                  code on failure.
 *
 *                  -EINVAL is returned if the input parameters fail validation,
 *                  e.g. if the format, width or height is invaild.
 *
 *                  -ENOSYS is returned if the texture does not support the
 *                  specified arguments, e.g. if the texture dimensions are
 *                  not multiples of the input block size.
 */
int64_t ttcGetSize(size_t width, size_t height, TTCFormat fmt);

/**
 * @brief       Convert 8 bits per channel, 4 channel input into 8 bits per
 *              channel, 3 channel output. The pixel control parameters
 *              determine the channel mapping. For example, a BGRA to RGB
 *              transcode swaps channels 0 and 2 and strips channel 3, so the
 *              parameters p0, p1, p2 should be 2, 1, 0 respectively.
 *
 * @param src   Source buffer.
 * 
 * @param dst   Destination buffer.
 * 
 * @param size  Source buffer size in bytes. Must be a multiple of 4.
 * 
 * @param p0    Channel 0 source channel.
 * 
 * @param p1    Channel 1 source channel.
 * 
 * @param p2    Channel 2 source channel.
 * 
 * @return      0 on success, -EINVAL on invalid input.
 */
void ttcConvIn8_4Out8_3(void * src, void * dst,
                        uint64_t size,
                        char p0, char p1, char p2);

/**
 * @brief       Swap channels in 8 bit per channel, 4 channel input.
 *              It is safe to use this function when src == dst.
 * 
 * @param src   Source buffer.
 * 
 * @param dst   Destination buffer.
 * 
 * @param size  Source buffer size in bytes. Must be a multiple of 4.
 * 
 * @param p0    Channel 0 source channel.
 * 
 * @param p1    Channel 1 source channel.
 * 
 * @param p2    Channel 2 source channel.
 * 
 * @param p3    Channel 3 source channel.
 */
void ttcSwapCh_8_4(void * src, void * dst, uint64_t size,
                   char p0, char p1, char p2, char p3);

#ifdef __cplusplus
}
#endif