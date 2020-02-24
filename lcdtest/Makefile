all:
	sh-elf-gcc -c -Wa,-gstabs -o asmfunc.o asmfunc.s
	sh-elf-gcc -c -g -o main.o main.c
	sh-elf-ld -Tsh7262_large.ld -nostartfiles -o lcdtest.elf asmfunc.o main.o
	sh-elf-objcopy -j .text -j .data -O binary lcdtest.elf lcdtest.bin
clean:
	rm lcdtest.elf lcdtest.bin asmfunc.o main.o
