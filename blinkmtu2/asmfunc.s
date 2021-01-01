.global start
.extern _main

.section .stack, "w"
	.align  4
	.space  32768
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
	.align  4
__main:
	.long   _main
_stack_base:
	.long   stack_base

.section .bss, "aw"
	.align  4
	.space  32768
