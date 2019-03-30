all:
	sh-elf-gcc -c -Wa,-gstabs -o asmfunc.o asmfunc.s
	sh-elf-gcc -c -g -o main.o main.c
	sh-elf-ld -Tsh7262_large.ld -nostartfiles -o blink.elf asmfunc.o main.o
	sh-elf-objcopy -j .text -j .data -O binary blink.elf blink.bin
clean:
	rm blink.elf blink.bin asmfunc.o main.o
