;===============================================================================
;            Exp18_6a.asm : Assembly Program for C & Assembly Link
;===============================================================================
;                            Designed and programmed by Duck-Yong Yoon in 2005.

	.module Exp18_6a
	.optsdcc -mmcs51 --model-small

	.globl _Mul_8bit_PARM_2
	.globl _Mul_8bit
	.globl _Delay_1sec

	ar7 = 0x07
	acc = 0xE0
	b   = 0xF0

	.area DSEG (DATA)
_Mul_8bit_PARM_2:
	.ds 1

	.area CSEG (CODE)

;-------------------------------------------------------------------------------
;  8-Bit Multiplication (DPL = DPL * _Mul_8bit_PARM_2)
;-------------------------------------------------------------------------------
_Mul_8bit:
	push	acc
	push	b
	mov	a,dpl			; DPL = multiplicand  (input)
	mov	b,_Mul_8bit_PARM_2	; PARM_2 = multiplier (input)
	mul	ab
	mov	dpl,a			; DPL = multiplication(output)
	pop	b
	pop	acc
	ret

;-------------------------------------------------------------------------------
;  Delay for 1 Second(at 24MHz)
;-------------------------------------------------------------------------------
_Delay_1sec:
	push	acc
	push	b
	push	ar7

	mov	a,#200			; 200*250*40 = 2000000 cycle
DELAY1:	mov	b,#250
DELAY2:	mov	r7,#18			; 1
DELAY3:	djnz	r7,DELAY3		; 2*18 = 36
	nop				; 1
	djnz	b,DELAY2		; 2
	djnz	acc,DELAY1

	pop	ar7
	pop	b
	pop	acc
	ret
