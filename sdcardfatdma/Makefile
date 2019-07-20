all:
	sh-elf-gcc -c -Wa,-gstabs -o asmfunc.o asmfunc.s
	sh-elf-gcc -c -g -o main.o main.c
	sh-elf-ld -Tsh7262_large.ld -nostartfiles -o sdcardfatdma.elf asmfunc.o main.o -L/usr/local/sh-tools/sh-elf/lib/m2 -lc
	sh-elf-objcopy -j .text -j .data -O binary sdcardfatdma.elf sdcardfatdma.bin
clean:
	rm sdcardfatdma.elf sdcardfatdma.bin asmfunc.o main.o
