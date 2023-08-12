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
; uint_fast32_t softfloat_a_mul32x32Jam( uint_fast32_t a, uint_fast32_t b );
;
; result = shortShiftRightJam64(((uint64_t)a) * b, 32);
;
; "a" is in A:X:rc2:rc3 on entry.  "b" is in rc4:rc5:rc6:rc7 on entry.
; "result" is in A:X:rc2:rc3 on exit.
;
.global softfloat_a_mul32x32Jam
.section .text.softfloat_a_mul32x32Jam,"ax",@progbits
softfloat_a_mul32x32Jam:
  ;
  ; Set the intermediate 64-bit result to zero.
  ;
  ldy #0
  sty __rc8
  sty __rc9
  sty __rc10
  sty __rc11
  sty __rc12
  sty __rc13
  sty __rc14
  sty __rc15
  ;
  ; Shift A:X into rc16:rc17
  ;
  sta __rc16
  stx __rc17
  ldy #32
  bne .Lsoftfloat_a_mul32x32Jam_skip_mul2
.Lsoftfloat_a_mul32x32Jam_loop:
  ;
  ; Multiply the result by 2.
  ;
  asl __rc8
  rol __rc9
  rol __rc10
  rol __rc11
  rol __rc12
  rol __rc13
  rol __rc14
  rol __rc15
.Lsoftfloat_a_mul32x32Jam_skip_mul2:
  ;
  ; Is the high bit of "a" set to 1?
  ;
  asl __rc16
  rol __rc17
  rol __rc2
  rol __rc3
  bcc .Lsoftfloat_a_mul32x32Jam_no_add
  ;
  ; Add "b" to the intermediate result.
  ;
  lda __rc8
  clc
  adc __rc4
  sta __rc8
  lda __rc9
  adc __rc5
  sta __rc9
  lda __rc10
  adc __rc6
  sta __rc10
  lda __rc11
  adc __rc7
  sta __rc11
  ;
  ; Shortcut the rest if we don't need to do carry propagation
  ; into the high word of the result.
  ;
  bcc .Lsoftfloat_a_mul32x32Jam_no_add
  inc __rc12
  bne .Lsoftfloat_a_mul32x32Jam_no_add
  inc __rc13
  bne .Lsoftfloat_a_mul32x32Jam_no_add
  inc __rc14
  bne .Lsoftfloat_a_mul32x32Jam_no_add
  inc __rc15
  ;
  ; Bottom of the multiplication loop.
  ;
.Lsoftfloat_a_mul32x32Jam_no_add:
  dey
  bne .Lsoftfloat_a_mul32x32Jam_loop
  ;
  ; If the low word is non-zero, then we need to jam a 1 bit
  ; into the high word of the result.
  ;
  lda __rc8
  ora __rc9
  ora __rc10
  ora __rc11
  beq .Lsoftfloat_a_mul32x32Jam_no_jam
  lda __rc15
  sta __rc3
  lda __rc14
  sta __rc2
  ldx __rc13
  lda __rc12
  ora #1
  rts
.Lsoftfloat_a_mul32x32Jam_no_jam:
  lda __rc15
  sta __rc3
  lda __rc14
  sta __rc2
  ldx __rc13
  lda __rc12
  rts
