all:
	sh-elf-gcc -c -Wa,-gstabs -o asmfunc.o asmfunc.s
	sh-elf-gcc -c -g -o main.o main.c
	sh-elf-ld -Tsh7262_large.ld -nostartfiles -o blinkmtu2.elf asmfunc.o main.o
	sh-elf-objcopy -j .text -j .data -O binary blinkmtu2.elf blinkmtu2.bin
clean:
	rm blinkmtu2.elf blinkmtu2.bin asmfunc.o main.o
