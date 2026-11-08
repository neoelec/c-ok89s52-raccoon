;===============================================================================
;  startup.asm: User-defined Power-On Initialization for SDCC (sdas8051)
;===============================================================================

	.module STARTUP
	.optsdcc -mmcs51 --model-small

	.area IABS (ABS,DATA)
	.org 0x0030
	.ds 2

	.area GSINIT5 (CODE)
	mov	0x30,#0b00000101		; LED data 1
	mov	0x31,#0b00001010		; LED data 2
