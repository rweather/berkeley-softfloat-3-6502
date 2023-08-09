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

;
; uint32_t softfloat_a_shiftRightJam32( uint32_t a, uint_fast16_t dist )
;
; -- shift right and set the low bit of the result to 1
; -- if any of the shifted-out bits were 1.
;
.global softfloat_a_shiftRightJam32
.section .text.softfloat_a_shiftRightJam32,"ax",@progbits
softfloat_a_shiftRightJam32:
  ; Move "a" to rc16:rc17:rc2:rc3
  sta __rc16
  stx __rc17
  ; Get the shift count into Y, which can be arbitrarily large.
  ; If the shift count is >= 31 then we do a quick non-zero check.
  ldy __rc5
  bne .Lsoftfloat_a_shiftRightJam32_quick
  ldy __rc4
  beq .Lsoftfloat_a_shiftRightJam32_zero
  cpy #31
  bcs .Lsoftfloat_a_shiftRightJam32_quick
  ; A will accumulate the number of non-zero bits shifted out.
  lda #0
.Lsoftfloat_a_shiftRightJam32_loop:
  ; Shift everything down by one bit.
  ror __rc3
  ror __rc2
  ror __rc17
  ror __rc16
  ; Accumulate the shifted-out bits.
  adc #0
  ; Are we done yet?
  dey
  bne .Lsoftfloat_a_shiftRightJam32_loop
  ; Set the low bit of the result if A is non-zero.
  ldx __rc17
  ora #0
  beq .Lsoftfloat_a_shiftRightJam32_done
.Lsoftfloat_a_shiftRightJam32_set_bit:
  lda __rc16
  ora #1
  rts
.Lsoftfloat_a_shiftRightJam32_done:
  lda __rc16
.Lsoftfloat_a_shiftRightJam32_zero:
  rts
.Lsoftfloat_a_shiftRightJam32_quick:
  ; Shift count is >= 31.
  ora __rc17
  ora __rc2
  ora __rc3
  beq .Lsoftfloat_a_shiftRightJam32_done
  lda #1
  ldx #0
  stx __rc2
  stx __rc3
  rts
