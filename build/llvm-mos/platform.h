
/*============================================================================

This C header template is part of the SoftFloat IEEE Floating-Point Arithmetic
Package, Release 3e, by John R. Hauser.

Copyright 2011, 2012, 2013, 2014, 2015, 2016 The Regents of the University of
California.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions, and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions, and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. Neither the name of the University nor the names of its contributors may
    be used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS", AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ARE
DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/

#include <stdint.h>

/*----------------------------------------------------------------------------
*----------------------------------------------------------------------------*/
#define LITTLEENDIAN 1

/*----------------------------------------------------------------------------
*----------------------------------------------------------------------------*/
#define INLINE inline

/*----------------------------------------------------------------------------
*----------------------------------------------------------------------------*/
#define THREAD_LOCAL

/*----------------------------------------------------------------------------
* Override definitions in primitives.h
*----------------------------------------------------------------------------*/

#ifndef SOFTFLOAT_NO_ASM

/* Shift right while jamming shifted out bits back into the LSB */
__attribute__((leaf)) uint64_t softfloat_a_shortShiftRightJam64( uint64_t a, uint_fast8_t dist );
__attribute__((leaf)) uint32_t softfloat_a_shiftRightJam32( uint32_t a, uint_fast16_t dist );
__attribute__((leaf)) uint64_t softfloat_a_shiftRightJam64( uint64_t a, uint_fast32_t dist );
#define softfloat_shortShiftRightJam64 softfloat_a_shortShiftRightJam64
#define softfloat_shiftRightJam32 softfloat_a_shiftRightJam32
#define softfloat_shiftRightJam64 softfloat_a_shiftRightJam64

/* Count leading zeroes in words of various sizes */
__attribute__((leaf)) uint_fast8_t softfloat_a_countLeadingZeros16( uint16_t a );
__attribute__((leaf)) uint_fast8_t softfloat_a_countLeadingZeros32( uint32_t a );
__attribute__((leaf)) uint_fast8_t softfloat_a_countLeadingZeros64( uint64_t a );
#define softfloat_countLeadingZeros16 softfloat_a_countLeadingZeros16
#define softfloat_countLeadingZeros32 softfloat_a_countLeadingZeros32
#define softfloat_countLeadingZeros64 softfloat_a_countLeadingZeros64

/* Multiply two 16-bit values with a 32-bit result. */
__attribute__((leaf)) uint_fast32_t softfloat_a_mul16x16( uint_fast16_t a, uint_fast16_t b );

/* Multiply two 16-bit values with a 32-bit result, returning the
 * high 16 bits only. */
__attribute__((leaf)) uint_fast16_t softfloat_a_mul16x16High( uint_fast16_t a, uint_fast16_t b );

/* Multiply two 16-bit values with a 32-bit result, shift it right
 * by 16 bits, and jam in the shifted-out bits.  This is faster than
 * upcasting and doing a full 32-bit by 32-bit multiply. */
__attribute__((leaf)) uint_fast16_t softfloat_a_mul16x16Jam( uint_fast16_t a, uint_fast16_t b );

/* Multiply two 32-bit values with a 64-bit result. */
__attribute__((leaf)) uint_fast64_t softfloat_a_mul32x32( uint_fast32_t a, uint_fast32_t b );

/* Multiply two 32-bit values with a 64-bit result, returning the
 * high 32 bits only. */
__attribute__((leaf)) uint_fast32_t softfloat_a_mul32x32High( uint_fast32_t a, uint_fast32_t b );

/* Multiply two 32-bit values with a 64-bit result, shift it right
 * by 32 bits, and jam in the shifted-out bits.  This is faster than
 * upcasting and doing a full 64-bit by 64-bit multiply. */
__attribute__((leaf)) uint_fast32_t softfloat_a_mul32x32Jam( uint_fast32_t a, uint_fast32_t b );

#endif /* SOFTFLOAT_NO_ASM */
