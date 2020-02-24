all:
	sh-elf-gcc -c -Wa,-gstabs -o asmfunc.o asmfunc.s
	sh-elf-gcc -c -g -o main.o main.c
	sh-elf-ld -Tsh7262_large.ld -nostartfiles -o lcdblink.elf asmfunc.o main.o
	sh-elf-objcopy -j .text -j .data -O binary lcdblink.elf lcdblink.bin
clean:
	rm lcdblink.elf lcdblink.bin asmfunc.o main.o
