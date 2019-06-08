.global start
.global _sleep
.extern _main

.section .stack, "w"
	.align  4
	.space  32768
stack_base:

.section .text, "ax"

start:
	MOV.L   __vect, R0
	LDC     R0, VBR
	MOV.L   _stack_base, SP
	MOV.L   __main, R0
	JSR     @R0
	NOP
loop:
	BRA     loop
	NOP
_sleep:
	SLEEP
	NOP
	RTS
	NOP
	.align  4
__main:
	.long   _main
_stack_base:
	.long   stack_base
__vect:
	.long   _vect

.section .bss, "aw"
	.align  4
	.space  32768

.section .text, "ax"
	.align  4
_vect:
	.space  704
	.long   _isr_cmi1
