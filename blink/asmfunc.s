.global start
.extern _main

.section .stack, "w"
	.align  4
	.space  65536
stack_base:

.section .vector, "ax"
vector_table:
	.long start
	.long stack_base
	.long start
	.long stack_base
	.space 16
	.long vector_table
	.space 1216

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

.section .text, "ax"

