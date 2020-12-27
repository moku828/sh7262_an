all:
	sh-elf-gcc -c -Wa,-gstabs -o asmfunc.o asmfunc.s
	sh-elf-gcc -c -g -o main.o main.c
	sh-elf-ld -Tsh7262_large.ld -nostartfiles -o irrcvirq.elf asmfunc.o main.o -lgcc -L/usr/local/sh-tools/lib/gcc/sh-elf/3.4.5/m2
	sh-elf-objcopy -j .text -j .data -O binary irrcvirq.elf irrcvirq.bin
clean:
	rm irrcvirq.elf irrcvirq.bin asmfunc.o main.o
