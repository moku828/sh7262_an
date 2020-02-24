.global start
.global _swt_tsk
.global _tskid
.extern _main

.section .stack, "w"
	.align  4
	.space  65536
stack_base:

.section .text, "ax"

start:
	MOV.L   _stack_base, SP
	MOV.L   __main, R0
	JSR     @R0
	NOP
loop:
	BRA     loop
	NOP
_swt_tsk:
	MOV.L   __tskid, R2
	MOV.L   @R2, R0
	SHLL8   R0
	MOV.L   __tskinf, R1
	ADD     R0, R1
	STS     PR, R0
	MOV.L   R0, @R1
	ADD     #4, R1
	MOV.L   SP, @R1
	MOV.L   @R2, R0
	XOR     #1, R0
	MOV.L   R0, @R2
	SHLL8   R0
	MOV.L   __tskinf, R1
	ADD     R0, R1
	MOV.L   @R1, R0
	LDS     R0, PR
	ADD     #4, R1
	MOV.L   @R1, SP
	RTS
	NOP

	.align  4
__main:
	.long   _main
_stack_base:
	.long   stack_base
__tskinf:
	.long   _tskinf
__tskid:
	.long   _tskid

.section .bss, "aw"
	.align  4
_tskinf:
	.space  16
_tskid:
	.space  4

.section .text, "ax"

