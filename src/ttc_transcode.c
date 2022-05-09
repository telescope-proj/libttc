#include <tmmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>

#include <stdio.h>
#include <stdint.h>

static inline void transcode_BGRAtoRGB(uint8_t *src, size_t size, uint8_t *dst) {
    __m128i mask = _mm_set_epi8(
    -128, -128, -128, -128, // top 4 bytes are not used
    12 ,13 ,14 ,8 ,
    9 ,10 ,4 ,5 ,
    6 ,0 ,1 ,2);
    uint8_t *end = src + size * 4;
    for (; src != end; src += 16, dst += 12) {
        _mm_storeu_si128((__m128i *)dst, _mm_shuffle_epi8(_mm_load_si128((__m128i *)src), mask));
    }
}

static inline void transcode_BGRAtoRGBAVX(void * src, void * dst, size_t width, size_t height, uint64_t flags)
{
  __m256i * tmp_src = src;
  __m256i * tmp_dst = dst;
  uint8_t * end = ((uint8_t *) src) + (width * height * 4);

  __m256i in0_out0 = _mm256_set_epi8(
    -128, -128, -128, -128, -128, -128, -128, -128,
    28, 29, 30, 24, 25, 26, 20, 21, 
    22, 16, 17, 18, 12, 13, 14, 8, 
    9, 10, 4, 5, 6, 0, 1, 2
  );

  __m256i in1_out0 = _mm256_set_epi8(
    9, 10, 4, 5, 6, 0, 1, 2, 
    -128, -128, -128, -128, -128, -128, -128, -128, 
    -128, -128, -128, -128, -128, -128, -128, -128, 
    -128, -128, -128, -128, -128, -128, -128, -128
  );

  __m256i in1_out1 = _mm256_set_epi8(
    -128, -128, -128, -128, -128, -128, -128, -128, 
    -128, -128, -128, -128, -128, -128, -128, -128, 
    28, 29, 30, 24, 25, 26, 20, 21, 22, 
    16, 17, 18, 12, 13, 14, 8
  );

  __m256i in2_out1 = _mm256_set_epi8(
    22, 16, 17, 18, 12, 13, 14, 8,
    9, 10, 4, 5, 6, 0, 1, 2, 
    -128, -128, -128, -128, -128, -128, -128, -128, 
    -128, -128, -128, -128, -128, -128, -128, -128
  );

  __m256i in2_out2 = _mm256_set_epi8(
    -128, -128, -128, -128, -128, -128, -128, -128,
    22, 16, 17, 18, 12, 13, 14, 8, 
    9, 10, 4, 5, 6, 0, 1, 2, 
    28, 29, 30, 24, 25, 26, 20, 21
  );

  __m256i in3_out2 = _mm256_set_epi8(
    28, 29, 30, 24, 25, 26, 20, 21, 
    -128, -128, -128, -128, -128, -128, -128, -128, 
    -128, -128, -128, -128, -128, -128, -128, -128, 
    -128, -128, -128, -128, -128, -128, -128, -128
  );

  while (tmp_src < (__m256i *) end)
  {

    __m256i pix0 = _mm256_load_si256(tmp_src);
    __m256i pix1 = _mm256_load_si256(tmp_src + 1);
    __m256i pix2 = _mm256_load_si256(tmp_src + 2);
    __m256i pix3 = _mm256_load_si256(tmp_src + 3);

    __m256i out0_p1   = _mm256_shuffle_epi8(pix0, in0_out0);
    __m256i out0_p2   = _mm256_shuffle_epi8(pix1, in1_out0);

    __m256i out1_p1   = _mm256_shuffle_epi8(pix1, in1_out1);
    __m256i out1_p2   = _mm256_shuffle_epi8(pix2, in2_out1);

    __m256i out2_p1   = _mm256_shuffle_epi8(pix2, in2_out2);
    __m256i out2_p2   = _mm256_shuffle_epi8(pix3, in3_out2);

    _mm256_store_si256( tmp_dst, _mm256_or_si256(out0_p1, out0_p2));
    _mm256_store_si256( tmp_dst + 1, _mm256_or_si256(out1_p1, out1_p2));
    _mm256_store_si256( tmp_dst + 2, _mm256_or_si256(out2_p1, out2_p2));

    tmp_src += 4;
    tmp_dst += 3;
  }
}

static inline void transcode_BGRAtoRGB_alligned( void * src, void * dst, size_t width
                                      , size_t height, uint64_t flags)
{
  __m128i * tmp_src = src;
  __m128i * tmp_dst = dst;
  uint8_t * end = ((uint8_t *) src) + (width * height * 4);

    __m128i in0_out0 = _mm_set_epi8(
        -128, -128, -128, -128, 
        12, 13, 14, 
        8, 9, 10, 
        4, 5, 6, 
        0, 1, 2
    );

   __m128i in1_out0 = _mm_set_epi8(
    6, 0, 1, 2,
    -128, -128, -128, -128, 
    -128, -128, -128, -128,
    -128, -128, -128, -128
  );


  __m128i in1_out1 = _mm_set_epi8(
    -128, -128, -128, -128,
    -128, -128, -128, -128,
    12, 13, 14, 8,
    9, 10, 4, 5
  );

  __m128i in2_out1 = _mm_set_epi8(
    9, 10, 4, 5, 
    6, 0, 1, 2,
    -128, -128, -128, -128,
    -128, -128, -128, -128
  );

  __m128i in2_out2 = _mm_set_epi8(
    -128, -128, -128, -128,
    -128, -128, -128, -128,
    -128, -128, -128, -128,
    12, 13, 14, 8
  );

  __m128i in3_out2 = _mm_set_epi8(
    12, 13, 14, 8,
    9, 10, 4, 5, 
    6, 0, 1, 2,
    -128, -128, -128, -128
  );
  
  while (tmp_src < (__m128i *) end)
  {

    __m128i pix0 = _mm_load_si128(tmp_src);
    __m128i pix1 = _mm_load_si128(tmp_src + 1);
    __m128i pix2 = _mm_load_si128(tmp_src + 2);
    __m128i pix3 = _mm_load_si128(tmp_src + 3);

    __m128i out0_p1   = _mm_shuffle_epi8(pix0, in0_out0);
    __m128i out0_p2   = _mm_shuffle_epi8(pix1, in1_out0);

    __m128i out1_p1   = _mm_shuffle_epi8(pix1, in1_out1);
    __m128i out1_p2   = _mm_shuffle_epi8(pix2, in2_out1);

    __m128i out2_p1   = _mm_shuffle_epi8(pix2, in2_out2);
    __m128i out2_p2   = _mm_shuffle_epi8(pix3, in3_out2);

    _mm_store_si128( tmp_dst, _mm_or_si128(out0_p1, out0_p2));
    _mm_store_si128( tmp_dst + 1, _mm_or_si128(out1_p1, out1_p2));
    _mm_store_si128( tmp_dst + 2, _mm_or_si128(out2_p1, out2_p2));

    tmp_src += 4;
    tmp_dst += 3;
  }
}