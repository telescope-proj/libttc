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

#include <inttypes.h>
#include <string.h>
#include <stdint.h>

#include <errno.h>

#include "ttc.h"
#include "etcpak/ProcessDxtc.hpp"
#include "etcpak/ProcessRGB.hpp"
#include "etcpak/DecodeDxtc.hpp"

extern "C" void ttcEncodeDXT5( void *src, void* dst, uint32_t width,
                    uint32_t height, uint32_t format)
{
    if ( !src || !dst || !width || !height || !format)
        return;

    uint32_t* lsrc = (uint32_t*)src;
    CompressDxt5((uint32_t *) lsrc, (uint64_t *) dst,
                width * height / 16, width);
}

extern "C" void ttcEncodeDXT1( void *src, void* dst, uint32_t width,
                    uint32_t height, uint32_t format)
{
    if ( !src || !dst || !width || !height || !format)
        return;

    uint32_t* lsrc = (uint32_t*)src;
    CompressDxt1((uint32_t *) lsrc, (uint64_t *) dst,
                width * height / 16, width);
}

extern "C" void ttcEncodeETC2RGB( void *src, void* dst, uint32_t width,
                    uint32_t height, uint32_t format, bool heuristics)
{
    if ( !src || !dst || !width || !height || !format)
        return;

    uint32_t* lsrc = (uint32_t*)src;
    CompressEtc2Rgb((uint32_t *) lsrc, (uint64_t *) dst,
                width * height / 16, width, heuristics);
}

extern "C" void ttcEncodeETC2RGBA( void *src, void* dst, uint32_t width,
                    uint32_t height, uint32_t format, bool heuristics)
{
    if ( !src || !dst || !width || !height || !format)
        return;

    uint32_t* lsrc = (uint32_t*)src;
    CompressEtc2Rgba((uint32_t *) lsrc, (uint64_t *) dst,
                width * height / 16, width, heuristics);
}

extern "C" void ttcEncodeETC1RGB( void *src, void* dst, uint32_t width,
                    uint32_t height, uint32_t format)
{
    if ( !src || !dst || !width || !height || !format)
        return;

    uint32_t* lsrc = (uint32_t*)src;
    CompressEtc1Rgb((uint32_t *) lsrc, (uint64_t *) dst,
                width * height / 16, width);
}

extern "C" void ttcDecodeDXT5( void* src, void* dst, uint32_t width,
                    uint32_t height, uint32_t format)
{
    if ( !src || !dst || !width || !height || !format || 
            width % 4 || height % 4)
        return;

    uint32_t* ldst = (uint32_t *) dst;
    uint64_t* lsrc = (uint64_t *) src;
    for( uint32_t y=0; y<height/4; y++ )
    {
        for( uint32_t x=0; x<width/4; x++ )
        {
            uint64_t a = *lsrc++;
            uint64_t d = *lsrc++;
            DecodeDxt5Part( a, d, ldst, width );
            ldst += 4;
        }
        ldst += width*3;
    }
}

extern "C" void ttcDecodeDXT1( void* src, void* dst, uint32_t width,
                    uint32_t height, uint32_t format)
{
    if ( !src || !dst || !width || !height || !format ||
            width % 4 || height % 4)
        return;

    uint32_t* ldst = (uint32_t *) dst;
    uint64_t* lsrc = (uint64_t *) src;
    for( uint32_t y=0; y<height/4; y++ )
    {
        for( uint32_t x=0; x<width/4; x++ )
        {
            uint64_t d = *lsrc++;
            DecodeDxt1Part( d, ldst, width );
            ldst += 4;
        }
        ldst += width*3;
    }
}