/*============================================================================

Copyright 2023 Rhys Weatherley

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. Neither the name of the copyright holder nor the names of its contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS”
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/

/*
 * Define aliases for the clang intrinsic functions for "float" and "double".
 *
 * See "llvm/include/llvm/IR/RuntimeLibcalls.def" in the LLVM source code
 * for a list of intrinsics that are expected by LLVM.
 */

#include <stdbool.h>
#include <stdint.h>
#include "platform.h"
#include "internals.h"
#include "softfloat.h"

#ifdef SOFTFLOAT_WEAK_ALIASES
#define PREFIX __attribute__((weak))
#else
#define PREFIX
#endif

// Arithmetic operators.

PREFIX float32_t __addsf3(float32_t x, float32_t y)
{
    return f32_add(x, y);
}

PREFIX float64_t __adddf3(float64_t x, float64_t y)
{
    return f64_add(x, y);
}

PREFIX float32_t __subsf3(float32_t x, float32_t y)
{
    return f32_sub(x, y);
}

PREFIX float64_t __subdf3(float64_t x, float64_t y)
{
    return f64_sub(x, y);
}

PREFIX float32_t __mulsf3(float32_t x, float32_t y)
{
    return f32_mul(x, y);
}

PREFIX float64_t __muldf3(float64_t x, float64_t y)
{
    return f64_mul(x, y);
}

PREFIX float32_t __divsf3(float32_t x, float32_t y)
{
    return f32_div(x, y);
}

PREFIX float64_t __divdf3(float64_t x, float64_t y)
{
    return f64_div(x, y);
}

PREFIX float32_t fmodf(float32_t x, float32_t y)
{
    return f32_rem(x, y);
}

PREFIX float64_t fmod(float64_t x, float64_t y)
{
    return f64_rem(x, y);
}

PREFIX float32_t fmaf(float32_t x, float32_t y, float32_t z)
{
    return f32_mulAdd(x, y, z);
}

PREFIX float64_t fma(float64_t x, float64_t y, float64_t z)
{
    return f64_mulAdd(x, y, z);
}

PREFIX float32_t sqrtf(float32_t x)
{
    return f32_sqrt(x);
}

PREFIX float64_t sqrt(float64_t x)
{
    return f64_sqrt(x);
}

// Rounding functions.

PREFIX float32_t ceilf(float32_t x)
{
    return f32_roundToInt(x, softfloat_round_max, false);
}

PREFIX float64_t ceil(float64_t x)
{
    return f64_roundToInt(x, softfloat_round_max, false);
}

PREFIX float32_t floorf(float32_t x)
{
    return f32_roundToInt(x, softfloat_round_min, false);
}

PREFIX float64_t floor(float64_t x)
{
    return f64_roundToInt(x, softfloat_round_min, false);
}

PREFIX float32_t truncf(float32_t x)
{
    return f32_roundToInt(x, softfloat_round_minMag, false);
}

PREFIX float64_t trunc(float64_t x)
{
    return f64_roundToInt(x, softfloat_round_minMag, false);
}

PREFIX float32_t roundf(float32_t x)
{
    return f32_roundToInt(x, softfloat_round_near_maxMag, false);
}

PREFIX float64_t round(float64_t x)
{
    return f64_roundToInt(x, softfloat_round_near_maxMag, false);
}

PREFIX float32_t roundevenf(float32_t x)
{
    return f32_roundToInt(x, softfloat_round_near_even, false);
}

PREFIX float64_t roundeven(float64_t x)
{
    return f64_roundToInt(x, softfloat_round_near_even, false);
}

PREFIX long lroundf(float32_t x)
{
    return f32_to_i32(x, softfloat_round_near_maxMag, false);
}

PREFIX long lround(float64_t x)
{
    return f64_to_i32(x, softfloat_round_near_maxMag, false);
}

PREFIX long long llroundf(float32_t x)
{
    return f32_to_i64(x, softfloat_round_near_maxMag, false);
}

PREFIX long long llround(float64_t x)
{
    return f64_to_i64(x, softfloat_round_near_maxMag, false);
}

// nearbyint(), rint(), lrint() use a fixed rounding mode of "round to even".
// Should we implement fesetround() to allow the mode to be changed?

PREFIX float32_t nearbyintf(float32_t x)
{
    return f32_roundToInt(x, softfloat_round_near_even, false);
}

PREFIX float64_t nearbyint(float64_t x)
{
    return f64_roundToInt(x, softfloat_round_near_even, false);
}

PREFIX float32_t rintf(float32_t x)
{
    return f32_roundToInt(x, softfloat_round_near_even, true);
}

PREFIX float64_t rint(float64_t x)
{
    return f64_roundToInt(x, softfloat_round_near_even, true);
}

PREFIX long lrintf(float32_t x)
{
    return f32_to_i32(x, softfloat_round_near_even, false);
}

PREFIX long lrint(float64_t x)
{
    return f64_to_i32(x, softfloat_round_near_even, false);
}

PREFIX long long llrintf(float32_t x)
{
    return f32_to_i64(x, softfloat_round_near_even, false);
}

PREFIX long long llrint(float64_t x)
{
    return f64_to_i64(x, softfloat_round_near_even, false);
}

// Comparison operators.

static inline int f32_isnan(float32_t x)
{
    union ui32_f32 ux;
    ux.f = x;
    return isNaNF32UI(ux.ui);
}

static inline int f64_isnan(float64_t x)
{
    union ui64_f64 ux;
    ux.f = x;
    return isNaNF64UI(ux.ui);
}

PREFIX int __unordsf2(float32_t x, float32_t y)
{
    return f32_isnan(x) || f32_isnan(y);
}

PREFIX int __unorddf2(float64_t x, float64_t y)
{
    return f64_isnan(x) || f64_isnan(y);
}

PREFIX int __eqsf2(float32_t x, float32_t y)
{
    return f32_eq_signaling(x, y);
}

PREFIX int __eqdf2(float64_t x, float64_t y)
{
    return f64_eq_signaling(x, y);
}

PREFIX int __nesf2(float32_t x, float32_t y)
{
    if (__unordsf2(x, y))
        return f32_eq_signaling(x, y); // Raise the error.
    return !f32_eq_signaling(x, y);
}

PREFIX int __nedf2(float64_t x, float64_t y)
{
    if (__unorddf2(x, y))
        return f64_eq_signaling(x, y); // Raise the error.
    return !f64_eq_signaling(x, y);
}

PREFIX int __ltsf2(float32_t x, float32_t y)
{
    return f32_lt(x, y);
}

PREFIX int __ltdf2(float64_t x, float64_t y)
{
    return f64_lt(x, y);
}

PREFIX int __lesf2(float32_t x, float32_t y)
{
    return f32_le(x, y);
}

PREFIX int __ledf2(float64_t x, float64_t y)
{
    return f64_le(x, y);
}

PREFIX int __gtsf2(float32_t x, float32_t y)
{
    return f32_lt(y, x);
}

PREFIX int __gtdf2(float64_t x, float64_t y)
{
    return f64_lt(y, x);
}

PREFIX int __gesf2(float32_t x, float32_t y)
{
    return f32_le(y, x);
}

PREFIX int __gedf2(float64_t x, float64_t y)
{
    return f64_le(y, x);
}

// Conversion operators.

PREFIX float32_t __gnu_h2f_ieee(float16_t x)
{
    return f16_to_f32(x);
}

PREFIX float64_t __extendhfdf2(float16_t x)
{
    return f16_to_f64(x);
}

PREFIX float64_t __extendsfdf2(float32_t x)
{
    return f32_to_f64(x);
}

PREFIX float16_t __gnu_f2h_ieee(float32_t x)
{
    return f32_to_f16(x);
}

PREFIX float16_t __truncdfhf2(float64_t x)
{
    return f64_to_f16(x);
}

PREFIX float32_t __truncdfsf2(float64_t x)
{
    return f64_to_f32(x);
}

PREFIX int32_t __fixhfsi(float16_t x)
{
    return f16_to_i32(x, softfloat_round_minMag, false);
}

PREFIX int64_t __fixhfdi(float16_t x)
{
    return f16_to_i64(x, softfloat_round_minMag, false);
}

PREFIX int32_t __fixsfsi(float32_t x)
{
    return f32_to_i32(x, softfloat_round_minMag, false);
}

PREFIX int64_t __fixsfdi(float32_t x)
{
    return f32_to_i64(x, softfloat_round_minMag, false);
}

PREFIX int32_t __fixdfsi(float64_t x)
{
    return f64_to_i32(x, softfloat_round_minMag, false);
}

PREFIX int64_t __fixdfdi(float64_t x)
{
    return f64_to_i64(x, softfloat_round_minMag, false);
}

PREFIX uint32_t __fixunshfsi(float16_t x)
{
    return f16_to_ui32(x, softfloat_round_minMag, false);
}

PREFIX uint64_t __fixunshfdi(float16_t x)
{
    return f16_to_ui64(x, softfloat_round_minMag, false);
}

PREFIX uint32_t __fixunssfsi(float32_t x)
{
    return f32_to_ui32(x, softfloat_round_minMag, false);
}

PREFIX uint64_t __fixunssfdi(float32_t x)
{
    return f32_to_ui64(x, softfloat_round_minMag, false);
}

PREFIX uint32_t __fixunsdfsi(float64_t x)
{
    return f64_to_ui32(x, softfloat_round_minMag, false);
}

PREFIX uint64_t __fixunsdfdi(float64_t x)
{
    return f64_to_ui64(x, softfloat_round_minMag, false);
}

PREFIX float16_t __floatsihf(int32_t x)
{
    return i32_to_f16(x);
}

PREFIX float32_t __floatsisf(int32_t x)
{
    return i32_to_f32(x);
}

PREFIX float64_t __floatsidf(int32_t x)
{
    return i32_to_f64(x);
}

PREFIX float16_t __floatdihf(int64_t x)
{
    return i64_to_f16(x);
}

PREFIX float32_t __floatdisf(int64_t x)
{
    return i64_to_f32(x);
}

PREFIX float64_t __floatdidf(int64_t x)
{
    return i64_to_f64(x);
}

PREFIX float16_t __floatunsihf(uint32_t x)
{
    return ui32_to_f16(x);
}

PREFIX float32_t __floatunsisf(uint32_t x)
{
    return ui32_to_f32(x);
}

PREFIX float64_t __floatunsidf(uint32_t x)
{
    return ui32_to_f64(x);
}

PREFIX float16_t __floatundihf(uint64_t x)
{
    return ui64_to_f16(x);
}

PREFIX float32_t __floatundisf(uint64_t x)
{
    return ui64_to_f32(x);
}

PREFIX float64_t __floatundidf(uint64_t x)
{
    return ui64_to_f64(x);
}
