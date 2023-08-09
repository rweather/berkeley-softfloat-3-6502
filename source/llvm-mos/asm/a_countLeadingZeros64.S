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

.include "imag.inc"

.text

.global softfloat_a_countLeadingZeros64
.section .text.softfloat_a_countLeadingZeros64,"ax",@progbits
softfloat_a_countLeadingZeros64:
  ldy __rc7
  bne .Lsoftfloat_a_countLeadingZeros64_b7
  ldy __rc6
  bne .Lsoftfloat_a_countLeadingZeros64_b6
  ldy __rc5
  bne .Lsoftfloat_a_countLeadingZeros64_b5
  ldy __rc4
  bne .Lsoftfloat_a_countLeadingZeros64_b4
  jsr softfloat_a_countLeadingZeros32
  clc
  adc #32
  rts
.Lsoftfloat_a_countLeadingZeros64_b4:
  lda softfloat_countLeadingZeros8,y
  clc
  adc #24
  rts
.Lsoftfloat_a_countLeadingZeros64_b5:
  lda softfloat_countLeadingZeros8,y
  clc
  adc #16
  rts
.Lsoftfloat_a_countLeadingZeros64_b6:
  lda softfloat_countLeadingZeros8,y
  clc
  adc #8
  rts
.Lsoftfloat_a_countLeadingZeros64_b7:
  lda softfloat_countLeadingZeros8,y
  rts
