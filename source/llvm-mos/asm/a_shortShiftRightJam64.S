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
; uint64_t softfloat_a_shortShiftRightJam64( uint64_t a, uint_fast8_t dist )
;
; -- shift right and set the low bit of the result to 1
; -- if any of the shifted-out bits were 1.
;
.global softfloat_a_shortShiftRightJam64
.section .text.softfloat_shortShiftRightJam64,"ax",@progbits
softfloat_a_shortShiftRightJam64:
  ; Move "a" to rc16:rc17:rc2..rc7
  sta __rc16
  stx __rc17
  ; Get the shift count into Y (assumed to be 1 to 63 only).
  ldy __rc8
  ; A will accumulate the number of non-zero bits shifted out.
  lda #0
.Lsoftfloat_shortShiftRightJam64_loop:
  ; Shift everything down by one bit.
  lsr __rc7
  ror __rc6
  ror __rc5
  ror __rc4
  ror __rc3
  ror __rc2
  ror __rc17
  ror __rc16
  ; Accumulate the shifted-out bits.
  adc #0
  ; Are we done yet?
  dey
  bne .Lsoftfloat_shortShiftRightJam64_loop
  ; Set the low bit of the result if A is non-zero.
  ldx __rc17
  ora #0
  beq .Lsoftfloat_shortShiftRightJam64_done
.Lsoftfloat_shortShiftRightJam64_set_bit:
  lda __rc16
  ora #1
  rts
.Lsoftfloat_shortShiftRightJam64_done:
  lda __rc16
.Lsoftfloat_shortShiftRightJam64_zero:
  rts
