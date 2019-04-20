all:
	sh-elf-gcc -c -Wa,-gstabs -o asmfunc.o asmfunc.s
	sh-elf-gcc -c -g -o main.o main.c
	sh-elf-ld -Tsh7262_large.ld -nostartfiles -o lcdfill.elf asmfunc.o main.o
	sh-elf-objcopy -j .text -j .data -O binary lcdfill.elf lcdfill.bin
clean:
	rm lcdfill.elf lcdfill.bin asmfunc.o main.o
