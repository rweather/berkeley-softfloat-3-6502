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
; uint_fast32_t softfloat_a_mul16x16Helper( uint_fast16_t a, uint_fast16_t b );
;
; result = ((uint32_t)a) * b
;
; "a" is in A:X on entry.  "b" is in rc2:rc3 on entry.  "result" is in
; rc4:rc5:rc6:rc7 on exit.

; The result is not compatible with llvm-mos calling conventions.
; Callers to this function must move the result to the correct registers.
;
.section .text.softfloat_a_mul16x16Helper,"ax",@progbits
softfloat_a_mul16x16Helper:
  ;
  ; Set the intermediate 32-bit result to zero.
  ;
  ldy #0
  sty __rc4
  sty __rc5
  sty __rc6
  sty __rc7
  ;
  ; Shift A:X into rc8:rc9
  ;
  sta __rc8
  stx __rc9
  ldy #16
  bne .Lsoftfloat_a_mul16x16Helper_skip_mul2
.Lsoftfloat_a_mul16x16Helper_loop:
  ;
  ; Multiply the result by 2.
  ;
  asl __rc4
  rol __rc5
  rol __rc6
  rol __rc7
.Lsoftfloat_a_mul16x16Helper_skip_mul2:
  ;
  ; Is the high bit of "a" set to 1?
  ;
  asl __rc8
  rol __rc9
  bcc .Lsoftfloat_a_mul16x16Helper_no_add
  ;
  ; Add "b" to the intermediate result.
  ;
  lda __rc4
  clc
  adc __rc2
  sta __rc4
  lda __rc5
  adc __rc3
  sta __rc5
  ;
  ; Shortcut the rest if we don't need to do carry propagation
  ; into the high word of the result.
  ;
  bcc .Lsoftfloat_a_mul16x16Helper_no_add
  inc __rc6
  bne .Lsoftfloat_a_mul16x16Helper_no_add
  inc __rc7
  ;
  ; Bottom of the multiplication loop.
  ;
.Lsoftfloat_a_mul16x16Helper_no_add:
  dey
  bne .Lsoftfloat_a_mul16x16Helper_loop
  rts

;
; uint_fast32_t softfloat_a_mul16x16( uint_fast16_t a, uint_fast16_t b );
;
; result = ((uint32_t)a) * b
;
; "a" is in A:X on entry.  "b" is in rc2:rc3 on entry.  "result" is in
; A:X:rc2:rc3 on exit.
;
.global softfloat_a_mul16x16
.section .text.softfloat_a_mul16x16,"ax",@progbits
softfloat_a_mul16x16:
  jsr softfloat_a_mul16x16Helper
  ;
  ; Copy the result to the correct registers.
  ;
  lda __rc7
  sta __rc3
  lda __rc6
  sta __rc2
  ldx __rc5
  lda __rc4
  rts

;
; uint_fast16_t softfloat_a_mul16x16High( uint_fast16_t a, uint_fast16_t b );
;
; result = (((uint32_t)a) * b) >> 16
;
; "a" is in A:X on entry.  "b" is in rc2:rc3 on entry.  "result" is in A:X.
;
.global softfloat_a_mul16x16High
.section .text.softfloat_a_mul16x16High,"ax",@progbits
softfloat_a_mul16x16High:
  jsr softfloat_a_mul16x16Helper
  ;
  ; Copy the result to the correct registers.
  ;
  ldx __rc7
  lda __rc6
  rts

;
; uint_fast16_t softfloat_a_mul16x16Jam( uint_fast16_t a, uint_fast16_t b );
;
; result = shiftRightJam32(((uint32_t)a) * b, 16);
;
; "a" is in A:X on entry.  "b" is in rc2:rc3 on entry.  "result" is in A:X.
;
.global softfloat_a_mul16x16Jam
.section .text.softfloat_a_mul16x16Jam,"ax",@progbits
softfloat_a_mul16x16Jam:
  jsr softfloat_a_mul16x16Helper
  ;
  ; If the low word is non-zero, then we need to jam a 1 bit
  ; into the high word of the result.
  ;
  ldx __rc7
  lda __rc4
  ora __rc5
  beq .Lsoftfloat_a_mul16x16Jam_no_jam
  lda __rc6
  ora #1
  rts
.Lsoftfloat_a_mul16x16Jam_no_jam:
  lda __rc6
  rts
